package com.monitoring.optimus.rs.glsurface.encrypt.exception;

public class AesException extends BaseException {
    public static String EncryptAESError = "encrypt AES error";
    public static String DecryptAESError = "decrypt AES error";

    public AesException() {
        super();
    }

    public AesException(String detailMessage) {
        super(detailMessage);
    }
}
