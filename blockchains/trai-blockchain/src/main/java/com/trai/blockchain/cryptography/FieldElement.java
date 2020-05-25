package com.trai.blockchain.cryptography;

import lombok.Data;
import java.math.BigInteger;


@Data
public class FieldElement {
    /* Field Element - represents one element of finite field */
    private final BigInteger num;
    private final BigInteger prime;

    public FieldElement(int num, int prime) {
        BigInteger numVal = BigInteger.valueOf(num);
        BigInteger primeVal = BigInteger.valueOf(prime);
        validateAttrs(numVal, primeVal);

        this.num = numVal;
        this.prime = primeVal;
    }

    public FieldElement(BigInteger num, BigInteger prime) {
        validateAttrs(num, prime);
        this.num = num;
        this.prime = prime;
    }

    public FieldElement(String hexNum, String hexPrime) {
        BigInteger num = new BigInteger(hexNum, 16);
        BigInteger prime = new BigInteger(hexPrime, 16);
        validateAttrs(num, prime);
        this.num = num;
        this.prime = prime;
    }

    public FieldElement(String hexNum, BigInteger prime) {
        BigInteger num = new BigInteger(hexNum, 16);
        validateAttrs(num, prime);
        this.num = num;
        this.prime = prime;
    }

    private void validateAttrs(BigInteger num, BigInteger prime) {
        if (num.compareTo(prime) >= 0 || num.signum() < 0)
            throw new IllegalArgumentException(String.format("Number %d is not in range 0 - %d",
                    num, prime.subtract(BigInteger.ONE)));
    }

    public boolean isEqual(FieldElement other) {
        return (num.compareTo(other.getNum()) == 0 && prime.compareTo(other.getPrime()) == 0);
    }

    public FieldElement add(FieldElement other) {
        // A + B = (a + b) % prime
        if (prime.compareTo(other.getPrime()) != 0)
            throw new IllegalArgumentException(String.format(
                    "Cannot add FieldElement with different prime (%d != %d", other.getPrime(), prime));

        BigInteger value = num.add(other.getNum()).mod(prime);
        return new FieldElement(value, prime);
    }

    public FieldElement sub(FieldElement other) {
        // A - B = (a - b) % prime
        if (prime.compareTo(other.getPrime()) != 0)
            throw new IllegalArgumentException(String.format(
                    "Cannot subtract FieldElement with different prime (%d != %d", other.getPrime(), prime));

        BigInteger value = num.subtract(other.getNum()).mod(prime);
        return new FieldElement(value, prime);
    }

    public FieldElement mul(FieldElement other) {
        // A * B = (a * b) % prime
        if (prime.compareTo(other.getPrime()) != 0)
            throw new IllegalArgumentException(String.format(
                    "Cannot multiply FieldElement with different prime (%d != %d", other.getPrime(), prime));

        BigInteger value = num.multiply(other.getNum()).mod(prime);
        return new FieldElement(value, prime);
    }

    public FieldElement mul(BigInteger val) {
        // A * B = (a * b) % prime
        BigInteger value = num.multiply(val).mod(prime);
        return new FieldElement(value, prime);
    }

    public FieldElement mul(int val) {
        BigInteger value = BigInteger.valueOf(val);
        return mul(value);
    }

    public FieldElement pow(BigInteger exponent) {
        // pow(A, exponent)
        while (exponent.signum() < 0)
            exponent = exponent.add(prime.subtract(BigInteger.ONE));

        BigInteger value = num.pow(exponent.intValue()).mod(prime);
        return new FieldElement(value, prime);
    }

    public FieldElement pow(int exponent) {
        BigInteger exp = BigInteger.valueOf(exponent);
        return pow(exp);
    }

    public FieldElement div(FieldElement other) {
        // A / B
        if (prime.compareTo(other.getPrime()) != 0)
            throw new IllegalArgumentException(String.format(
                    "Cannot divide FieldElement with different prime (%d != %d", other.getPrime(), prime));

        BigInteger exponent = prime.subtract(BigInteger.valueOf(2));
        BigInteger value = num.multiply(other.getNum().modPow(exponent, prime)).mod(prime);
        return new FieldElement(value, prime);
    }

}
