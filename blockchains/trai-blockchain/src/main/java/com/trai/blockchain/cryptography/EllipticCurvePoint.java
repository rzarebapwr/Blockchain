package com.trai.blockchain.cryptography;

import lombok.Data;

@Data
public class EllipticCurvePoint {
    private int x;
    private int y;
    private EllipticCurve ellipticCurve;

    public EllipticCurvePoint(int x, int y, EllipticCurve ellipticCurve) {
        if (!belongsToCurve(x, y, ellipticCurve))
            throw new IllegalArgumentException("Point does not belong to specified Elliptic Curve");
        this.x = x;
        this.y = y;
        this.ellipticCurve = ellipticCurve;

    }

    private boolean belongsToCurve(int x, int y, EllipticCurve ellipticCurve) {
        return Math.pow(y, 2) == Math.pow(x, 3) + ellipticCurve.a * x + ellipticCurve.b;
    }

    public boolean isEqual(EllipticCurvePoint other) {
        return x == other.getX() && y == other.getY() && ellipticCurve.isEqual(other.getEllipticCurve());
    }

    public EllipticCurvePoint add(EllipticCurvePoint other) {
        if (!ellipticCurve.isEqual(other.getEllipticCurve()))
            throw new IllegalArgumentException(
                    "Cannot add Elliptic Curve Points that do not belong to the same Elliptic Curve");

        // If p1 != p2
        if (x != other.getX()) {
            int s = (other.getY() - y) / (other.getX() - x);
            int newX = (int) (Math.pow(s, 2) - x - other.getX());
            int newY = s * (x - newX) - y;
            return new EllipticCurvePoint(newX, newY, ellipticCurve);
        }
        if (this.equals(other)) {
            int s = (int) (((3 * Math.pow(x, 2)) + ellipticCurve.a) / (2 * y));
            int newX = (int) (Math.pow(s, 2) - (2 * x));
            int newY = s * (x - newX) - y;
            return new EllipticCurvePoint(newX, newY, ellipticCurve);
        }

        else
            return this;

    }
}
