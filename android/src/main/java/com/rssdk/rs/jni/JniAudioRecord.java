package com.monitoring.optimus.rs.jni;

import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder.AudioSource;
import android.os.Process;
import android.util.Log;

import java.nio.ByteBuffer;

public class JniAudioRecord {
    private static final String  TAG = "JniAudioRecord";

    private JniAudioEffect       effect_;
    private final long           native_sess_;
    private AudioRecord          audio_record_ = null;
    private JniAudioRecordThread audio_thread_ = null;
    private ByteBuffer           buffer_;

    private class JniAudioRecordThread extends Thread {
        private volatile boolean keep_alive = true;

        public JniAudioRecordThread(String name) {
            super(name);
        }

        @Override
        public void run() {
            Process.setThreadPriority(Process.THREAD_PRIORITY_URGENT_AUDIO);
            while (keep_alive) {
                int bytesRead = audio_record_.read(buffer_, buffer_.capacity());
                if (bytesRead == buffer_.capacity()) {
                    if (keep_alive) {
                        native_send_record_data(bytesRead, native_sess_);
                    }
                } else {
                    Log.e(TAG, "===sharp JniAudioRecord AudioRecord.read failed:" + bytesRead);
                    if (bytesRead == AudioRecord.ERROR_INVALID_OPERATION) {
                        keep_alive = false;
                    }
                }
            }

            if (audio_record_ != null) {
                try {
                    audio_record_.stop();
                } catch (IllegalStateException e) {
                    Log.e(TAG, "===sharp JniAudioRecord AudioRecord.stop failed:" + e.getMessage());
                }
            }
        }

        public void stop_thread() {
            keep_alive = false;
        }
    }

    JniAudioRecord(long native_sess) {
        this.native_sess_ = native_sess;
        effect_ = JniAudioEffect.create();
    }

    private int init(int sample_rate, int channel) {
        assert (audio_record_ == null);
        assert (audio_thread_ == null);

        final int bytes_per_frame = channel * (16 / 8);
        final int frames_per_buffer = sample_rate / 100;
        buffer_ = ByteBuffer.allocateDirect(bytes_per_frame * frames_per_buffer);
        native_cache_buffer_address(buffer_, native_sess_);

        final int mini_buffer_size = AudioRecord.getMinBufferSize(sample_rate,
                AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT);
        if (mini_buffer_size == AudioRecord.ERROR || mini_buffer_size == AudioRecord.ERROR_BAD_VALUE) {
            Log.e(TAG, "===sharp audio JniAudioRecord AudioRecord.getMinBufferSize failed:"
                    + mini_buffer_size);
            return -1;
        }

        int buffer_size_in_bytes = Math.max(2 * mini_buffer_size, buffer_.capacity());
        try {
            audio_record_ = new AudioRecord(AudioSource.VOICE_COMMUNICATION, sample_rate,
                    AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT, buffer_size_in_bytes);
        } catch (IllegalArgumentException e) {
            Log.e(TAG, "===sharp audio JniAudioRecord new AudioRecord failed");
            if (audio_record_ != null) {
                audio_record_.release();
                audio_record_ = null;
            }
            return -1;
        }

        if (audio_record_ == null || audio_record_.getState() != AudioRecord.STATE_INITIALIZED) {
            Log.e(TAG, "===sharp audio JniAudioRecord start failed");
            if (audio_record_ != null) {
                audio_record_.release();
                audio_record_ = null;
            }
            return -1;
        }

        if (effect_ != null) {
            effect_.init(audio_record_.getAudioSessionId());
        }

        Log.e(TAG, "===sharp audio JniAudioRecord init success");
        return 0;
    }

    private int start() {
        if (audio_record_ != null) {
            try {
                audio_record_.startRecording();
            } catch (IllegalStateException e) {
                Log.e(TAG, "===sharp audio JniAudioRecord AudioRecord.startRecording failed:"
                        + e.getMessage());
                return -1;
            }

            if (audio_record_.getRecordingState() != AudioRecord.RECORDSTATE_RECORDING) {
                Log.e(TAG, "===sharp audio JniAudioRecord AudioRecord.getRecordingState() failed:"
                        + audio_record_.getRecordingState());
                return -1;
            }

            audio_thread_ = new JniAudioRecordThread("JniAudioRecordThread");
            audio_thread_.start();

            Log.e(TAG, "===sharp audio JniAudioRecord start success");
            return 0;
        }

        Log.e(TAG, "===sharp audio JniAudioRecord start failed:audio_record is null");
        return -1;
    }

    private int stop() {
        if (audio_thread_ != null) {
            audio_thread_.stop_thread();
            try {
                audio_thread_.join();
            } catch (InterruptedException e) {
                Log.e(TAG, "===sharp audio JniAudioRecord Thread.join failed:" + e.getMessage());
            }
            audio_thread_ = null;
        }

        if (audio_record_ != null) {
            audio_record_.release();
            audio_record_ = null;
        }

        Log.e(TAG, "===sharp audio JniAudioRecord stop success");
        return 0;
    }

    private native void native_cache_buffer_address(ByteBuffer buffer, long native_sess);
    private native void native_send_record_data(int bytes, long native_sess);
}
