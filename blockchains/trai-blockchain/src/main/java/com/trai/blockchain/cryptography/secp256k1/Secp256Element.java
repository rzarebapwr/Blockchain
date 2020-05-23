package com.trai.blockchain.cryptography.secp256k1;

import com.trai.blockchain.cryptography.FieldElement;

import java.math.BigInteger;

public class Secp256Element extends FieldElement {

    // Secp256k1 prime = 2^256 - 2^32 - 977
    static private final BigInteger prime = BigInteger.valueOf(2).pow(256)
            .subtract(BigInteger.valueOf(2).pow(32))
            .subtract(BigInteger.valueOf(977));

    public Secp256Element(BigInteger num) {
        super(num, prime);
    }

    public Secp256Element(String hexNum) {
        super(hexNum, prime);
    }
}
