package com.monitoring.optimus.rs.glsurface.encrypt;

import java.math.BigInteger;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.KeySpec;

import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;


public class PasswordEncryption {

    private static String hexStr =  "0123456789ABCDEF";


    public static final String PBKDF2_ALGORITHM = "PBKDF2WithHmacSHA256";


    public static final int SALT_BYTE_SIZE = 32 / 2;


    public static final int HASH_BIT_SIZE = 128 * 2;


    public static final int PBKDF2_ITERATIONS = 10086;


    public static byte[] getEncryptedPassword(String password, byte[] salt, int iterations) throws NoSuchAlgorithmException,
            InvalidKeySpecException {
        char[] chars = password.toCharArray();
        KeySpec spec = new PBEKeySpec(chars, salt, iterations, HASH_BIT_SIZE);
        SecretKeyFactory f = SecretKeyFactory.getInstance(PBKDF2_ALGORITHM);
        return f.generateSecret(spec).getEncoded();
    }


    public static String generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = SecureRandom.getInstance("SHA1PRNG");
        byte[] salt = new byte[SALT_BYTE_SIZE];
        random.nextBytes(salt);

        return toHex(salt);
    }


    private static byte[] fromHex(String hex) {
        byte[] binary = new byte[hex.length() / 2];
        for (int i = 0; i < binary.length; i++) {
            binary[i] = (byte) Integer.parseInt(hex.substring(2 * i, 2 * i + 2), 16);
        }
        return binary;
    }


    private static String toHex(byte[] array) {
        BigInteger bi = new BigInteger(1, array);
        String hex = bi.toString(16);
        int paddingLength = (array.length * 2) - hex.length();
        if (paddingLength > 0) {

            return String.format("%0" + paddingLength + "d", 0) + hex;
        } else {
            return hex;
        }
    }


    public static String bin2HexStr(byte[] bytes){

        String result = "";
        String hex = "";
        for(int i=0;i<bytes.length;i++){
            hex = String.valueOf(hexStr.charAt((bytes[i]&0xF0)>>4));
            hex += String.valueOf(hexStr.charAt(bytes[i]&0x0F));
            result +=hex;  //+" "
        }
        return result;
    }


}
