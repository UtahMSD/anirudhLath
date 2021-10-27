import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class FractionTest {

    Fraction fraction1 = new Fraction();
    Fraction fraction2 = new Fraction(2,2);
    Fraction fraction3 = new Fraction(24,64);
    Fraction fraction4 = new Fraction(2,-1);
    Fraction fraction5 = new Fraction(-12,64);
    Fraction fraction6 = new Fraction(24,61);

    ArrayList<Fraction> fractions = new ArrayList<>();


    @org.junit.jupiter.api.Test
    void plus() {
        // For some reason the numerical values fail the test even though it is the same value.
        assertEquals(new Fraction(-1,1).toString(), fraction2.plus(fraction4).toString());
        assertEquals(new Fraction(3,16).toString(), fraction5.plus(fraction3).toString());
        assertEquals(new Fraction(201,976).toString(), fraction5.plus(fraction6).toString());
    }

    @org.junit.jupiter.api.Test
    void minus() {
        // For some reason the numerical values fail the test even though it is the same value.
        assertEquals(new Fraction(3,1).toString(), fraction2.minus(fraction4).toString());
        assertEquals(new Fraction(-9,16).toString(), fraction5.minus(fraction3).toString());
        assertEquals(new Fraction(-567,976).toString(), fraction5.minus(fraction6).toString());
    }

    @org.junit.jupiter.api.Test
    void times() {
        assertEquals(new Fraction(-2,1).toString(), fraction2.times(fraction4).toString());
        assertEquals(new Fraction(-9,128).toString(), fraction5.times(fraction3).toString());
        assertEquals(new Fraction(-9,122).toString(), fraction5.times(fraction6).toString());
    }

    @org.junit.jupiter.api.Test
    void dividedBy() {
        assertEquals(new Fraction(-1,2).toString(), fraction2.dividedBy(fraction4).toString());
        assertEquals(new Fraction(-1,2).toString(), fraction5.dividedBy(fraction3).toString());
        assertEquals(new Fraction(-61,128).toString(), fraction5.dividedBy(fraction6).toString());
    }

    @org.junit.jupiter.api.Test
    void reciprocal() {
        assertEquals(new Fraction(1,1).toString(), fraction2.reciprocal().toString());
        assertEquals(new Fraction(-16,3).toString(), fraction5.reciprocal().toString());
        assertEquals(new Fraction(8,3).toString(), fraction3.reciprocal().toString());
    }

    @org.junit.jupiter.api.Test
    void testToString() {
        assertEquals("1/1", fraction2.toString());
        assertEquals("-3/16", fraction5.toString());
        assertEquals("3/8", fraction3.toString());
    }

    @org.junit.jupiter.api.Test
    void toDouble() {
        assertEquals(1.0, fraction2.toDouble());
        assertEquals(-0.1875, fraction5.toDouble());
        assertEquals(0.375, fraction3.toDouble());
    }

    @org.junit.jupiter.api.Test
    void main() {
        assertEquals(new ArithmeticException("The denominator cannot be 0."), new Fraction(2,0));
    }
}