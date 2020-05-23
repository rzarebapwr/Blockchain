package com.trai.blockchain;

import com.trai.blockchain.cryptography.EllipticCurve;
import com.trai.blockchain.cryptography.Point;
import com.trai.blockchain.cryptography.FieldElement;
import com.trai.blockchain.cryptography.secp256k1.Secp256Element;
import com.trai.blockchain.cryptography.secp256k1.Secp256EllipticCurve;
import com.trai.blockchain.cryptography.secp256k1.Secp256Point;

import java.math.BigInteger;

/**
 * Hello world!
 *
 */

public class App {
    public static void main(String[] args) {

//        long startTime = System.nanoTime();
//        long stopTime = System.nanoTime();
//        System.out.println(String.format("Classic for loop took %d", stopTime - startTime));



//        Secp256Element Gx = new Secp256Element("79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798");
//        Secp256Element Gy = new Secp256Element("483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8");
//        Secp256Point generatorPoint = new Secp256Point(Gx, Gy);

        BigInteger prime = BigInteger.valueOf(2).pow(256)
                .subtract(BigInteger.valueOf(2).pow(32))
                .subtract(BigInteger.valueOf(977));

        FieldElement Gx = new FieldElement("79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798", prime);
        FieldElement Gy = new FieldElement("483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8", prime);

        FieldElement a = new FieldElement(BigInteger.valueOf(0), prime);
        FieldElement b = new FieldElement(BigInteger.valueOf(7), prime);
        EllipticCurve ellipticCurve = new EllipticCurve(a, b);

        Point generatorPoint = new Point(Gx, Gy, ellipticCurve);
//        Point publicKey = generatorPoint.mul(BigInteger.valueOf(10));

        Point added = generatorPoint.add(generatorPoint);

        BigInteger privateKey = BigInteger.valueOf(12311);

        long startTime = System.nanoTime();
        Point publicKey2 = generatorPoint.mul(privateKey);
        long stopTime = System.nanoTime();
        System.out.println(String.format("Iteration took %d", stopTime - startTime));

        long startTime2 = System.nanoTime();
        Point publicKey22 = generatorPoint.rmul(privateKey);
        long stopTime2 = System.nanoTime();
        System.out.println(String.format("Iteration took %d", stopTime2 - startTime2));


//        Point publicKey = generatorPoint.rmul(privateKey);
//        System.out.println(publicKey.isEqual(publicKey2));

//


    }
}
