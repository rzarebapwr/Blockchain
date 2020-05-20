package com.trai.blockchain;

import com.trai.blockchain.cryptography.FieldElement;

/**
 * Hello world!
 *
 */

public class App {
    public static void main(String[] args) {

        FieldElement fieldElement1 = new FieldElement(8, 10);
        FieldElement fieldElement2 = new FieldElement(7, 10);
        System.out.println(fieldElement1.equals(fieldElement2));
        FieldElement fieldElement3 = fieldElement1.add(fieldElement2);
        System.out.println(fieldElement3);

    }
}
