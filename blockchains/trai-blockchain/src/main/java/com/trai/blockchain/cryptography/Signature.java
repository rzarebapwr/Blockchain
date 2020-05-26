package com.trai.blockchain.cryptography;

import java.math.BigInteger;

public class Signature {

    public final BigInteger r;
    public final BigInteger s;

    public Signature(BigInteger r, BigInteger s) {
        this.r = r;
        this.s = s;
    }
}
