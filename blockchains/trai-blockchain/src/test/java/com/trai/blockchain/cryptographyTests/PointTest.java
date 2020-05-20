package com.trai.blockchain.cryptographyTests;

import com.trai.blockchain.cryptography.EllipticCurve;
import com.trai.blockchain.cryptography.Point;
import com.trai.blockchain.cryptography.FieldElement;
import org.junit.Test;
import static org.junit.Assert.*;

public class PointTest {

    static final int prime = 223;


    @Test(expected = IllegalArgumentException.class)
    public void creationException() {
        // This point is does not belong to specified Elliptic Curve - Exception expected
        FieldElement a = new FieldElement(0, prime);
        FieldElement b = new FieldElement(7, prime);
        FieldElement x = new FieldElement(200, prime);
        FieldElement y = new FieldElement(119, prime);

        EllipticCurve ellipticCurve = new EllipticCurve(a, b);
        Point point = new Point(x, y, ellipticCurve);
    }

    @Test
    public void equalOperator() {
        FieldElement a = new FieldElement(0, prime);
        FieldElement b = new FieldElement(7, prime);
        EllipticCurve ellipticCurve = new EllipticCurve(a, b);

        FieldElement x = new FieldElement(192, prime);
        FieldElement y = new FieldElement(105, prime);

        Point point1 = new Point(x, y, ellipticCurve);
        Point point2 = new Point(x, y, ellipticCurve);
        assertTrue(point1.isEqual(point2));
    }

    @Test
    public void addOperator() {
        FieldElement a = new FieldElement(0, prime);
        FieldElement b = new FieldElement(7, prime);
        EllipticCurve ellipticCurve = new EllipticCurve(a, b);

        FieldElement x1 = new FieldElement(170, prime);
        FieldElement y1 = new FieldElement(142, prime);
        Point point1 = new Point(x1, y1, ellipticCurve);

        FieldElement x2 = new FieldElement(60, prime);
        FieldElement y2 = new FieldElement(139, prime);
        Point point2 = new Point(x2, y2, ellipticCurve);
//
        Point added1 = point1.add(point2);

//        EllipticCurvePoint ellipticCurvePoint3 = new EllipticCurvePoint(2, 5, ellipticCurve);
//        EllipticCurvePoint ellipticCurvePoint4 = new EllipticCurvePoint(-1, -1, ellipticCurve);
//        EllipticCurvePoint added2 = ellipticCurvePoint3.add(ellipticCurvePoint4);

//        System.out.println(added1);

//        assertEquals(new FieldElement(200, prime), added1.getX());
//        assertEquals(new FieldElement(181, prime), added1.getY());
//        assertEquals(3, added2.getX());
//        assertEquals(-7, added2.getY());
    }

}
