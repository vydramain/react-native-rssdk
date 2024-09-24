package com.monitoring.optimus.rs.jni;

import android.media.audiofx.AcousticEchoCanceler;
import android.media.audiofx.AudioEffect;
import android.media.audiofx.AudioEffect.Descriptor;
import android.media.audiofx.AutomaticGainControl;
import android.media.audiofx.NoiseSuppressor;

import java.util.UUID;

import android.util.Log;

public class JniAudioEffect {
    private static final String TAG = "JniAudioEffect";
    private static Descriptor[] audio_effects_ = null;

    private AcousticEchoCanceler aec_ = null;
    private NoiseSuppressor ns_ = null;
    private AutomaticGainControl agc_ = null;

    public static boolean support_aec() {
        return effect_type_available(AudioEffect.EFFECT_TYPE_AEC);
    }

    public static boolean support_ns() {
        return effect_type_available(AudioEffect.EFFECT_TYPE_NS);
    }

    public static boolean support_agc() {
        return effect_type_available(AudioEffect.EFFECT_TYPE_AGC);
    }

    public static JniAudioEffect create() {
        return new JniAudioEffect();
    }

    public void init(int audio_record_session) {
        if (support_aec()) {
            aec_ = AcousticEchoCanceler.create(audio_record_session);
            if (aec_ != null && aec_.setEnabled(true) == AudioEffect.SUCCESS) {
                Log.e(TAG, "===sharp audio aec init success");
            } else {
                Log.e(TAG, "===sharp audio aec init failed");
            }
        } else {
            Log.e(TAG, "===sharp audio aec not support");
        }

        if (support_ns()) {
            ns_ = NoiseSuppressor.create(audio_record_session);
            if (ns_ != null && ns_.setEnabled(true) == AudioEffect.SUCCESS) {
                Log.e(TAG, "===sharp audio ns init success");
            } else {
                Log.e(TAG, "===sharp audio ns init failed");
            }
        } else {
            Log.e(TAG, "===sharp audio ns not support");
        }

        if (support_agc()) {
            agc_ = AutomaticGainControl.create(audio_record_session);
            if (agc_ != null && agc_.setEnabled(true) == AudioEffect.SUCCESS) {
                Log.e(TAG, "===sharp audio agc init success");
            } else {
                Log.e(TAG, "===sharp audio agc init failed");
            }
        } else {
            Log.e(TAG, "===sharp audio agc not support");
        }
    }

    public void uninit() {
        if (aec_ != null) {
            aec_.release();
            aec_ = null;
        }

        if (ns_ != null) {
            ns_.release();
            ns_ = null;
        }

        if (agc_ != null) {
            agc_.release();
            agc_ = null;
        }
    }

    private static Descriptor[] audio_effects() {
        if (audio_effects_ != null) {
            return audio_effects_;
        }
        audio_effects_ = AudioEffect.queryEffects();
        return audio_effects_;
    }

    private static boolean effect_type_available(UUID effect_type) {
        Descriptor[] effects = audio_effects();
        if (effects == null) {
            return false;
        }

        for (Descriptor d : effects) {
            if (d.type.equals(effect_type)) {
                return true;
            }
        }
        return false;
    }
}
