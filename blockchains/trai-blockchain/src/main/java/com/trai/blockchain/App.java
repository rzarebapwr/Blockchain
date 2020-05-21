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

        long startTime = System.nanoTime();


        int product = 0;
        int value = 5;
        int times = 10000;

        for (int i=0; i<times; ++i) {
            product += value;
        }

        long stopTime = System.nanoTime();
        System.out.println(String.format("Classic for loop took %d", stopTime - startTime));
        System.out.println(product);


        startTime = System.nanoTime();
        int rmultiplied = rmul(times);
        stopTime = System.nanoTime();
        System.out.println(String.format("RMUL took %d", stopTime - startTime));
        System.out.println(rmultiplied);





    }

    public static int rmul(int coefficient) {
        int coef = coefficient;
        int current = 5;
        int result = 0;

        while (coef != 0) {
//            System.out.println(coef);
            if ((coef & 1) == 1)
                result += current;
            current += current;
            coef >>= 1;

        }
        return result;
    }
}
