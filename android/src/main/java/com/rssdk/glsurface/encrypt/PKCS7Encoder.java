/**
 *
 * @copyright Copyright (c) 1998-2014 Tencent Inc.
 */

// ------------------------------------------------------------------------

package com.rssdk.glsurface.encrypt;

import java.nio.charset.Charset;
import java.util.Arrays;

/**
 */
class PKCS7Encoder {
    private static Charset CHARSET = Charset.forName("utf-8");
    private static int BLOCK_SIZE = 16;

    static byte[] encode(int count) {
        int amountToPad = BLOCK_SIZE - (count % BLOCK_SIZE);
        if (amountToPad == 0) {
            amountToPad = BLOCK_SIZE;
        }
        char padChr = chr(amountToPad);
        StringBuilder tmp = new StringBuilder();
        for (int index = 0; index < amountToPad; index++) {
            tmp.append(padChr);
        }
        return tmp.toString().getBytes(CHARSET);
    }

    static byte[] decode(byte[] decrypted) {
        int pad = (int) decrypted[decrypted.length - 1];
        if (pad < 1 || pad > 16) {
            pad = 0;
        }
        return Arrays.copyOfRange(decrypted, 0, decrypted.length - pad);
    }

    private static char chr(int a) {
        byte target = (byte) (a & 0xFF);
        return (char) target;
    }
}
