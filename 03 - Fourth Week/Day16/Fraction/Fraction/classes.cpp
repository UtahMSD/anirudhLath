//
//  classes.cpp
//  Fraction
//
//  Created by Anirudh Lath on 9/14/21.
//

#include "classes.hpp"
#include <cmath>
#include <iostream>

using namespace std;

void Fraction::reduce() {
    long gcd = this -> GCD();
    numerator /= gcd;
    denominator /= gcd;
} // Changes this fraction to its reduced form.

long Fraction::GCD() {
    long gcd = (long) abs(numerator);
    long remainder = (long) abs(denominator);
    while(remainder != 0) {
      long temp = remainder;
      remainder = (long) gcd % remainder;
      gcd = temp;
    }
    return gcd;
} // Returns the greatest common divisor of this fraction's numerator and denominator. This is a helper method for the reduce method, below.

Fraction::Fraction(){
    numerator = 0;
    denominator = 1;
} // The default constructor

Fraction::Fraction(long n, long d){
    if (n < 0 and d < 0) {
        numerator = (long) abs(n);
        denominator = (long) abs(d);
    } else if (d < 0) {
        numerator = (long) n * -1;
        denominator = (long) abs(d);
    } else {
        numerator = n;
        denominator = d;
    }
} // Constructor with the ability to assign the values.

Fraction Fraction::plus(Fraction rhs){
    Fraction result;
    rhs.resolve();
    result.numerator = (long)(numerator * rhs.denominator) + (long)(rhs.numerator * denominator);
    result.denominator = (long) denominator * (long)rhs.denominator;
    result.resolve();
    result.reduce();
    return result;
} // Returns a new fraction that is the result of the right hand side (rhs) fraction added to this fraction.

Fraction Fraction::minus(Fraction rhs){
    Fraction result;
    rhs.resolve();
    result.numerator = (long)(numerator * (long) rhs.denominator) - (rhs.numerator * denominator);
    result.denominator = (long) denominator * (long)rhs.denominator;
    result.resolve();
    result.reduce();
    return result;
} // Returns a new fraction that is the result of the right hand side (rhs) fraction subtracted from this fraction.

Fraction Fraction::times(Fraction rhs){
    Fraction result;
    rhs.resolve();
    result.numerator = (long) numerator * (long)rhs.numerator;
    result.denominator = (long) denominator * (long)rhs.denominator;
    result.resolve();
    result.resolve();
    return result;
} // Returns a new fraction that is the result of this fraction multiplied by the right hand side (rhs) fraction.

Fraction Fraction::dividedBy(Fraction rhs){
    Fraction result;
    rhs.resolve();
    result.numerator = (long) numerator * (long) rhs.denominator;
    result.denominator = (long) denominator * (long) rhs.numerator;
    result.resolve();
    result.reduce();
    return result;
} // Returns a new fraction that is the result of this fraction divided by the right hand side (rhs) fraction.

void Fraction::resolve() {
    if (numerator < 0 and denominator < 0) {
        numerator = (long) abs(numerator);
        denominator = (long) abs(denominator);
    } else if (denominator < 0) {
        numerator =  (long) numerator * -1;
        denominator = (long) abs(denominator);
    }
} // Resolves numerator and denominator negativity.

Fraction Fraction::reciprocal(){
    Fraction result;
    result.numerator = (long) denominator;
    result.denominator = (long) numerator;
    return result;
} // Returns a new fraction that is the reciprocal of this fraction.

std::string Fraction::toString(){
    string result;
    this -> reduce();
    if (numerator < 0 and denominator < 0) {
        result += to_string(abs(numerator));
        result.push_back('/');
        result += to_string(abs(denominator));
    } else if (denominator < 0) {
        result += to_string(numerator * -1);
        result.push_back('/');
        result += to_string(abs(denominator));
    } else {
        result += to_string(numerator);
        result.push_back('/');
        result += to_string(denominator);
        
    }
    return result;
} // Returns a string representing this fraction. The string should have the format: "N/D", where N is the numerator, and D is the denominator. This method should always print the reduced form of the fraction. If the fraction is negative, the sign should be displayed on the numerator, e.g., "-1/2" not "1/-2".

double Fraction::toDouble() const{
    double result = (long) numerator * 1.0000000000 / (long) denominator * 1.0000000000;
    
    return result;
} // Returns a (double precision) floating point number that is the approximate value of this fraction, printed as a real number.

Fraction Fraction::operator+(const Fraction& rhs) {
    Fraction f1 = plus(rhs);
    return f1;
}

Fraction& Fraction::operator+=( const Fraction& rhs){
    Fraction f1 = plus(rhs);
    numerator = f1.numerator;
    denominator = f1.denominator;
    return *this;
}

Fraction Fraction::operator-(const Fraction& rhs) {
    Fraction f1 = minus(rhs);
    return f1;
}

Fraction& Fraction::operator-=( const Fraction& rhs){
    Fraction f1 = minus(rhs);
    numerator = f1.numerator;
    denominator = f1.denominator;
    return *this;
}

Fraction Fraction::operator*(const Fraction& rhs) {
    Fraction f1 = times(rhs);
    return f1;
}

Fraction& Fraction::operator*=( const Fraction& rhs) {
    Fraction f1 = times(rhs);
    numerator = f1.numerator;
    denominator = f1.denominator;
    return *this;
}

Fraction Fraction::operator/(const Fraction& rhs) {
    Fraction f1 = dividedBy(rhs);
    return f1;
}
Fraction& Fraction::operator/=( const Fraction& rhs){
    Fraction f1 = dividedBy(rhs);
    numerator = f1.numerator;
    denominator = f1.denominator;
    return *this;
}

bool Fraction::operator==(const Fraction& rhs) {
    if(numerator == rhs.numerator && denominator == rhs.denominator) {
        return true;
    }
    return false;
}
bool Fraction::operator!=( const Fraction& rhs) {
    if(numerator == rhs.numerator && denominator == rhs.denominator) {
        return false;
    }
    return true;
}
bool Fraction::operator<(const Fraction& rhs) {
    double thisDouble = toDouble();
    double rhsDouble = rhs.toDouble();
    
    if(thisDouble < rhsDouble) {
        return true;
    }
    return false;
}

bool Fraction::operator>( const Fraction& rhs) {
    double thisDouble = toDouble();
    double rhsDouble = rhs.toDouble();
    
    if(thisDouble > rhsDouble) {
        return true;
    }
    return false;
}
bool Fraction::operator<=(const Fraction& rhs) {
    double thisDouble = toDouble();
    double rhsDouble = rhs.toDouble();
    
    if(thisDouble <= rhsDouble) {
        return true;
    }
    return false;
}
bool Fraction::operator>=( const Fraction& rhs) {
    double thisDouble = toDouble();
    double rhsDouble = rhs.toDouble();
    
    if(thisDouble >= rhsDouble) {
        return true;
    }
    return false;
}
