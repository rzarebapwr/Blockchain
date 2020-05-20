package com.trai.blockchain.cryptography;

public class EllipticCurve {
    public final int a;
    public final int b;

    public EllipticCurve(int a, int b) {
        this.a = a;
        this.b = b;
    }

    public boolean isEqual(EllipticCurve other) {
        return a == other.a && b == other.b;
    }
}
