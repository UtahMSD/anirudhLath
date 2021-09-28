//
//  main.cpp
//  BitManipulation
//
//  Created by Anirudh Lath, Andrew Kellett & Braden Kirkham on 9/11/21.
//
/*
  Author: Daniel Kopta, Ben Jones
  
  CS 6010
  Bit puzzles

  * The set of functions below are exercises to help you practice accessing
  * and manipulating individual bits in program data, and to help understand
  * how a computer represents numbers.
  * Replace the TODO statements below with correct implementations of the functions.
  * Each function's purpose is described in a comment.
  * main() runs many tests on your functions and reports which ones passed or failed.
  * Make sure you pass all tests.
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

/*
 * Determines whether or not the specified bit is set in the input int
 *
 * Parameters:
 *   input -- The input int
 *   b -- The bit to retreive (0 = least significant, 31 = most significant)
 *
 * Returns:
 *   true if the specified bit is set, false otherwise.
 *
 * Examples:
 *   GetBit(5, 0) -> returns true, because the bit pattern for 5 is 101, we are looking at the rightmost bit
 *   GetBit(5, 1) -> returns false
 *   GetBit(-42, 31) -> returns true
 */
bool GetBit( uint32_t input, int b )
{
    int i = input >> b;
    return (i & 0x1) == 1;
}


/*
 * Determines whether or not an int is negative
 *
 * Do not use the < or > operators
 *
 * Parameters:
 *   input -- The input int
 *
 * Returns:
 *   Whether or not the int is negative
 */
bool IsNegative( int input )
{
    return GetBit(input, 31);
}

/*
 * Determines the number of bits set (to 1) in a number
 *
 * Parameters:
 *   input -- The input int
 *
 * Returns:
 *   The number of set bits.
 *
 * Examples:
 *   NumBitsSet(5) -> returns 2
 *   NumBitsSet(64) -> returns 1
 *   NumBitsSet(-1) -> returns 32
 */
int NumBitsSet( uint32_t input )
{
    int i = input;
        int count = 0;
        int index = 0;
        while (index < 32){
            if(GetBit( i, index)){
                count++;
            }
            index++;
        }
        return count;
}


/*
 * GetByte() returns a specified byte from a 4-byte variable.
 *
 * Parameters:
 *   input -- The input value
 *   b -- The byte to retreive (0 = least significant, 3 = most significant)
 *
 * Returns:
 *   The specified byte within the input.
 *
 * Examples:
 *   GetByte( 5, 0 )          -> returns 5
 *   GetByte( 5, 1 )          -> returns 0
 *   GetByte( 0x1234abcd, 0 ) -> returns 0xcd (205 as unsigned char)
 *   GetByte( 0x1234abcd, 3 ) -> returns 0x12 (18 as an unsigned char)
 */
unsigned char GetByte( uint32_t input, int b )
{
    int i = input;
        if( b == 0){
            i = i & 0xff;
        }
        else if( b == 1){
            i = (i & 0xff00) >> 8;
        }
        else if( b == 2){
            i = (i & 0xff0000) >> 16;
        }
        else if( b == 3){
            i = i >> 24;
        }
        unsigned char c = i;     // why char unsigned?
        return c;
}


/*
 * SetByte() sets the specified byte in the input to the specified value, and returns the result.
 *
 * Parameters:
 *   input -- The input value
 *   value -- The value to set the input's specified byte to
 *   b -- The byte to set (0 = least significant, 3 = most significant)
 *
 * Returns:
 *   The modified result
 *
 * Examples:
 *   SetByte( 0, 5, 0 )                -> returns 5
 *   SetByte( 0, 5, 1 )                -> returns 0x500 (1280 as unsigned int)
 *   SetByte( 0xffffffff, 0, 2 )       -> returns 0xff00ffff (4278255615 as unsigned int)
 *   SetByte( (unsigned int)-1, 0, 2 ) -> returns 0xff00ffff (4278255615 as unsigned int)
 *   SetByte( 0xabcd, 7, 1 )           -> returns 0x7cd (1997 as unsigned int)
 */
uint32_t SetByte( uint32_t input, uint8_t value, int b )
{
    uint32_t i = input;
        int j;
        if( b == 0){
            i = i & 0xffffff00;
            i = i | value;
        }
        else if( b == 1){
            j = i & 0xff;
            i = (i & 0xffff0000) >> 8;
            i = (i | value) << 8;
            i = i | j;
            
        }
        else if( b == 2){
            j = i & 0xffff;
            i = (i & 0xff000000) >> 16;
            i = (i | value) << 16;
            i = i | j;
        }
        else if( b == 3){
            j = i & 0xffffff;
            i = i >> 24 << 8;
            i = (i | value) << 24;
            i = i | j;
        }
        return i;
}


/*
 * Negate() computes the negation of an integer.
 *
 * Do not use the * or *= operators
 * Do not use the / or /= operators
 * Do not use the + or += operators
 * Do not use the - or -= operators
 * Do not use the unary - operator
 *
 * Assumes that input is not equal to INT_MIN (a bit pattern of 100...0, or the minimum integer)
 *
 * Parameters:
 *   input -- The input int
 *
 * Returns:
 *   -i (negative i)
 *
 * Examples:
 *   Negate(5) -> returns -5
 *   Negate(-1) -> returns 1
 */
int Negate( int input )
{
    input = ~input;
        int pos = 1;
        while ( pos & input ){
            input = input ^ pos;
            pos = pos << 1;
        }
        input = input ^ pos;
        return input;
}


/*
 * Challenge Question
 *
 * Increment
 * This function should return x + 1 but should only make use of bitwise operators and == or !=
*/
int Increment( uint32_t input ){
    int pos = 1;
    while ( pos & input ){
        input = input ^ pos;
        pos = pos << 1;
    }
    input = input ^ pos;
    return input;
}



/**************************************************/
/* End bit puzzles. Below are the provided tests. */
/**************************************************/


/*
 * Three forms of helper functions for the tests in main().
 * These functions compare a given value to an expected value,
 * and report an error if they don't match.
 */

/*
 * Compare two 32-bit values
 */

void Test32Bit( int a, int b, const string & message )
{
  if( a != b ) {
    cout << "FAIL: " << message << ", expected " << b << ", got " << a << endl;
  }
  else {
    cout << "PASS: " << message << endl;
  }
}

/*
 * Compare two 8-bit values
 */

void Test8Bit( unsigned char a, unsigned char b, const string & message )
{
  if( a != b ) {
    cout << "FAIL: " << message << ", expected " << std::hex << (unsigned int)b << ", got " << std::hex << (unsigned int)a << endl;
  }
  else {
    cout << "PASS: " << message << endl;
  }
}

/*
 * Compare two boolean values
 */

void TestBool( bool a, bool b, const string & message )
{
  if( a != b ) {
    cout << "FAIL: " << message << ", expected " << b << ", got " << a << endl;
  }
  else {
    cout << "PASS: " << message << endl;
  }
}


int main()
{
  /*
   * These tests exercise your bit puzzle solutions.
   * Many of the tests rely on hexadecimal instead of decimal.
   * Since hexadecimal maps much more easily to binary, it's  more useful
   * when we want to specify a number with a specific bit pattern,
   * such as alternating 10101010... (0xaa), or 01010101... (0x55),
   * or all ones in a certain byte: 0x00ff0000
   */
  SetByte( 0, 5, 0 );
    
  TestBool( GetBit( 0, 0 ), false, "GetBit1" );
  TestBool( GetBit( 0, 1 ), false, "GetBit2" );
  TestBool( GetBit( 0, 31 ), false, "GetBit3" );
  TestBool( GetBit( -1, 0 ), true, "GetBit4" );
  TestBool( GetBit( -1, 1 ), true, "GetBit5" );
  TestBool( GetBit( -1, 31 ), true, "GetBit6" );
  TestBool( GetBit( 0xAAAAAAAA, 0 ), false, "GetBit7" );
  TestBool( GetBit( 0xAAAAAAAA, 16 ), false, "GetBit8" );
  TestBool( GetBit( 0xAAAAAAAA, 17 ), true, "GetBit9" );
  TestBool( GetBit( 0xAAAAAAAA, 31 ), true, "GetBit10" );

  TestBool( IsNegative( 0 ), false, "IsNegative1" );
  TestBool( IsNegative( 1 ), false, "IsNegative2" );
  TestBool( IsNegative( -1 ), true, "IsNegative3" );
  TestBool( IsNegative( 0xAAAAAAAA ), true, "IsNegative4" );
  TestBool( IsNegative( 0x55555555 ), false, "IsNegative5" );
  TestBool( IsNegative( INT_MIN ), true, "IsNegative6" );
  TestBool( IsNegative( INT_MAX ), false, "IsNegative7" );

  Test32Bit( NumBitsSet( 0 ), 0, "NumBitsSet1" );
  Test32Bit( NumBitsSet( 1 ), 1, "NumBitsSet2" );
  Test32Bit( NumBitsSet( 2 ), 1, "NumBitsSet3" );
  Test32Bit( NumBitsSet( 3 ), 2, "NumBitsSet4" );
  Test32Bit( NumBitsSet( 5 ), 2, "NumBitsSet5" );
  Test32Bit( NumBitsSet( -1 ), 32, "NumBitsSet6" );
  Test32Bit( NumBitsSet( 0xAAAAAAAA ), 16, "NumBitsSet7" );
  Test32Bit( NumBitsSet( 0x55555555 ), 16, "NumBitsSet8" );

  Test8Bit( GetByte( 0, 0 ), 0, "GetByte1" );
  Test8Bit( GetByte( 0, 1 ), 0, "GetByte2" );
  Test8Bit( GetByte( 0, 2 ), 0, "GetByte3" );
  Test8Bit( GetByte( 0, 3 ), 0, "GetByte4" );
  Test8Bit( GetByte( 0xAAAAAAAA, 0 ), 0xaa, "GetByte4" );
  Test8Bit( GetByte( 0xAAAAAAAA, 1 ), 0xaa, "GetByte5" );
  Test8Bit( GetByte( 0xAAAAAAAA, 2 ), 0xaa, "GetByte6" );
  Test8Bit( GetByte( 0xAAAAAAAA, 3 ), 0xaa, "GetByte7" );
  Test8Bit( GetByte( 0x12345678, 0 ), 0x78, "GetByte8" );
  Test8Bit( GetByte( 0x12345678, 1 ), 0x56, "GetByte9" );
  Test8Bit( GetByte( 0x12345678, 2 ), 0x34, "GetByte10" );
  Test8Bit( GetByte( 0x12345678, 3 ), 0x12, "GetByte11" );

  Test32Bit( SetByte( 0, 0xFF, 0 ), 0xFF, "SetByte1" );
  Test32Bit( SetByte( 0, 0xFF, 1 ), 0xFF00, "SetByte2" );
  Test32Bit( SetByte( 0, 0xFF, 2 ), 0xFF0000, "SetByte3" );
  Test32Bit( SetByte( 0, 0xFF, 3 ), 0xFF000000, "SetByte4" );
  Test32Bit( SetByte( 0x12345678, 0xAA, 0 ), 0x123456aa, "SetByte5" );
  Test32Bit( SetByte( 0x12345678, 0xAA, 1 ), 0x1234aa78, "SetByte6" );
  Test32Bit( SetByte( 0x12345678, 0xAA, 2 ), 0x12aa5678, "SetByte7" );
  Test32Bit( SetByte( 0x12345678, 0xAA, 3 ), 0xaa345678, "SetByte8" );

  Test32Bit( Negate( -1 ), 1, "Negate1" );
  Test32Bit( Negate( 1 ), -1, "Negate2" );
  Test32Bit( Negate( 2 ), -2, "Negate3" );
  Test32Bit( Negate( -2 ), 2, "Negate4" );
  Test32Bit( Negate( 0 ), 0, "Negate5" );
  Test32Bit( Negate( 0x7fffffff ), 0x80000001, "Negate6" );
  Test32Bit( Negate( 0xAAAAAAAA ), 0x55555556, "Negate7" );


  Test32Bit( Increment( 0 ), 1, "Increment1" );
  Test32Bit( Increment( -1 ), 0, "Increment2" );
  Test32Bit( Increment( 10000 ), 10001, "Increment3" );
  Test32Bit( Increment( -999 ), -998, "Increment4" );

  return 0;
}
