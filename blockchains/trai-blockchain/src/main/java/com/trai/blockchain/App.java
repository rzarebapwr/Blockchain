package com.trai.blockchain;

import com.trai.blockchain.cryptography.*;

import java.math.BigInteger;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * Hello world!
 *
 */

public class App {

    public static BigInteger sha256(String message) throws NoSuchAlgorithmException {
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hash = digest.digest(message.getBytes(StandardCharsets.UTF_8));
        return new BigInteger(hash);
    }

    public static void main(String[] args) throws NoSuchAlgorithmException {

//        String nValue = "fffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141";
//        BigInteger n = new BigInteger(nValue, 16);
//
//        BigInteger prime = BigInteger.valueOf(2).pow(256)
//                .subtract(BigInteger.valueOf(2).pow(32))
//                .subtract(BigInteger.valueOf(977));
//
//        FieldElement Gx = new FieldElement("79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798", prime);
//        FieldElement Gy = new FieldElement("483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8", prime);
//
//        FieldElement a = new FieldElement(BigInteger.valueOf(0), prime);
//        FieldElement b = new FieldElement(BigInteger.valueOf(7), prime);
//        EllipticCurve ellipticCurve = new EllipticCurve(a, b);
//        CurvePoint generatorCurvePoint = new CurvePoint(Gx, Gy, ellipticCurve);
//
//        // Sign message
//        BigInteger privateKey = sha256("fakeRandom");
//        CurvePoint publicKey = generatorCurvePoint.mul(privateKey, n);
//        BigInteger z = sha256("Message to sign");
//        BigInteger k = BigInteger.valueOf(123);
//        BigInteger r = generatorCurvePoint.mul(k).getX().getNum();
//        BigInteger kInv = k.modPow(n.subtract(BigInteger.valueOf(2)), n);
//        BigInteger s = z.add(r.multiply(privateKey)).multiply(kInv).mod(n);
//
//
//        System.out.println(z);
//        System.out.println(r);
//        System.out.println(s);
//
//        System.out.println("\nVerification:");
//
//
//        BigInteger z2 = sha256("Message to sign2");
//        BigInteger sInv = s.modPow(n.subtract(BigInteger.valueOf(2)), n);
//        BigInteger u = z2.multiply(sInv).mod(n);
//        BigInteger v = r.multiply(sInv).mod(n);
//        CurvePoint total = generatorCurvePoint.mul(u).add(publicKey.mul(v));
//        boolean verified = total.getX().getNum().equals(r);
//        System.out.println(verified);

        BigInteger privateKey = ECDSA.generatePrivateKey();
        CurvePoint publicKey = ECDSA.generatePublicKey(privateKey);
        BigInteger message = sha256("Hello");
        Signature sig = ECDSA.sign(message, privateKey);

//        System.out.println(privateKey);

        BigInteger messageToCheck = sha256("Hello");
        boolean verified = ECDSA.verify(messageToCheck, publicKey, sig);
        System.out.println(verified);









    }


}
