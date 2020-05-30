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

    public static CurvePoint fromSEC(String secFormat, BigInteger prime, EllipticCurve ellipticCurve) {
        boolean isCompressed = !secFormat.startsWith("04");
        int firstHalf = (secFormat.length() / 2) + 1;
        System.out.println(secFormat.length());
        FieldElement x;
        FieldElement y;

        if (!isCompressed) {
            x = new FieldElement(secFormat.substring(2, firstHalf), prime);
            y = new FieldElement(secFormat.substring(firstHalf), prime);
            return new CurvePoint(x, y, ellipticCurve);
        }
        boolean isEven = secFormat.startsWith("02");
        x = new FieldElement(new BigInteger(secFormat.substring(2), 16), prime);
        // alpha = x^3 + b
        FieldElement alpha = x.pow(3).add(new FieldElement(ellipticCurve.b.getNum(), prime));
        FieldElement beta = alpha.sqrt();
        FieldElement evenBeta;
        FieldElement oddBeta;

        if (beta.getNum().mod(BigInteger.valueOf(2)).equals(BigInteger.ZERO)) {
            evenBeta = beta;
            oddBeta = new FieldElement(prime.subtract(beta.getNum()), prime);
        } else {
            evenBeta = new FieldElement(prime.subtract(beta.getNum()), prime);
            oddBeta = beta;
        }

        if (isEven)
            return new CurvePoint(x, evenBeta, ellipticCurve);
        else
            return new CurvePoint(x, oddBeta, ellipticCurve);
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
        /* for better efficiency if order of field 'n' is known */
        coefficient = coefficient.mod(n);
        return mul(coefficient);
    }

    public String toSEC() {
        return "04" + x.getNum().toString(16) + y.getNum().toString(16);
    }

    public String toCompressedSEC() {
        String prefix;
        if (y.getNum().mod(BigInteger.valueOf(2)).equals(BigInteger.ZERO))
            prefix = "02";
        else
            prefix = "03";
        return prefix + x.getNum().toString(16);

    }



}
