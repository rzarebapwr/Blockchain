package com.trai.blockchain.cryptography;

import java.math.BigInteger;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Random;

public final class ECDSA {

    // Prime = 2^256 - 2^32 - 977
    public static final BigInteger prime = BigInteger.valueOf(2).pow(256)
            .subtract(BigInteger.valueOf(2).pow(32))
            .subtract(BigInteger.valueOf(977));

    // Secp256k1 elliptic curve
    public static final String nValue = "fffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141";
    public static final BigInteger n = new BigInteger(nValue, 16);
    public static final FieldElement a = new FieldElement(BigInteger.valueOf(0), prime);
    public static final FieldElement b = new FieldElement(BigInteger.valueOf(7), prime);
    public static final EllipticCurve ellipticCurve = new EllipticCurve(a, b);

    // Generator elliptic curve point G
    public static final FieldElement Gx = new FieldElement("79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798", prime);
    public static final FieldElement Gy = new FieldElement("483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8", prime);
    public static final CurvePoint generatorCurvePoint = new CurvePoint(Gx, Gy, ellipticCurve);


    public static BigInteger sha256(String message) throws NoSuchAlgorithmException {
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hash = digest.digest(message.getBytes(StandardCharsets.UTF_8));
        return new BigInteger(hash);
    }

    private static BigInteger generateRandomBigInteger() {
        Random rand = new Random();
        BigInteger upperLimit = n;
        BigInteger result;

        do {
            result = new BigInteger(upperLimit.bitLength(), rand);
        } while(result.compareTo(upperLimit) >= 0);

        return result;
    }

    private static BigInteger getDeterministicK(BigInteger message, BigInteger privateKey) throws NoSuchAlgorithmException {
        BigInteger messageHash = sha256(message.toString());
        BigInteger privateKeyHash = sha256(privateKey.toString());
        String combined = messageHash.add(privateKeyHash).toString();
//        return sha256(combined);
        return BigInteger.valueOf(2);
    }

    public static BigInteger generatePrivateKey() throws NoSuchAlgorithmException {
        return generateRandomBigInteger();
    }

    public static CurvePoint generatePublicKey(BigInteger privateKey) {
        return generatorCurvePoint.mul(privateKey, n);
    }

    public static Signature sign(BigInteger message, BigInteger privateKey) throws NoSuchAlgorithmException {
        BigInteger k = getDeterministicK(message, privateKey);
        BigInteger r = generatorCurvePoint.mul(k, n).getX().getNum();
        BigInteger kInv = k.modPow(n.subtract(BigInteger.valueOf(2)), n);
        BigInteger s = message.add(r.multiply(privateKey)).multiply(kInv).mod(n);
        if (s.compareTo(n.divide(BigInteger.valueOf(2))) > 0)
            s = n.subtract(s);
        return new Signature(r, s);
    }

    public static boolean verify(BigInteger message, CurvePoint publicKey, Signature sig) {
        BigInteger sInv = sig.s.modPow(n.subtract(BigInteger.valueOf(2)), n);
        BigInteger u = message.multiply(sInv).mod(n);
        BigInteger v = sig.r.multiply(sInv).mod(n);
        CurvePoint total = generatorCurvePoint.mul(u).add(publicKey.mul(v));
        return total.getX().getNum().equals(sig.r);
    }









}
