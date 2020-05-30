package com.trai.blockchain;

import com.trai.blockchain.cryptography.*;

import java.math.BigInteger;
import java.nio.ByteOrder;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

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

    public static String byteToHex(byte num) {
        char[] hexDigits = new char[2];
        hexDigits[0] = Character.forDigit((num >> 4) & 0xF, 16);
        hexDigits[1] = Character.forDigit((num & 0xF), 16);
        return new String(hexDigits);
    }

    public static String encodeHexString(byte[] byteArray) {
        StringBuilder hexStringBuffer = new StringBuilder();
        for (byte b : byteArray) {
            hexStringBuffer.append(byteToHex(b));
        }
        return hexStringBuffer.toString();
    }

    public static String reverseHex(String hexNum) {
        if (!(hexNum.length() % 2 == 0))
            hexNum = "0" + hexNum;

        int lengthInBytes = hexNum.length() / 2;
        char[] chars = new char[lengthInBytes * 2];
        for (int index = 0; index < lengthInBytes; index++) {
            int reversedIndex = lengthInBytes - 1 - index;
            chars[reversedIndex * 2] = hexNum.charAt(index * 2);
            chars[reversedIndex * 2 + 1] = hexNum.charAt(index * 2 + 1);
        }
        return new String(chars);
    }


    public static void main(String[] args) throws NoSuchAlgorithmException {




        BigInteger privateKey = ECDSA.generatePrivateKey();
        CurvePoint publicKey = ECDSA.generatePublicKey(privateKey);
//        Signature sig = ECDSA.sign(message, privateKey);
//
////        System.out.println(privateKey);
//
//        BigInteger messageToCheck = sha256("Hello2");
//        boolean verified = ECDSA.verify(messageToCheck, publicKey, sig);
//        System.out.println(verified);

        System.out.println(publicKey.getX().getNum().toString(16));
        System.out.println(publicKey.getY().getNum().toString(16));
        String sec = publicKey.toSEC();
        String secCompressed = publicKey.toCompressedSEC();


        CurvePoint fromSec = ECDSA.generatePublicKeyFromSEC(sec);
        System.out.println("FROM SEC:");
        System.out.println(fromSec.getX().getNum().toString(16));
        System.out.println(fromSec.getY().getNum().toString(16));

        CurvePoint fromCompressedSec = ECDSA.generatePublicKeyFromSEC(secCompressed);
        System.out.println("FROM Compressed SEC:");
        System.out.println(fromCompressedSec.getX().getNum().toString(16));
        System.out.println(fromCompressedSec.getY().getNum().toString(16));


    }


}
