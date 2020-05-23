package com.trai.blockchain.cryptography.secp256k1;

import com.trai.blockchain.cryptography.Point;

import java.math.BigInteger;

public class Secp256Point extends Point {

    private String nValue = "fffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141";
    private BigInteger n = new BigInteger(nValue, 16);

    public Secp256Point(Secp256Element x, Secp256Element y) {
        super(x, y, new Secp256EllipticCurve());
    }

    @Override
    public Secp256Point mul(BigInteger coefficient) {
        BigInteger coeff = coefficient.mod(n);
        Point result = super.mul(coeff);
        Secp256Element resultX = new Secp256Element(result.getX().getNum());
        Secp256Element resultY = new Secp256Element(result.getY().getNum());
        return new Secp256Point(resultX, resultY);
    }
}
