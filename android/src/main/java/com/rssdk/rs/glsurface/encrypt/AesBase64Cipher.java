package com.monitoring.optimus.rs.glsurface.encrypt;

import android.util.Base64;

import com.monitoring.optimus.rs.glsurface.encrypt.exception.AesException;

import java.nio.ByteBuffer;
import java.nio.charset.Charset;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;


public class AesBase64Cipher {
    private static final String ALGORITHM = "AES/CBC/NoPadding";
    private static Charset CHARSET = Charset.forName("UTF-8");

    public static String encrypt(String msg, String encodingAesKey) throws AesException {
        try {
            byte[] key = createSecretKeyBytes(encodingAesKey);
            Cipher cipher = Cipher.getInstance(ALGORITHM);
            SecretKeySpec keySpec = new SecretKeySpec(key, "AES");
            IvParameterSpec iv = new IvParameterSpec(key, 0, 16);
            cipher.init(Cipher.ENCRYPT_MODE, keySpec, iv);

            byte[] source = msg.getBytes(CHARSET);
            byte[] padBytes = PKCS7Encoder.encode(source.length);

            ByteBuffer buf = ByteBuffer.allocate(source.length + padBytes.length);
            buf.put(source).put(padBytes);

            byte[] resultBytes = cipher.doFinal(buf.array());

            return Base64.encodeToString(resultBytes, Base64.DEFAULT);
        } catch (Exception e) {
            e.printStackTrace();
            throw new AesException(AesException.EncryptAESError);
        }
    }

    public static String decrypt(String encodeEncryptMsg, String encodingAesKey) throws AesException {
        try {

            byte[] raw = createSecretKeyBytes(encodingAesKey);
            SecretKeySpec skeySpec = new SecretKeySpec(raw, "AES");
            Cipher c = Cipher.getInstance(ALGORITHM);
            IvParameterSpec iv = new IvParameterSpec(raw, 0, 16);
            c.init(Cipher.DECRYPT_MODE, skeySpec, iv);

            byte[] decodeEncryptMsg = Base64.decode(encodeEncryptMsg, Base64.DEFAULT);
            byte[] resultBytes = c.doFinal(decodeEncryptMsg);

            byte[] removedPadBytes = PKCS7Encoder.decode(resultBytes);

            return new String(removedPadBytes, CHARSET);
        } catch (Exception e) {
            e.printStackTrace();
            throw new AesException(AesException.DecryptAESError);
        }
    }

    private static byte[] createSecretKeyBytes(String encodingAesKey) throws AesException {
        return Base64.decode(encodingAesKey, Base64.DEFAULT);
    }
}
