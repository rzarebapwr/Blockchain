package com.trai.blockchain.cryptographyTests;

import com.trai.blockchain.cryptography.EllipticCurve;
import com.trai.blockchain.cryptography.EllipticCurvePoint;
import org.junit.Test;
import static org.junit.Assert.*;

public class EllipticCurvePointTest {

    @Test(expected = IllegalArgumentException.class)
    public void creationException() {
        EllipticCurve ellipticCurve = new EllipticCurve(5, 7);
        EllipticCurvePoint ellipticCurvePoint = new EllipticCurvePoint(2, 4, ellipticCurve);
    }

    @Test
    public void equalOperator() {
        EllipticCurve ellipticCurve = new EllipticCurve(5, 7);
        EllipticCurvePoint ellipticCurvePoint1 = new EllipticCurvePoint(18, 77, ellipticCurve);
        EllipticCurvePoint ellipticCurvePoint2 = new EllipticCurvePoint(18, 77, ellipticCurve);
        assertTrue(ellipticCurvePoint1.isEqual(ellipticCurvePoint2));
    }

    @Test
    public void addOperator() {
        EllipticCurve ellipticCurve = new EllipticCurve(5, 7);
        EllipticCurvePoint ellipticCurvePoint1 = new EllipticCurvePoint(-1, 1, ellipticCurve);
        EllipticCurvePoint ellipticCurvePoint2 = new EllipticCurvePoint(-1, 1, ellipticCurve);
        EllipticCurvePoint added = ellipticCurvePoint1.add(ellipticCurvePoint2);
        assertEquals(18, added.getX());
        assertEquals(-77, added.getY());
    }

}
