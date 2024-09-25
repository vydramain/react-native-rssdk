package com.rssdk.rs.jni;

import android.content.Context;
import android.media.AudioAttributes;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.os.Build;
import android.os.Process;
import android.util.Log;

import com.blankj.utilcode.util.Utils;

import java.nio.ByteBuffer;

public class JniAudioTrack {
    private static final String TAG = "JniAudioTrack";

    private final long native_sess_;
    //    private final AudioManager   audio_manager_;
    private AudioTrack audio_track_ = null;
    private JniAudioTrackThread audio_thread_ = null;
    private ByteBuffer buffer_;
    private final boolean os_above_21_ = (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) ? true : false;

    private AudioManager audioManager;

    private class JniAudioTrackThread extends Thread {
        private volatile boolean keep_alive = true;

        public JniAudioTrackThread(String name) {
            super(name);
        }

        @Override
        public void run() {
            Process.setThreadPriority(Process.THREAD_PRIORITY_URGENT_AUDIO);
            assert (audio_track_.getPlayState() == AudioTrack.PLAYSTATE_PLAYING);

            final int size_in_bytes = buffer_.capacity();
            while (keep_alive) {
                native_get_track_data(size_in_bytes, native_sess_);
                assert (size_in_bytes <= buffer_.remaining());

                int bytes_written;
                if (os_above_21_) {
                    bytes_written = audio_track_.write(buffer_, size_in_bytes, AudioTrack.WRITE_BLOCKING);
                } else {
                    bytes_written = audio_track_.write(buffer_.array(), buffer_.arrayOffset(), size_in_bytes);
                }

                if (bytes_written != size_in_bytes) {
                    Log.e(TAG, "===sharp JniAudioTrack AudioTrack.write invalid number:" + bytes_written);
                    if (bytes_written < 0) {
                        keep_alive = false;
                    }
                }

                buffer_.rewind();
            }

            if (audio_track_ != null) {
                try {
                    audio_track_.stop();
                } catch (IllegalStateException e) {
                    Log.e(TAG, "===sharp JniAudioTrack AudioTrack.stop failed:" + e.getMessage());
                }
            }
        }

        public void stop_thread() {
            keep_alive = false;
        }
    }

    JniAudioTrack(long native_sess) {
        this.native_sess_ = native_sess;
        audioManager = (AudioManager) Utils.getApp().getSystemService(Context.AUDIO_SERVICE);
    }

    private int init(int sample_rate, int channel) {
        assert (audio_track_ == null);
        assert (audio_thread_ == null);

        final int bytes_per_frame = channel * (16 / 8);
        final int frames_per_buffer = sample_rate / 100;
        buffer_ = ByteBuffer.allocateDirect(bytes_per_frame * frames_per_buffer);
        native_cache_buffer_address(buffer_, native_sess_);

        final int mini_buffer_size = AudioTrack.getMinBufferSize(sample_rate,
                AudioFormat.CHANNEL_OUT_MONO, AudioFormat.ENCODING_PCM_16BIT);
        if (mini_buffer_size < buffer_.capacity()) {
            Log.e(TAG, "===sharp audio JniAudioTrack AudioTrack.getMinBufferSize invalid:" + mini_buffer_size);
            return -1;
        }

        try {
            if (os_above_21_) {
                final int default_sample_rate = AudioTrack.getNativeOutputSampleRate(AudioManager.STREAM_VOICE_CALL);
                if (sample_rate != default_sample_rate) {
                    Log.e(TAG, "===sharp audio JniAudioTrack AudioTrack.getNativeOutputSampleRate not equal(app:"
                            + sample_rate + ", default:" + default_sample_rate + "):");
                }

                audio_track_ = new AudioTrack(
                        new AudioAttributes.Builder()
                                .setUsage(AudioAttributes.USAGE_VOICE_COMMUNICATION)
                                .setContentType(AudioAttributes.CONTENT_TYPE_SPEECH)
                                .build(),
                        new AudioFormat.Builder()
                                .setEncoding(AudioFormat.ENCODING_PCM_16BIT)
                                .setSampleRate(sample_rate)
                                .setChannelMask(AudioFormat.CHANNEL_OUT_MONO)
                                .build(),
                        mini_buffer_size,
                        AudioTrack.MODE_STREAM,
                        AudioManager.AUDIO_SESSION_ID_GENERATE);
            } else {
                audio_track_ = new AudioTrack(AudioManager.STREAM_VOICE_CALL, sample_rate, AudioFormat.CHANNEL_OUT_MONO,
                        AudioFormat.ENCODING_PCM_16BIT, mini_buffer_size, AudioTrack.MODE_STREAM);
            }
        } catch (IllegalArgumentException e) {
            Log.e(TAG, "===sharp audio JniAudioTrack new AudioTrack failed");
            if (audio_track_ != null) {
                audio_track_.release();
                audio_track_ = null;
            }
            return -1;
        }

        if (audio_track_ == null || audio_track_.getState() != AudioTrack.STATE_INITIALIZED) {
            Log.e(TAG, "===sharp audio JniAudioTrack start failed");
            if (audio_track_ != null) {
                audio_track_.release();
                audio_track_ = null;
            }
            return -1;
        }

        Log.e(TAG, "===sharp audio JniAudioTrack init success");
        return 0;
    }

    private int start() {
        if (audio_track_ != null) {
            try {
                audio_track_.play();
            } catch (IllegalStateException e) {
                Log.e(TAG, "===sharp audio JniAudioTrack AudioTrack.play failed:" + e.getMessage());
                if (audio_track_ != null) {
                    audio_track_.release();
                    audio_track_ = null;
                }
                return -1;
            }

            if (audio_track_.getPlayState() != AudioTrack.PLAYSTATE_PLAYING) {
                Log.e(TAG, "===sharp audio JniAudioTrack AudioTrack.getPlayState() failed:"
                        + audio_track_.getPlayState());
                if (audio_track_ != null) {
                    audio_track_.release();
                    audio_track_ = null;
                }
                return -1;
            }

            audio_thread_ = new JniAudioTrackThread("AudioTrackJavaThread");
            audio_thread_.start();

            Log.e(TAG, "===sharp audio JniAudioTrack start success");
            return 0;
        }

        Log.e(TAG, "===sharp audio JniAudioTrack start failed:audio_track is null");
        return -1;
    }

    private int stop() {
        if (audio_thread_ != null) {
            audio_thread_.stop_thread();
            try {
                audio_thread_.join();
            } catch (InterruptedException e) {
                Log.e(TAG, "===sharp audio JniAudioTrack Thread.join failed:" + e.getMessage());
            }
            audio_thread_ = null;
        }

        if (audio_track_ != null) {
            audio_track_.release();
            audio_track_ = null;
        }

        Log.e(TAG, "===sharp audio JniAudioTrack stop success");
        return 0;
    }

    private void setVolume(int streamType, int volumeIndex,int flag) {
        if (volumeIndex >= 0 && volumeIndex <= get_max_volume()) {
            audioManager.setStreamVolume(streamType, volumeIndex, flag);
        }
    }

    /**
     * 设置music音量大小
     *
     * @param volumeIndex
     */
    public void setMusicVolume(int volumeIndex) {
        setVolume(AudioManager.STREAM_MUSIC, volumeIndex,AudioManager.FLAG_ALLOW_RINGER_MODES);
    }

    private int get_volume() {
        return audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
    }

    private int set_volume(int volume) {
        setVolume(AudioManager.STREAM_MUSIC, volume ,AudioManager.FLAG_ALLOW_RINGER_MODES);
        return 0;
    }

    private int get_max_volume() {
        return audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
    }

    private native void native_cache_buffer_address(ByteBuffer buffer, long native_sess);

    private native void native_get_track_data(int bytes, long native_sess);
}
