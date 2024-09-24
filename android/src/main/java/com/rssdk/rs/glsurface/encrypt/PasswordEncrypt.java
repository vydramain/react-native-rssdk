package com.monitoring.optimus.rs.glsurface.encrypt;

import android.util.Base64;

import com.rs.network.rs.base.BaseEncPassword;

import org.bouncycastle.crypto.AsymmetricCipherKeyPair;
import org.bouncycastle.crypto.AsymmetricCipherKeyPairGenerator;
import org.bouncycastle.crypto.Digest;
import org.bouncycastle.crypto.InvalidCipherTextException;
import org.bouncycastle.crypto.agreement.X25519Agreement;
import org.bouncycastle.crypto.digests.SHA256Digest;
import org.bouncycastle.crypto.engines.AESEngine;
import org.bouncycastle.crypto.generators.HKDFBytesGenerator;
import org.bouncycastle.crypto.generators.PKCS5S2ParametersGenerator;
import org.bouncycastle.crypto.generators.X25519KeyPairGenerator;
import org.bouncycastle.crypto.modes.GCMBlockCipher;
import org.bouncycastle.crypto.modes.gcm.Tables4kGCMMultiplier;
import org.bouncycastle.crypto.params.AEADParameters;
import org.bouncycastle.crypto.params.AsymmetricKeyParameter;
import org.bouncycastle.crypto.params.HKDFParameters;
import org.bouncycastle.crypto.params.KeyParameter;
import org.bouncycastle.crypto.params.X25519KeyGenerationParameters;
import org.bouncycastle.crypto.params.X25519PublicKeyParameters;

import java.io.IOException;
import java.security.SecureRandom;

/**
 * Copyright (c) 2021 Raysharp.cn. All rights reserved.
 * <p>
 * TestEncrypt
 *
 * @author Liang Jingyan
 * @date 2021-10-21
 */
public class PasswordEncrypt {

    private static final SecureRandom RANDOM = new SecureRandom();


    public static byte[] pbkdf2(String password, byte[] salt, int iterations, int keyLength) {

        PKCS5S2ParametersGenerator gen = new PKCS5S2ParametersGenerator(new SHA256Digest());
        byte[] secretData = password.getBytes();
        gen.init(secretData, salt, iterations);
        byte[] derivedKey = ((KeyParameter) gen.generateDerivedParameters(keyLength * 8)).getKey();
        return derivedKey;
    }


    public static AsymmetricCipherKeyPair generateKeyPair() {
        AsymmetricCipherKeyPairGenerator kpGen = new X25519KeyPairGenerator();
        kpGen.init(new X25519KeyGenerationParameters(RANDOM));
        return kpGen.generateKeyPair();
    }


    public static byte[] generateShareSecret(byte[] pubKey, AsymmetricCipherKeyPair kp) {
        AsymmetricKeyParameter kB = new X25519PublicKeyParameters(pubKey, 0);

        X25519Agreement agree = new X25519Agreement();
        agree.init(kp.getPrivate());
        byte[] secret = new byte[agree.getAgreementSize()];
        agree.calculateAgreement(kB, secret, 0);

        return secret;
    }


    public static byte[] hkdfExpand(byte[] ikm, byte[] salt, byte[] info, int l) {

        Digest hash = new SHA256Digest();
        byte[] okm = new byte[l];

        HKDFParameters params = HKDFParameters.skipExtractParameters(ikm, info);

        HKDFBytesGenerator hkdf = new HKDFBytesGenerator(hash);
        hkdf.init(params);
        hkdf.generateBytes(okm, 0, l);

        return okm;
    }


    public static CryptWrapper aesGcm(byte[] key, byte[] iv, byte[] plainText) throws InvalidCipherTextException {

        Tables4kGCMMultiplier m = new Tables4kGCMMultiplier();
        AEADParameters parameters = new AEADParameters(new KeyParameter(key), 16 * 8, iv);

        GCMBlockCipher cipher = new GCMBlockCipher(new AESEngine(), m);
        cipher.init(true, parameters);

        byte[] c = new byte[cipher.getOutputSize(plainText.length)];

        cipher.processBytes(plainText, 0, plainText.length, c, 0);
        cipher.doFinal(c, 0);

        // tag
        byte[] mac = cipher.getMac();

        byte[] macOut = new byte[mac.length];
        System.arraycopy(mac, 0, macOut, 0, mac.length);
        CryptWrapper wrapper = new CryptWrapper();
        wrapper.setCipher(c);
        wrapper.setMac(macOut);
        return wrapper;
    }

    public static class CryptWrapper {

        private byte[] cipher;

        private byte[] mac;

        public byte[] getCipher() {
            return cipher;
        }

        public void setCipher(byte[] cipher) {
            this.cipher = cipher;
        }

        public byte[] getMac() {
            return mac;
        }

        public void setMac(byte[] mac) {
            this.mac = mac;
        }
    }


    public static synchronized BaseEncPassword encPassword(String fristLoginKey, int seq, String pwd) {
        AsymmetricCipherKeyPair asymmetricCipherKeyPair = PasswordEncrypt.generateKeyPair();
        String substring = fristLoginKey.substring(1);
        byte[] decode = Base64.decode(substring, Base64.NO_WRAP);
        byte[] pubKey = PasswordEncrypt.generateShareSecret(decode, asymmetricCipherKeyPair);
        String expandKey = "expand key";
        String expandIv = "expand iv";
        byte[] expandKeys = PasswordEncrypt.hkdfExpand(pubKey, null, expandKey.getBytes(), 32);
        byte[] expandIvs = PasswordEncrypt.hkdfExpand(pubKey, null, expandIv.getBytes(), 12);
        CryptWrapper cryptWrapper = null;
        try {
            cryptWrapper = PasswordEncrypt.aesGcm(expandKeys, expandIvs, pwd.getBytes());
        } catch (InvalidCipherTextException e) {
            e.printStackTrace();
        }

        String cipher = null;
        String peerkey = null;
        byte[] cipher1 = cryptWrapper.getCipher();
        byte[] mac = cryptWrapper.getMac();
        byte[] result = removeRepeat(cipher1,mac);
        byte[] bytes = addBytes(addBytes(result, expandIvs), mac);
        AsymmetricKeyParameter aPublic = asymmetricCipherKeyPair.getPublic();
        cipher = Base64.encodeToString(bytes, Base64.NO_WRAP);
        peerkey = Base64.encodeToString(((X25519PublicKeyParameters)aPublic).getEncoded(), Base64.NO_WRAP);

        BaseEncPassword baseEncPassword = new BaseEncPassword();
        baseEncPassword.cipher = "0"+cipher;
        baseEncPassword.peerKey = "0"+peerkey;
        baseEncPassword.seq = seq;
        return baseEncPassword;
    }

    public static byte[] removeRepeat(byte[] cipher1, byte[] mac) {
        if(mac.length > cipher1.length){
            return null;
        }

        byte[] bytes = new byte[cipher1.length - mac.length];
        for(int i = 0; i < bytes.length; ++i){
            bytes[i] = cipher1[i];
        }
        return bytes;
    }

    public static byte[] addBytes(byte[] data1, byte[] data2) {
        byte[] data3 = new byte[data1.length + data2.length];

        System.arraycopy(data1, 0, data3, 0, data1.length);

        System.arraycopy(data2, 0, data3, data1.length, data2.length);

        return data3;

    }


    public static BaseEncPassword encryptPassword(String b64xKeyWith0, String password, int seq) throws InvalidCipherTextException, IOException {
        String b64xKey = b64xKeyWith0.substring(1);
        AsymmetricCipherKeyPair keyPair = generateKeyPair();
        X25519PublicKeyParameters publicKeyParameters = (X25519PublicKeyParameters) keyPair.getPublic();
        String peerKey = "0" + com.monitoring.optimus.rs.glsurface.encrypt.Base64.encodeBytes(publicKeyParameters.getEncoded());
        byte[] shareSecret = generateShareSecret(com.monitoring.optimus.rs.glsurface.encrypt.Base64.decode(b64xKey), keyPair);
        String expKey = "expand key";
        String expIv = "expand iv";

        byte[] expandKey = hkdfExpand(shareSecret, null, expKey.getBytes(), 32);
        byte[] expandIv = hkdfExpand(shareSecret, null, expIv.getBytes(), 12);

        CryptWrapper wrapper = aesGcm(expandKey, expandIv, password.getBytes());
        byte[] mac = wrapper.getMac();
        byte[] cryptOut = wrapper.getCipher();

        byte[] result = new byte[cryptOut.length + expandIv.length];
        System.arraycopy(cryptOut, 0, result, 0, cryptOut.length - mac.length);
        System.arraycopy(expandIv, 0, result, cryptOut.length - mac.length, expandIv.length);
        System.arraycopy(mac, 0, result, cryptOut.length - mac.length + expandIv.length, mac.length);

        String cipher = "0" + com.monitoring.optimus.rs.glsurface.encrypt.Base64.encodeBytes(result);

        BaseEncPassword baseEncPassword = new BaseEncPassword();
        baseEncPassword.cipher = cipher;
        baseEncPassword.peerKey = peerKey;
        baseEncPassword.seq = seq;
        return baseEncPassword;
    }
}
