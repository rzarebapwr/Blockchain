package com.trai.blockchain.cryptography;

import java.math.BigInteger;

public class Signature {

    public final BigInteger r;
    public final BigInteger s;

    public Signature(BigInteger r, BigInteger s) {
        this.r = r;
        this.s = s;
    }

    public String toDER() {
        /* Returns DER representation (Distinguished Encoding Rules) */
        long rLen = Math.round(r.toByteArray().length / 1.6);
        long sLen = Math.round(s.toByteArray().length / 1.6);
        String rValue = r.toString(16);
        String sValue = r.toString(16);
        if (r.toString(16).startsWith("80")) {
            rValue = "0" + rValue;
            rLen += 1;
        }
        if (s.toString(16).startsWith("80")) {
            sValue = "0" + sValue;
            sLen += 1;
        }

        long totalLen = 4 + rLen + sLen;
        return "30" + totalLen + "02" + rLen + rValue + "02" + sLen + sValue;
    }
}
