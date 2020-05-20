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
        assertEquals(10, added.getPrime());
        assertEquals(5, added.getNum());
    }

    @Test
    public void subOperator() {
        FieldElement fieldElement1 = new FieldElement(9, 57);
        FieldElement fieldElement2 = new FieldElement(29, 57);
        FieldElement sub = fieldElement1.sub(fieldElement2);
        assertEquals(57, sub.getPrime());
        assertEquals(37, sub.getNum());
    }

    @Test
    public void mulOperator() {
        FieldElement fieldElement1 = new FieldElement(3, 13);
        FieldElement fieldElement2 = new FieldElement(12, 13);
        FieldElement multiplied = fieldElement1.mul(fieldElement2);
        assertEquals(13, multiplied.getPrime());
        assertEquals(10, multiplied.getNum());
    }

    @Test
    public void powOperator() {
        FieldElement fieldElement1 = new FieldElement(7, 13);
        FieldElement powered = fieldElement1.pow(-3);
        assertEquals(13, powered.getPrime());
        assertEquals(8, powered.getNum());
    }

    @Test
    public void divOperator() {
        FieldElement fieldElement1 = new FieldElement(3, 31);
        FieldElement fieldElement2 = new FieldElement(24, 31);
        FieldElement divided = fieldElement1.div(fieldElement2);

        assertEquals(31, divided.getPrime());
        assertEquals(4, divided.getNum());
    }

}
