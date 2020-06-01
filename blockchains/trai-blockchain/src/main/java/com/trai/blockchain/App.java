package com.trai.blockchain;

import com.trai.blockchain.cryptography.*;

import java.io.UnsupportedEncodingException;
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

    public static final String base58Chars = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

    private static final char[] HEX_ARRAY = "0123456789abcdef".toCharArray();
    public static String bytesToHex(byte[] bytes) {
        char[] hexChars = new char[bytes.length * 2];
        for (int j = 0; j < bytes.length; j++) {
            int v = bytes[j] & 0xFF;
            hexChars[j * 2] = HEX_ARRAY[v >>> 4];
            hexChars[j * 2 + 1] = HEX_ARRAY[v & 0x0F];
        }
        return new String(hexChars);
    }

    public static byte[] hexToBytes(String s) {
        if (s.length() % 2 != 0)
            throw new IllegalArgumentException();

        byte[] b = new byte[s.length() / 2];
        for (int i = 0; i < s.length(); i += 2) {
            if (s.charAt(i) == '+' || s.charAt(i) == '-')
                throw new IllegalArgumentException();
            b[i / 2] = (byte)Integer.parseInt(s.substring(i, i + 2), 16);
        }
        return b;
    }

    public static BigInteger sha256(String message) throws NoSuchAlgorithmException {
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hash = digest.digest(message.getBytes(StandardCharsets.UTF_8));
        return new BigInteger(hash);
    }

    public static BigInteger ripemd160(String message) {
        byte[] hash = Ripemd160.getHash(message.getBytes(StandardCharsets.UTF_8));
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
        /* Change endianess */
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

    public static void main(String[] args) throws NoSuchAlgorithmException, UnsupportedEncodingException {



        BigInteger message = sha256("Hello");
        BigInteger privateKey = ECDSA.generatePrivateKey();
        CurvePoint publicKey = ECDSA.generatePublicKey(privateKey);
        Signature sig = ECDSA.sign(message, privateKey);

//        System.out.println(privateKey);

        BigInteger messageToCheck = sha256("Hello2");
        boolean verified = ECDSA.verify(messageToCheck, publicKey, sig);
        String der = sig.toDER();
//        System.out.println(der);


//        System.out.println(toBase58("1ff00"));
//        System.out.println(Base58.encode("1ff00".getBytes()));
//        System.out.println(Base58.encode("7c076ff316692a3d7eb3c3bb0f8b1488cf72e1afcd929e29307032997a838ad3".getBytes()));
//        System.out.println(Base58.encode(new BigInteger("7c076ff316692a3d7eb3c3bb0f8b1488cf72e1afcd929e29307032997a838a3d", 16).toByteArray()));
//        System.out.println(Base58.encode(new BigInteger("eff69ef2b1bd93a66ed5219add4fb51e11a840f404876325a1e8ffe0529a2c", 16).toByteArray()));
//        System.out.println(Base58.encode(new BigInteger("c7207fee197d27c618aea621406f6bf5ef6fca38681d82b2f06fddbdce6feab6", 16).toByteArray()));

//        System.out.println(ripemd160("Hello").toString(16));
        byte[] hash = Ripemd160.getHash("abc".getBytes("US-ASCII"));
        BigInteger rip160 = new BigInteger(hash);
//        System.out.println(rip160.toString(16));
        System.out.println(bytesToHex(hash));
//        System.out.println(rip160.toString(16));
//        System.out.println(sha256("Hello").toString(16));

    }


}
