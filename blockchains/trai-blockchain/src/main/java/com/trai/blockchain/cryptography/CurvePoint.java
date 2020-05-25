package com.trai.blockchain.cryptography;

import lombok.Data;

import java.math.BigInteger;

@Data
public class CurvePoint {
    private FieldElement x;
    private FieldElement y;
    private EllipticCurve ellipticCurve;

    public CurvePoint(FieldElement x, FieldElement y, EllipticCurve ellipticCurve) {
        if (!belongsToCurve(x, y, ellipticCurve))
            throw new IllegalArgumentException("Point does not belong to specified Elliptic Curve");
        this.x = x;
        this.y = y;
        this.ellipticCurve = ellipticCurve;

    }

    private boolean belongsToCurve(FieldElement x, FieldElement y, EllipticCurve ellipticCurve) {
        return y.pow(2).isEqual(x.pow(3).add(ellipticCurve.a.mul(x)).add(ellipticCurve.b));
    }

    public boolean isEqual(CurvePoint other) {
        return x.isEqual(other.getX()) && y.isEqual(other.getY()) && ellipticCurve.isEqual(other.getEllipticCurve());

    }

    public CurvePoint add(CurvePoint other) {
        if (!ellipticCurve.isEqual(other.getEllipticCurve()))
            throw new IllegalArgumentException(
                    "Cannot add Elliptic Curve Points that do not belong to the same Elliptic Curve");

        // If p1 != p2
        if (!x.isEqual(other.getX())) {
            FieldElement s = (other.getY().sub(y)).div(other.getX().sub(x));
            FieldElement newX = s.pow(2).sub(x).sub(other.getX());
            FieldElement newY = s.mul((x.sub(newX))).sub(y);
            return new CurvePoint(newX, newY, ellipticCurve);
        }
        // If p1 == p2
        if (this.equals(other)) {
            FieldElement s = (x.pow(2).mul(3).add(ellipticCurve.a)).div(y.mul(2));
            FieldElement newX = s.pow(2).sub(x.mul(2));
            FieldElement newY = s.mul(x.sub(newX)).sub(y);
            return new CurvePoint(newX, newY, ellipticCurve);
        }

        else
            return this;

    }

    public CurvePoint mul(int coefficient) {
        int coef = coefficient-1;
        CurvePoint current = this;
        CurvePoint result = this;

        while (coef != 0) {
            if ((coef & 1) == 1)
                result = result.add(current);
            current = current.add(current);
            coef >>= 1;
        }
        return result;
    }

    public CurvePoint mul(BigInteger coefficient) {
        BigInteger coef = coefficient.subtract(BigInteger.ONE);
        CurvePoint current = this;
        CurvePoint result = this;

        while (coef.compareTo(BigInteger.ZERO) != 0) {
            if (coef.and(BigInteger.ONE).compareTo(BigInteger.ONE) == 0)
                result = result.add(current);
            current = current.add(current);
            coef = coef.shiftRight(1);
        }
        return result;
    }

    public CurvePoint mul(BigInteger coefficient, BigInteger n) {
        /* for better efficiency if order of field n is known */
        coefficient = coefficient.mod(n);
        return mul(coefficient);
    }



}
