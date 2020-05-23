package com.trai.blockchain.cryptographyTests;

import com.trai.blockchain.cryptography.FieldElement;
import org.junit.Test;
import static org.junit.Assert.*;


public class FieldElementTest {

    @Test(expected = IllegalArgumentException.class)
    public void creationException() {
        FieldElement fieldElement = new FieldElement(12, 10);
    }

    @Test
    public void equalOperator() {
        FieldElement fieldElement1 = new FieldElement(10, 12);
        FieldElement fieldElement2 = new FieldElement(10, 12);
        FieldElement fieldElement3 = new FieldElement(9, 12);
        assertTrue(fieldElement1.isEqual(fieldElement2));
        assertFalse(fieldElement1.isEqual(fieldElement3));
    }

    @Test
    public void addOperator() {
        FieldElement fieldElement1 = new FieldElement(8, 10);
        FieldElement fieldElement2 = new FieldElement(7, 10);
        FieldElement added = fieldElement1.add(fieldElement2);
        FieldElement expected = new FieldElement(5, 10);
        assertTrue(added.isEqual(expected));
    }

    @Test
    public void subOperator() {
        FieldElement fieldElement1 = new FieldElement(9, 57);
        FieldElement fieldElement2 = new FieldElement(29, 57);
        FieldElement subtracted = fieldElement1.sub(fieldElement2);
        FieldElement expected = new FieldElement(37, 57);
        assertTrue(subtracted.isEqual(expected));
    }

    @Test
    public void mulOperator() {
        FieldElement fieldElement1 = new FieldElement(3, 13);
        FieldElement fieldElement2 = new FieldElement(12, 13);
        FieldElement multiplied = fieldElement1.mul(fieldElement2);
        FieldElement expected = new FieldElement(10, 13);
        assertTrue(multiplied.isEqual(expected));
    }

    @Test
    public void powOperator() {
        FieldElement fieldElement1 = new FieldElement(7, 13);
        FieldElement powered = fieldElement1.pow(-3);
        FieldElement expected = new FieldElement(8, 13);
        assertTrue(powered.isEqual(expected));
    }

    @Test
    public void divOperator() {
        FieldElement fieldElement1 = new FieldElement(3, 31);
        FieldElement fieldElement2 = new FieldElement(24, 31);
        FieldElement divided = fieldElement1.div(fieldElement2);
        FieldElement expected = new FieldElement(4, 31);
        assertTrue(divided.isEqual(expected));
    }

}
