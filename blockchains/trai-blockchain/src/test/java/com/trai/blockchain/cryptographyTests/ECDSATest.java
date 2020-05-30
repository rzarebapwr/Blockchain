package com.trai.blockchain.cryptographyTests;

import com.trai.blockchain.cryptography.CurvePoint;
import com.trai.blockchain.cryptography.ECDSA;
import com.trai.blockchain.cryptography.Signature;
import org.junit.Test;

import java.math.BigInteger;
import java.security.NoSuchAlgorithmException;

import static org.junit.Assert.*;

public class ECDSATest {


    @Test
    public void generatePrivateKey() throws NoSuchAlgorithmException {
        BigInteger privateKey = ECDSA.generatePrivateKey();
        assertEquals(privateKey.toString(16).length(), 64);
    }

    @Test
    public void signAndVerify() throws NoSuchAlgorithmException {
        BigInteger message = ECDSA.sha256("Hello");
        BigInteger message2 = ECDSA.sha256("Hello2");

        BigInteger privateKey = ECDSA.generatePrivateKey();
        BigInteger privateKey2 = ECDSA.generatePrivateKey();

        CurvePoint publicKey = ECDSA.generatePublicKey(privateKey);
        CurvePoint publicKey2 = ECDSA.generatePublicKey(privateKey2);

        Signature sig = ECDSA.sign(message, privateKey);
        Signature sig2 = ECDSA.sign(message2, privateKey2);

        boolean verified = ECDSA.verify(message, publicKey, sig);
        boolean verified2 = ECDSA.verify(message2, publicKey2, sig2);
        boolean notVerified = ECDSA.verify(message2, publicKey, sig);
        boolean notVerified2 = ECDSA.verify(message, publicKey2, sig);
        boolean notVerified3 = ECDSA.verify(message, publicKey, sig2);
        boolean notVerified4 = ECDSA.verify(message, publicKey2, sig2);

        assertTrue(verified);
        assertTrue(verified2);
        assertFalse(notVerified);
        assertFalse(notVerified2);
        assertFalse(notVerified3);
        assertFalse(notVerified4);
    }

    @Test
    public void publicKeyToSEC() {
        BigInteger privateKey = ECDSA.generatePrivateKey();
        CurvePoint publicKey = ECDSA.generatePublicKey(privateKey);
        String sec = publicKey.toSEC();
        assertTrue(sec.startsWith("04"));
    }

    @Test
    public void publicKeyToCompressedSEC() {
        BigInteger privateKey = ECDSA.generatePrivateKey();
        CurvePoint publicKey = ECDSA.generatePublicKey(privateKey);
        String sec = publicKey.toCompressedSEC();
        assertTrue(sec.startsWith("02") || sec.startsWith("03"));
    }

    @Test
    public void publicKeyFromSEC() {
        BigInteger privateKey = ECDSA.generatePrivateKey();
        CurvePoint publicKey = ECDSA.generatePublicKey(privateKey);
        String sec = publicKey.toSEC();
        String compressedSec = publicKey.toCompressedSEC();

        CurvePoint publicKeyFromSec = ECDSA.generatePublicKeyFromSEC(sec);
        CurvePoint publicKeyFromCompressedSec = ECDSA.generatePublicKeyFromSEC(compressedSec);

        assertTrue(publicKeyFromSec.isEqual(publicKey));
        assertTrue(publicKeyFromCompressedSec.isEqual(publicKey));
        assertTrue(publicKeyFromSec.isEqual(publicKeyFromCompressedSec));
    }



}
