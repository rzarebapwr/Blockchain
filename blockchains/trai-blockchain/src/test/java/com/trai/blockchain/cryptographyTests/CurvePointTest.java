package com.trai.blockchain.cryptographyTests;

import com.trai.blockchain.cryptography.EllipticCurve;
import com.trai.blockchain.cryptography.CurvePoint;
import com.trai.blockchain.cryptography.FieldElement;
import org.junit.Test;

import java.math.BigInteger;
import java.util.Arrays;
import java.util.List;

import static org.junit.Assert.*;

public class CurvePointTest {

    static final int prime = 223;
    static final FieldElement a = new FieldElement(0, prime);
    static final FieldElement b = new FieldElement(7, prime);
    static final EllipticCurve ellipticCurve = new EllipticCurve(a, b);

    @Test(expected = IllegalArgumentException.class)
    public void creationException() {
        // This point is does not belong to specified Elliptic Curve - Exception expected
        FieldElement x = new FieldElement(200, prime);
        FieldElement y = new FieldElement(119, prime);
        CurvePoint curvePoint = new CurvePoint(x, y, ellipticCurve);
    }

    @Test
    public void equalOperator() {
//        FieldElement x = new FieldElement(192, prime);
//        FieldElement y = new FieldElement(105, prime);

        FieldElement x = new FieldElement(BigInteger.valueOf(192), BigInteger.valueOf(prime));
        FieldElement y = new FieldElement(BigInteger.valueOf(105), BigInteger.valueOf(prime));

        CurvePoint curvePoint1 = new CurvePoint(x, y, ellipticCurve);
        CurvePoint curvePoint2 = new CurvePoint(x, y, ellipticCurve);
        assertTrue(curvePoint1.isEqual(curvePoint2));
    }

    @Test
    public void addDifferentPoints() {
        List<CurvePoint> points1 = Arrays.asList(
                new CurvePoint(new FieldElement(170, prime), new FieldElement(142, prime), ellipticCurve),
                new CurvePoint(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve),
                new CurvePoint(new FieldElement(143, prime), new FieldElement(98, prime), ellipticCurve));

        List<CurvePoint> points2 = Arrays.asList(
                new CurvePoint(new FieldElement(60, prime), new FieldElement(139, prime), ellipticCurve),
                new CurvePoint(new FieldElement(17, prime), new FieldElement(56, prime), ellipticCurve),
                new CurvePoint(new FieldElement(76, prime), new FieldElement(66, prime), ellipticCurve));

        List<CurvePoint> expectedValues = Arrays.asList(
                new CurvePoint(new FieldElement(220, prime), new FieldElement(181, prime), ellipticCurve),
                new CurvePoint(new FieldElement(215, prime), new FieldElement(68, prime), ellipticCurve),
                new CurvePoint(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve));

        for (int i=0; i<expectedValues.size(); ++i)
            assertTrue(points1.get(i).add(points2.get(i)).isEqual(expectedValues.get(i)));
    }

    @Test
    public void addSamePoints() {
        List<CurvePoint> curvePoints = Arrays.asList(
                new CurvePoint(new FieldElement(192, prime), new FieldElement(105, prime), ellipticCurve),
                new CurvePoint(new FieldElement(143, prime), new FieldElement(98, prime), ellipticCurve),
                new CurvePoint(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve));

        List<CurvePoint> expectedValues = Arrays.asList(
                new CurvePoint(new FieldElement(49, prime), new FieldElement(71, prime), ellipticCurve),
                new CurvePoint(new FieldElement(64, prime), new FieldElement(168, prime), ellipticCurve),
                new CurvePoint(new FieldElement(36, prime), new FieldElement(111, prime), ellipticCurve));

        for (int i=0; i<expectedValues.size(); ++i) {
            CurvePoint curvePoint = curvePoints.get(i);
            assertTrue(curvePoint.add(curvePoint).isEqual(expectedValues.get(i)));
        }

    }

    @Test
    public void multiply() {
        List<CurvePoint> curvePoints = Arrays.asList(
                new CurvePoint(new FieldElement(192, prime), new FieldElement(105, prime), ellipticCurve),
                new CurvePoint(new FieldElement(143, prime), new FieldElement(98, prime), ellipticCurve),
                new CurvePoint(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve),
                new CurvePoint(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve),
                new CurvePoint(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve));

        List<Integer> coefficients = Arrays.asList(2, 2, 2, 4, 8);

        List<CurvePoint> expected = Arrays.asList(
                new CurvePoint(new FieldElement(49, prime), new FieldElement(71, prime), ellipticCurve),
                new CurvePoint(new FieldElement(64, prime), new FieldElement(168, prime), ellipticCurve),
                new CurvePoint(new FieldElement(36, prime), new FieldElement(111, prime), ellipticCurve),
                new CurvePoint(new FieldElement(194, prime), new FieldElement(51, prime), ellipticCurve),
                new CurvePoint(new FieldElement(116, prime), new FieldElement(55, prime), ellipticCurve));

        for (int i = 0; i< curvePoints.size(); ++i)
            assertTrue(curvePoints.get(i).mul(coefficients.get(i)).isEqual(expected.get(i)));
    }

    @Test
    public void multiplyBigNumbers() {
        List<CurvePoint> curvePoints = Arrays.asList(
                new CurvePoint(new FieldElement(192, prime), new FieldElement(105, prime), ellipticCurve),
                new CurvePoint(new FieldElement(143, prime), new FieldElement(98, prime), ellipticCurve),
                new CurvePoint(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve),
                new CurvePoint(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve),
                new CurvePoint(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve));

        List<BigInteger> coefficients = Arrays.asList(
                BigInteger.valueOf(2),
                BigInteger.valueOf(2),
                BigInteger.valueOf(2),
                BigInteger.valueOf(4),
                BigInteger.valueOf(8));

        List<CurvePoint> expected = Arrays.asList(
                new CurvePoint(new FieldElement(49, prime), new FieldElement(71, prime), ellipticCurve),
                new CurvePoint(new FieldElement(64, prime), new FieldElement(168, prime), ellipticCurve),
                new CurvePoint(new FieldElement(36, prime), new FieldElement(111, prime), ellipticCurve),
                new CurvePoint(new FieldElement(194, prime), new FieldElement(51, prime), ellipticCurve),
                new CurvePoint(new FieldElement(116, prime), new FieldElement(55, prime), ellipticCurve));

        for (int i = 0; i< curvePoints.size(); ++i)
            assertTrue(curvePoints.get(i).mul(coefficients.get(i)).isEqual(expected.get(i)));
    }

}
