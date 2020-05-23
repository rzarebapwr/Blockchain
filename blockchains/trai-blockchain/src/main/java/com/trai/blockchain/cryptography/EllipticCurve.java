package com.trai.blockchain.cryptography;


public class EllipticCurve {
    public final FieldElement a;
    public final FieldElement b;

    public EllipticCurve(FieldElement a, FieldElement b) {
        this.a = a;
        this.b = b;
    }

    public boolean isEqual(EllipticCurve other) {
        return a.isEqual(other.a) && b.isEqual(other.b);
    }

}
