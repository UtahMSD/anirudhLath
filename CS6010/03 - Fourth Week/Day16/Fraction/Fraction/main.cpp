/*
 * Author: Daniel Kopta and Anirudh Lath
 * July 2017 >>> Updated by Anirudh Lath on 9/14/21.

 * Testing program for your Fraction class.
 * These tests are not very thorough, and you will need to add your own.
*/

// Include the student's Fraction class
#include "classes.hpp"

// Standard includes
#include <iostream>
#include <string>
// Also include math so we can use the pow and abs functions (see below)
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::string;

bool CompareDoubles( double d1, double d );


/* Helper function for writing tests that compare strings.
 * Compares expected to result, and prints an error if they don't match.
 */
void Test( const string & message, const string & expected, const string & result )
{
  cout << "Test: " << message << endl;
  if(expected != result) {
    cout << "\tFAILED, expected: \"" << expected << "\", got: \"" << result << "\"" << endl;
  }
  else {
    cout << "\tPASSED" << endl;
  }
}

/* Helper function for writing tests that compare doubles (overloaded version of the above)
 * Compares expected to result, and prints an error if they don't match.
 */
void Test( const string & message, double expected, double result )
{
  cout << "Test: " << message << endl;
  if( !CompareDoubles( expected, result ) ) {
    cout << "\tFAILED, expected: " << expected << ", got: " << result << endl;
  }
  else {
    cout << "\tPASSED" << endl;
  }
}


/*
 * Helper function
 * Returns whether or not two doubles are "equivalent",
 * within a certain error bound.
 *
 * As we know, floating point numbers are incapable of
 * precisely representing certain values, so to compare
 * equality, we must tolerate some absolute difference.
 */
bool CompareDoubles( double d1, double d2 )
{
  return std::abs( d1 - d2 ) < 1e-6;
}

/*
 * Basic constructor and toString tests
 */
void TestConstructors()
{
    std::string result = "";
    Fraction f1;
    result = f1.toString();
    Test( "Default constructor", "0/1", result );
    
    Fraction f2(1, 2);
    result = f2.toString();
    Test( "Basic constructor #1", "1/2", result );
    
    Fraction f3(10000, 2);
    result = f3.toString();
    Test( "Basic constructor #2", "5000/1", result );
    
    Fraction f4(1, 20342);
    result = f4.toString();
    Test( "Basic constructor #3", "1/20342", result );
    
    Fraction f5(23421, 99932);
    result = f5.toString();
    Test( "Basic constructor #4", "23421/99932", result );


}


/*
 * Negative fraction tests
 */
void TestNegative()
{
    std::string result = "";
    Fraction f1(-1, 2);
    result = f1.toString();
    Test( "Negative numerator #1", "-1/2", result );

    Fraction f2(1, -2);
    result = f2.toString();
    Test( "Negative denominator #1", "-1/2", result );

    Fraction f3(-1, -2);
    result = f3.toString();
    Test( "Negative numerator and denominator #1", "1/2", result );

    Fraction f4(4, -16);
    result = f4.toString();
    Test( "Negative denominator and reduce #1", "-1/4", result );
    
    Fraction f5(-19834, 24325);
    result = f5.toString();
    Test( "Negative numerator #2", "-19834/24325", result );

    Fraction f6(1345, -24567);
    result = f6.toString();
    Test( "Negative denominator #2", "-1345/24567", result );

    Fraction f7(-1346, -23467);
    result = f7.toString();
    Test( "Negative numerator and denominator #2", "1346/23467", result );

    Fraction f8(8, -180);
    result = f8.toString();
    Test( "Negative denominator and reduce #2", "-2/45", result );

}


/*
 * Reduced fraction tests
 */
void TestReduced()
{
    std::string result = "";
    Fraction f1(2, 4);
    result = f1.toString();
    Test( "Reduce fraction (2/4)", "1/2", result );
    
    Fraction f2(5, 120);
    result = f2.toString();
    Test( "Reduce fraction (5/120)", "1/24", result );
    
    Fraction f3(24, 460);
    result = f3.toString();
    Test( "Reduce fraction (2/4)", "6/115", result );
    
    Fraction f4(27, 54);
    result = f4.toString();
    Test( "Reduce fraction (2/4)", "1/2", result );
}


/*
 * Reciprocal tests
 */
void TestReciprocal()
{
  std::string result = "";
  Fraction f1(1, 3);
  f1 = f1.reciprocal();
  result = f1.toString();
  Test( "Reciprocal of simple #1", "3/1", result );

  Fraction f2(-1, 2);
  f2 = f2.reciprocal();
  result = f2.toString();
  Test( "Reciprocal of negative #1", "-2/1", result );

  Fraction f3(6, 2);
  f3 = f3.reciprocal();
  result = f3.toString();
  Test( "Reciprocal of reduced #1", "1/3", result );

    Fraction f4(1, 5);
    f4 = f4.reciprocal();
    result = f4.toString();
    Test( "Reciprocal of simple #2", "5/1", result );

    Fraction f5(-5, 2);
    f5 = f5.reciprocal();
    result = f5.toString();
    Test( "Reciprocal of negative #2", "-2/5", result );

    Fraction f6(6000, 2);
    f6 = f6.reciprocal();
    result = f6.toString();
    Test( "Reciprocal of reduced #3", "1/3000", result );
}

/*
 * Fraction addition tests
 */
void TestPlus()
{
  std::string result = "";
  Fraction f1(4, 6);
  Fraction f2(3, 4);
  
  // Should result in 17/12
  Fraction f3 = f1.plus(f2);
  result = f3.toString();
  Test( "Addition of non-reduced", "17/12", result );
    
    Fraction f4 = f3.plus(f2);
    result = f4.toString();
    Test( "Addition of non-reduced", "13/6", result );
    
    Fraction f5 = f1 + f2;
    result = f5.toString();
    Test( "operator+ overload", "17/12", result );
    
    f1 += f2;
    result = f1.toString();
    Test( "operator+= overload", "17/12", result );
    
    
}

/*
 * Fraction subraction tests
 */
void TestMinus()
{
  std::string result = "";
  Fraction f1(4, 6);
  Fraction f2(3, 4);
    
  Fraction f3 = f1.minus(f2);
  result = f3.toString();
  Test( "Subtraction of non-reduced", "-1/12", result );
    
    Fraction f4 = f3.minus(f2);
    result = f4.toString();
    Test( "Subtraction of non-reduced", "-5/6", result );
    
    Fraction f5 = f1 - f2;
    result = f5.toString();
    Test( "operator- overload", "-1/12", result );
    
    f1 -= f2;
    result = f1.toString();
    Test( "operator-= overload", "-1/12", result );
    
}

/*
 * Fraction subraction tests
 */
void TestMultiply()
{
  std::string result = "";
  Fraction f1(4, 6);
  Fraction f2(3, 4);
    
  Fraction f3 = f1.times(f2);
  result = f3.toString();
  Test( "Multiplication of non-reduced", "1/2", result );
    
    Fraction f4 = f3.times(f2);
    result = f4.toString();
    Test( "Multiplication of non-reduced", "3/8", result );
    
    Fraction f5 = f1 * f2;
    result = f5.toString();
    Test( "operator* overload", "1/2", result );
    
    f1 *= f2;
    result = f1.toString();
    Test( "operator*= overload", "1/2", result );
    
}

void TestDivide()
{
  std::string result = "";
  Fraction f1(4, 6);
  Fraction f2(3, 4);
    
  Fraction f3 = f1.dividedBy(f2);
  result = f3.toString();
  Test( "Division of non-reduced", "8/9", result );
    
    Fraction f4 = f3.dividedBy(f2);
    result = f4.toString();
    Test( "Division of non-reduced", "32/27", result );
    
    Fraction f5 = f1 / f2;
    result = f5.toString();
    Test( "operator/ overload", "8/9", result );
    
    f1 /= f2;
    result = f1.toString();
    Test( "operator/= overload", "8/9", result );
    
}

void TestBool()
{
  std::string result = "";
  Fraction f1(4, 6);
  Fraction f2(3, 4);
    Fraction f10(4, 6);
    
    cout << "Test: Bool operator overload test\n";
    
    if (f1 > f2 or f1 >= f2 or f2 < f1 or f2 <= f1
        or f1 == f2 or f1 != f10) {
        cout << "    FAILED\n";
    } else if (f2 > f1 and f1 >= f10 and f1 < f2 and f10 <= f1 and f1 == f10 and f1 != f2) {
        cout << "    PASSED\n";
    }
}

void TestToDouble()
{
  Fraction f1(1, 2);
  double result = f1.toDouble();
  Test( "toDouble (1/2)", 0.5, result );

  Fraction f2(1, 3);
  result = f2.toDouble();
  Test( "toDouble (1/3)", 1.0/3.0, result );
}

/*
 * Approximates pi using a summation of fractions.
 */
double ComputePi()
{
  Fraction sum;

  // We will only compute the first 4 terms
  // Note that even with long (64-bit) numbers,
  // the intermediate numbers required for fraction addition
  // become too large to represent if we go above k=4.
  for( long k = 0; k < 4; k++ )
  {
    Fraction multiplier( 1, pow(16, k) );
    Fraction firstTerm(  4, 8*k + 1 );
    Fraction secondTerm( 2, 8*k + 4 );
    Fraction thirdTerm(  1, 8*k + 5 );
    Fraction fourthTerm( 1, 8*k + 6 );

    Fraction temp = firstTerm.minus( secondTerm );
    temp = temp.minus( thirdTerm );
    temp = temp.minus( fourthTerm );
 
    Fraction product = multiplier.times( temp );

    sum = sum.plus( product );
  }
  
  return sum.toDouble();
}

int main()
{
  // Break up the tests into categories for better readability.
  TestConstructors();
  TestNegative();
  TestReduced();
  TestReciprocal();
  TestToDouble();
  TestPlus();
  Test("Approximating pi", 3.141592, ComputePi());
    TestMinus();
    TestMultiply();
    TestDivide();
    TestBool();
    
    // The 3 functions are not needed as we are not destroying any objects here in the operation overloads. We are just referencing and changing the member variables.
}
