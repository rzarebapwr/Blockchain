package com.trai.blockchain;

import com.trai.blockchain.cryptography.EllipticCurve;
import com.trai.blockchain.cryptography.Point;
import com.trai.blockchain.cryptography.FieldElement;

/**
 * Hello world!
 *
 */

public class App {
    public static void main(String[] args) {

        int prime = 223;
        FieldElement a = new FieldElement(0, prime);
        FieldElement b = new FieldElement(7, prime);
        FieldElement x = new FieldElement(192, prime);
        FieldElement y = new FieldElement(105, prime);

        EllipticCurve ellipticCurve = new EllipticCurve(a, b);
        Point point = new Point(x, y, ellipticCurve);

    }
}
