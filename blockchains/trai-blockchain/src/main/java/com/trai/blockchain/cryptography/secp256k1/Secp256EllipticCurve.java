package com.trai.blockchain.cryptography.secp256k1;

import com.trai.blockchain.cryptography.EllipticCurve;
import com.trai.blockchain.cryptography.FieldElement;

import java.math.BigInteger;

public class Secp256EllipticCurve extends EllipticCurve {

    static private final Secp256Element a = new Secp256Element(BigInteger.valueOf(0));
    static private final Secp256Element b = new Secp256Element(BigInteger.valueOf(7));

    public Secp256EllipticCurve() {
        super(a, b);
    }


}
