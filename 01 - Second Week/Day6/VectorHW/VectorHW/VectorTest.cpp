/*
  Author: Daniel Kopta and ??
  July 2017
  
  CS 6010 Fall 2019
  Vector util library tests

  Compile this file together with your VectorUtil library with the following command:
  clang++ -std=c++11 VectorTest.cpp VectorUtil.cpp

  Most of the provided tests will fail until you have provided correct 
  implementations for the VectorUtil library functions.

  You will need to provide more thorough tests.
*/

#include <iostream>
#include <string>

// Include the VectorUtil library
#include "VectorUtil.h"

/*
 * Helper function for failing a test.
 * Prints a message and exits the program.
 */
void ErrorExit( std::string message )
{
  std::cerr << "Failed test: " << message << std::endl;
  exit(1); // Causes the entire program to exit.
}


int main()
{
  
  // Set up some input vectors for testing purposes.

  // We can use list initialization syntax:
  vector<int> v1 = {3, 1, 0, -1, 5};

  // Or we can repeatedly push_back items
  vector<int> v2;
  v2.push_back(1);
  v2.push_back(2);
  v2.push_back(3);

  // When testing, be sure to check boundary conditions, such as an empty vector
  vector<int> empty;
  
  
  /* 
   * Contains tests 
   */

  // v1 doesn't contain 4, so this should return false
  if( Contains(v1, 4) ) {
    ErrorExit( "Contains() - test 1" );
  }
    

  // v1 does contain -1, so this should return true
  if(!Contains(v1, -1)) {
    ErrorExit("Contains() - test 2");
      std::cout << "Contains -1, it worked." << std::endl;
  }

  /* 
   * The vector 'empty' doesn't contain anything, so this should return false
   * The specific value we're looking for here (99) is not important in this test. 
   * This test is designed to find any general errors caused by the array being empty. 
   * That type of error is unlikely to depend on the value we are looking for.
  */
  if( Contains(empty, 99) ) {
    ErrorExit("Contains() - empty");
  }
    
  
  // TODO: Add your own tests that thoroughly exercise your VectorUtil library.
    /// Contains() Test
    if( !Contains(v1, 3) ) {
        ErrorExit( "T1: Contains()" );
    }
    if( !Contains(v1, 1) ) {
        ErrorExit( "T2: Contains()" );
    }
    if( Contains(v1, 4) ) {
        ErrorExit( "T3: Contains()" );
    }
    if( Contains(v1, 20) ) {
        ErrorExit( "T4: Contains()" );
    }
    if( !Contains(v2, 1) ) {
        ErrorExit( "T5: Contains()" );
    }
    if( !Contains(v2, 3) ) {
        ErrorExit( "T6: Contains()" );
    }
    if( Contains(v2, 20) ) {
        ErrorExit( "T7: Contains()" );
    }
    if( Contains(v2, 17) ) {
        ErrorExit( "T8: Contains()" );
    }
    if( Contains(empty, 1) ) {
        ErrorExit("T9: Contains()");
    }
    if( Contains(empty, 22) ) {
        ErrorExit("T10: Contains()");
    }
    std::cout << "Contains() works!\n";
    
    /// FindMin() Tests
    if (FindMin(v1) != -1) {
        ErrorExit("T11: FindMin()");
    }
    if (FindMin(v2) != 1) {
        ErrorExit("T12: FindMin()");
    }
    if (FindMin(empty) == 123) {
        ErrorExit("T13: FindMin()");
    }
    std::cout << "FindMin() works!\n";
    
    /// FindMax() Tests
    if (FindMax(v1) != 5) {
        ErrorExit("T14: FindMax()");
    }
    if (FindMax(v2) != 3) {
        ErrorExit("T15: FindMax()");
    }
    if (FindMax(empty) == 123) {
        ErrorExit("T16: FindMax()");
    }
    std::cout << "FindMax() works!\n";
    
    /// Average() Tests
    if (Average(v1) != 1) {
        ErrorExit("T17: Average()");
    }
    if (Average(v2) != 2) {
        ErrorExit("T18: Average()");
    }
    if (Average(empty) == 123) {
        ErrorExit("T19: Average()");
    }
    std::cout << "Average() works!\n";
    
    /// IsSorted() Tests
    for (int i = 0; i < 100; i++) { //Testing it 100 times because the algorithm was returning different values across different runs. It is fixed now.
        if (IsSorted(v1)) {
            ErrorExit("T20: IsSorted()");
        }
        if (!IsSorted(v2)) {
            ErrorExit("T21: IsSorted()");
        }
        if (IsSorted(empty)) {
            ErrorExit("T22: IsSorted()");
        }
    }
    std::cout << "IsSorted() works!\n";


  // Since any failed test exits the program, if we made it this far, we passed all tests.
  std::cout << "All tests passed!\n";

}
