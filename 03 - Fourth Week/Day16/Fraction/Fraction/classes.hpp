//
//  classes.hpp
//  Fraction
//
//  Created by Anirudh Lath on 9/14/21.
//

#ifndef classes_hpp
#define classes_hpp

#include <stdio.h>
#include <string>

class Fraction {
private:
    /// Variables
    long numerator; // The numerator
    long denominator; // The denominator
    
    /// Private Methods
    void reduce(); // Changes this fraction to its reduced form.
    long GCD(); // Returns the greatest common divisor of this fraction's numerator and denominator. This is a helper method for the reduce method, below.
    void resolve(); // Resolves numerator and denominator negativity.

public:
    /// Constructors
    Fraction(); // The default constructor
    Fraction(long n, long d); // Constructor with the ability to assign the values.
    
    /// Public Methods
    Fraction plus(Fraction rhs); // Returns a new fraction that is the result of the right hand side (rhs) fraction added to this fraction.
    Fraction minus(Fraction rhs); // Returns a new fraction that is the result of the right hand side (rhs) fraction subtracted from this fraction.
    Fraction times(Fraction rhs); // Returns a new fraction that is the result of this fraction multiplied by the right hand side (rhs) fraction.
    Fraction dividedBy(Fraction rhs); // Returns a new fraction that is the result of this fraction divided by the right hand side (rhs) fraction.
    void extracted(Fraction &result);
    
    Fraction reciprocal(); // Returns a new fraction that is the reciprocal of this fraction.
    std::string toString(); // Returns a string representing this fraction. The string should have the format: "N/D", where N is the numerator, and D is the denominator. This method should always print the reduced form of the fraction. If the fraction is negative, the sign should be displayed on the numerator, e.g., "-1/2" not "1/-2".
    double toDouble(); // Returns a (double precision) floating point number that is the approximate value of this fraction, printed as a real number.
};

#endif /* classes_hpp */
