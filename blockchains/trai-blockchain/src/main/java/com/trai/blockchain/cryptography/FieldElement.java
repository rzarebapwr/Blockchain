package com.trai.blockchain.cryptography;

import lombok.Data;

import java.math.BigInteger;


@Data
public class FieldElement {
    /* Field Element - represents one element of finite field */
    private final int num;
    private final int prime;

    public FieldElement(int num, int prime) {
        validateAttrs(num, prime);
        this.num = num;
        this.prime = prime;
    }

    private void validateAttrs(int num, int prime) {
        if (num >= prime || num < 0)
            throw new IllegalArgumentException(String.format("Number %d is not in range 0 - %d", num, prime-1));
    }

    public boolean isEqual(FieldElement other) {
        return num == other.getNum() && prime == other.getPrime();
    }

    public FieldElement add(FieldElement other) {
        // A + B = (a + b) % prime
        if (prime != other.getPrime())
            throw new IllegalArgumentException(String.format(
                    "Cannot add FieldElement with different prime (%d != %d", other.getPrime(), prime));

        int value = (num + other.getNum()) % prime;
        return new FieldElement(value, prime);
    }

    public FieldElement sub(FieldElement other) {
        // A - B = (a - b) % prime
        if (prime != other.getPrime())
            throw new IllegalArgumentException(String.format(
                    "Cannot subtract FieldElement with different prime (%d != %d", other.getPrime(), prime));

        int value = ((num - other.getNum()) + prime) % prime;
        return new FieldElement(value, prime);
    }

    public FieldElement mul(FieldElement other) {
        // A * B = (a * b) % prime
        if (prime != other.getPrime())
            throw new IllegalArgumentException(String.format(
                    "Cannot multiply FieldElement with different prime (%d != %d", other.getPrime(), prime));

        int value = (num * other.getNum()) % prime;
        return new FieldElement(value, prime);
    }

    public FieldElement pow(int exponent) {
        // pow(A, exponent)
        while (exponent < 0)
            exponent += prime - 1;

        int value = (int) (Math.pow(num, exponent) % prime);
        return new FieldElement(value, prime);
    }

    public FieldElement div(FieldElement other) {
        // A / B
        if (prime != other.getPrime())
            throw new IllegalArgumentException(String.format(
                    "Cannot divide FieldElement with different prime (%d != %d", other.getPrime(), prime));

        BigInteger thisValue = BigInteger.valueOf(num);
        BigInteger thisPrime = BigInteger.valueOf(prime);

        int value = BigInteger.valueOf(other.getNum()).pow(prime-2).multiply(thisValue).mod(thisPrime).intValue();

//        int value = (int) (num * (Math.pow(other.getNum(), prime-2)) % prime) % prime;
        return new FieldElement(value, prime);
    }

}
