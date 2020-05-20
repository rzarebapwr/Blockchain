package com.trai.blockchain.cryptography;

import lombok.Data;

@Data
public class Point {
    private FieldElement x;
    private FieldElement y;
    private EllipticCurve ellipticCurve;

    public Point(FieldElement x, FieldElement y, EllipticCurve ellipticCurve) {
        if (!belongsToCurve(x, y, ellipticCurve))
            throw new IllegalArgumentException("Point does not belong to specified Elliptic Curve");
        this.x = x;
        this.y = y;
        this.ellipticCurve = ellipticCurve;

    }

    private boolean belongsToCurve(FieldElement x, FieldElement y, EllipticCurve ellipticCurve) {
        return y.pow(2).isEqual(x.pow(3).add(ellipticCurve.a.mul(x)).add(ellipticCurve.b));
    }

    public boolean isEqual(Point other) {
        return x.isEqual(other.getX()) && y.isEqual(other.getY()) && ellipticCurve.isEqual(other.getEllipticCurve());

    }

    public Point add(Point other) {
        if (!ellipticCurve.isEqual(other.getEllipticCurve()))
            throw new IllegalArgumentException(
                    "Cannot add Elliptic Curve Points that do not belong to the same Elliptic Curve");

        // If p1 != p2
        if (!x.isEqual(other.getX())) {
            FieldElement s = (other.getY().sub(y)).div(other.getX().sub(x));
            FieldElement newX = s.pow(2).sub(x).sub(other.getX());
            FieldElement newY = s.mul((x.sub(newX))).sub(y);
            return new Point(newX, newY, ellipticCurve);
        }
//        if (this.equals(other)) {
//            FieldElement s =
//
//            int s = (int) (((3 * Math.pow(x, 2)) + ellipticCurve.a) / (2 * y));
//            int newX = (int) (Math.pow(s, 2) - (2 * x));
//            int newY = s * (x - newX) - y;
//            return new EllipticCurvePoint(newX, newY, ellipticCurve);
//        }

        else
            return this;

    }
}
