package com.trai.blockchain.cryptographyTests;

import com.trai.blockchain.cryptography.EllipticCurve;
import com.trai.blockchain.cryptography.Point;
import com.trai.blockchain.cryptography.FieldElement;
import org.junit.Test;

import java.math.BigInteger;
import java.util.Arrays;
import java.util.List;

import static org.junit.Assert.*;

public class PointTest {

    static final int prime = 223;
    static final FieldElement a = new FieldElement(0, prime);
    static final FieldElement b = new FieldElement(7, prime);
    static final EllipticCurve ellipticCurve = new EllipticCurve(a, b);

    @Test(expected = IllegalArgumentException.class)
    public void creationException() {
        // This point is does not belong to specified Elliptic Curve - Exception expected
        FieldElement x = new FieldElement(200, prime);
        FieldElement y = new FieldElement(119, prime);
        Point point = new Point(x, y, ellipticCurve);
    }

    @Test
    public void equalOperator() {
//        FieldElement x = new FieldElement(192, prime);
//        FieldElement y = new FieldElement(105, prime);

        FieldElement x = new FieldElement(BigInteger.valueOf(192), BigInteger.valueOf(prime));
        FieldElement y = new FieldElement(BigInteger.valueOf(105), BigInteger.valueOf(prime));

        Point point1 = new Point(x, y, ellipticCurve);
        Point point2 = new Point(x, y, ellipticCurve);
        assertTrue(point1.isEqual(point2));
    }

    @Test
    public void addDifferentPoints() {
        List<Point> points1 = Arrays.asList(
                new Point(new FieldElement(170, prime), new FieldElement(142, prime), ellipticCurve),
                new Point(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve),
                new Point(new FieldElement(143, prime), new FieldElement(98, prime), ellipticCurve));

        List<Point> points2 = Arrays.asList(
                new Point(new FieldElement(60, prime), new FieldElement(139, prime), ellipticCurve),
                new Point(new FieldElement(17, prime), new FieldElement(56, prime), ellipticCurve),
                new Point(new FieldElement(76, prime), new FieldElement(66, prime), ellipticCurve));

        List<Point> expectedValues = Arrays.asList(
                new Point(new FieldElement(220, prime), new FieldElement(181, prime), ellipticCurve),
                new Point(new FieldElement(215, prime), new FieldElement(68, prime), ellipticCurve),
                new Point(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve));

        for (int i=0; i<expectedValues.size(); ++i)
            assertTrue(points1.get(i).add(points2.get(i)).isEqual(expectedValues.get(i)));
    }

    @Test
    public void addSamePoints() {
        List<Point> points = Arrays.asList(
                new Point(new FieldElement(192, prime), new FieldElement(105, prime), ellipticCurve),
                new Point(new FieldElement(143, prime), new FieldElement(98, prime), ellipticCurve),
                new Point(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve));

        List<Point> expectedValues = Arrays.asList(
                new Point(new FieldElement(49, prime), new FieldElement(71, prime), ellipticCurve),
                new Point(new FieldElement(64, prime), new FieldElement(168, prime), ellipticCurve),
                new Point(new FieldElement(36, prime), new FieldElement(111, prime), ellipticCurve));

        for (int i=0; i<expectedValues.size(); ++i) {
            Point point = points.get(i);
            assertTrue(point.add(point).isEqual(expectedValues.get(i)));
        }

    }

    @Test
    public void multiply() {
        List<Point> points = Arrays.asList(
                new Point(new FieldElement(192, prime), new FieldElement(105, prime), ellipticCurve),
                new Point(new FieldElement(143, prime), new FieldElement(98, prime), ellipticCurve),
                new Point(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve),
                new Point(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve),
                new Point(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve));

        List<Integer> coefficients = Arrays.asList(2, 2, 2, 4, 8);

        List<Point> expected = Arrays.asList(
                new Point(new FieldElement(49, prime), new FieldElement(71, prime), ellipticCurve),
                new Point(new FieldElement(64, prime), new FieldElement(168, prime), ellipticCurve),
                new Point(new FieldElement(36, prime), new FieldElement(111, prime), ellipticCurve),
                new Point(new FieldElement(194, prime), new FieldElement(51, prime), ellipticCurve),
                new Point(new FieldElement(116, prime), new FieldElement(55, prime), ellipticCurve));

        for (int i=0; i<points.size(); ++i)
            assertTrue(points.get(i).mul(coefficients.get(i)).isEqual(expected.get(i)));
    }

    @Test
    public void multiplyBigNumber() {
        List<Point> points = Arrays.asList(
                new Point(new FieldElement(192, prime), new FieldElement(105, prime), ellipticCurve),
                new Point(new FieldElement(143, prime), new FieldElement(98, prime), ellipticCurve),
                new Point(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve),
                new Point(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve),
                new Point(new FieldElement(47, prime), new FieldElement(71, prime), ellipticCurve));

        List<BigInteger> coefficients = Arrays.asList(
                BigInteger.valueOf(2),
                BigInteger.valueOf(2),
                BigInteger.valueOf(2),
                BigInteger.valueOf(4),
                BigInteger.valueOf(8));

        List<Point> expected = Arrays.asList(
                new Point(new FieldElement(49, prime), new FieldElement(71, prime), ellipticCurve),
                new Point(new FieldElement(64, prime), new FieldElement(168, prime), ellipticCurve),
                new Point(new FieldElement(36, prime), new FieldElement(111, prime), ellipticCurve),
                new Point(new FieldElement(194, prime), new FieldElement(51, prime), ellipticCurve),
                new Point(new FieldElement(116, prime), new FieldElement(55, prime), ellipticCurve));

        for (int i=0; i<points.size(); ++i)
            assertTrue(points.get(i).mul(coefficients.get(i)).isEqual(expected.get(i)));
    }

}
