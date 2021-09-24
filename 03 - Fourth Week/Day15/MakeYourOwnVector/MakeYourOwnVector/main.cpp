//
//  main.cpp
//  MakeYourOwnVector
//
//  Created by Anirudh Lath on 9/13/21.
//
#include "helper.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>




template <typename T>
void makeVectorTest(const myvector<T> &testVector, const myvector<T> &testVector2, const myvector<T> &testVector3) {
    if (testVector.getCapacity() == 4 && testVector.getSize() == 0
    && testVector2.getCapacity() == 10 && testVector2.getSize() == 0
    && testVector3.getCapacity() == 129 && testVector3.getSize() == 0) // Check the class parameters to see if it is the expected value.
    {
        std::cout << "T1: makeVector() passed!\n";
    } else {
        std::cout << "T1: makeVector() failed!!!\n";
        exit(1);
    }

    // Print Stats
    std::cout << " Statistics of each vector:\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity:   " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity:  " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
} // Make Vector Test

template <typename T>
static void pushBackTest(myvector<T> &testVector, myvector<T> &testVector2, myvector<T> &testVector3) {
    for(int i = 0; i < 150; i++) { // Push 150 elements into each vector.
        testVector.pushBack(i);
        testVector2.pushBack(i);
        testVector3.pushBack(i);
        if (testVector.getSize() != i + 1 && testVector[i] != i
        && testVector2.getSize() != i + 1 && testVector2[i] != i
        && testVector3.getSize() != i + 1 && testVector3[i] != i) { // Check the size and the value that was copied.
            std::cout << "T2: pushBack() failed!!!\n";
            exit(1);
        }
    }
    // Print Stats
    std::cout << "T2: pushBack() passed!\n";
    std::cout << " Statistics of each vector:\n";
    std::cout << " *** NOTICE THE ADDRESS CHANGED DUE TO growVector() ***\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity: " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
} // pushBack() Test

template <typename T>
static void CopyConstructorTest(myvector<T> &testVector) {
    myvector<int> testCopy(testVector); // Use copy constructor.

    for(int i = 0; i < 150; i++) { // Compare every element in the array and if it doesn't match exit program and fail the test.
        if(testCopy[i] != testVector[i] or testCopy.getSize() != testVector.getSize() or testCopy.getCapacity() != testVector.getCapacity() or testCopy.getAddress() == testVector.getAddress()) {
            std::cout << "T9: Copy Constructor failed!!!\n\n";
            exit(1);
        }
    }
    // Print Stats
    std::cout << "T9: Copy Constructor passed!!!\n";
    std::cout << " Statistics of each vector:\n";
    std::cout << " *** NOTICE THE ADDRESS CHANGED ***\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testCopy    ===> Size = " << testCopy.getSize() << " | Capacity: " << testCopy.getCapacity() << " | Address: " << testCopy.getAddress() << "\n\n";
} // Copy Constructor Test

template <typename T>
static void OperationOverloadTest(myvector<T> &testVector) {
    myvector<int> testOperator;
    testOperator = testVector; // Use '=' operator to test
    int beforeValue = testVector[10]; // Record the value at index 10 before change.

    testVector[10] = 1000; // Assign the 10th value to 1000.
    if (testVector[10] != 1000) { // Check if the value changed to 1000 or not.
        std::cout << "T10: Operation Overload '[]' failed!!!\n";
        exit(1);
    }
    // Print Stats
    std::cout << "T10: Operation Overload '[]' passed!\n";
    std::cout << "testVector[10] before assignment was: " << beforeValue << std::endl;
    std::cout << "testVector[10] before assignment is:  " << testVector[10] << "\n";
    std::cout << "testOperator[10] value after assign:  " << testOperator[10] << "\n";
    testVector[10] = 10; // Reassign the value to 10 so that it doesn't break the other tests.
    std::cout << " *** TestVector[10] reverted to a value of " << beforeValue << " ***\n\n";

    // Test for '='
    for(int i = 0; i < 150; i++) { // Check if every member variable and data in array matches or not.
        if(testOperator[i] != testVector[i] or testOperator.getSize() != testVector.getSize() or testOperator.getCapacity() != testVector.getCapacity() or testOperator.getAddress() == testVector.getAddress()) {
            std::cout << "T11: Operation Overload '=' failed!!!\n";
            exit(1);
        }
    }
    std::cout << "T11: Operation Overload '=' passed!\n";

    // Print Stats
    std::cout << " Statistics of each vector:\n";
    std::cout << " *** NOTICE THE ADDRESS CHANGED ***\n";
    std::cout << " testVector   ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testOperator ===> Size = " << testOperator.getSize() << " | Capacity: " << testOperator.getCapacity() << " | Address: " << testOperator.getAddress() << "\n\n";

} // Operation Overload Test

template <typename T>
static void getTest(const myvector<T> &testVector, const myvector<T> &testVector2, const myvector<T> &testVector3) {
    for (int i = 0; i < 150; i++) { // get every element and compare it with the expected value.
        if (testVector.get(i) != i
        && testVector2.get(i) != i
        && testVector3.get(i) != i ) {
            std::cout << "T3: get() failed!!!\n";
            exit(1);
        }
    } // get() Test

    // Print Stats
    std::cout << "T3: get() passed!\n";
    std::cout << " Statistics of each vector:\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity: " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
}

template <typename T>
static void setTest(myvector<T> &testVector, myvector<T> &testVector2, myvector<T> &testVector3) {
    for (int i = 150; i > 0; i--) { // set a new value to every element in all the given myvector objects. I am reversing the data using set here.
        testVector.set(i - 1, 150 - i);
        testVector2.set(i - 1, 150 - i);
        testVector3.set(i - 1, 150 - i);
        if (   testVector.get(i - 1) != 150 - i
        && testVector2.get(i - 1) != 150 - i
        && testVector3.get(i - 1) != 150 - i) { // If the data doesn't change fail the test.
            std::cout << "T4: set() failed!!!\n";
            exit(1);
        }
    }
    // Print Stats
    std::cout << "T4: set() passed!\n";
    std::cout << " Statistics of each vector:\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity: " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
} // set() Test

template <typename T>
static void growVectorTest(myvector<T> &testVector, myvector<T> &testVector2, myvector<T> &testVector3) {
    // Record the initial capacity of the vectors.
    int vec1 = testVector.getCapacity();
    int vec2 = testVector2.getCapacity();
    int vec3 = testVector3.getCapacity();

    // Grow all the vectors.
    testVector.growVector();
    testVector2.growVector();
    testVector3.growVector();

    if (   testVector.getCapacity() != vec1 * 2
    && testVector2.getCapacity() != vec2 * 2
    && testVector3.getCapacity() != vec3 * 2) { // If the capacity of each vector hasn't doubled, fail the test.
        std::cout << "T5: growVector() failed!!!\n";
        exit(1);
    }
    // Print Stats
    std::cout << "T5: growVector() passed!\n";
    std::cout << " Statistics of each vector:\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity: " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
} // growVector() Test

template <typename T>
static void popBackTest(myvector<T> &testVector, myvector<T> &testVector2, myvector<T> &testVector3) {
    for(int i = 0; i < 150; i++) { // pop each element in each vector.
        testVector.popBack();
        testVector2.popBack();
        testVector3.popBack();
        if (testVector.getSize() != 150 - i - 1 && testVector[i] != 0
        && testVector2.getSize() != 150 - i - 1 && testVector2[i] != 0
        && testVector3.getSize() != 150 - i - 1 && testVector3[i] != 0) { // If the size hasn't decreased and the old value hasn't changed to null fail the test.
            std::cout << "T6: popBack() failed!!!\n";
            exit(1);
        }
    }
    // Print Test
    std::cout << "T6: popBack() passed!\n";
    std::cout << " Statistics of each; vector:\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity: " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
} // popBack() Test

template <typename T>
static void DestructorTest(myvector<T> &testVector, myvector<T> &testVector2, myvector<T> &testVector3) {
    // Record the current memory address of each vector.
    int *myvec1 = testVector.getAddress();
    int *myvec2 = testVector2.getAddress();
    int *myvec3 = testVector3.getAddress();

    // Destroy all the vectors
    testVector.~myvector();
    testVector2.~myvector();
    testVector3.~myvector();

    if (   testVector.getAddress() == myvec1
    && testVector2.getAddress() == myvec2
    && testVector3.getAddress() == myvec3) { // If the destroyed vectors still point to the same memory addresses fail the test.
        std::cout << "T7: ~myvector() failed!!!\n";
        exit(1);
    }
    std::cout << "T7: ~myvector() passed!\n";

    std::cout << " Statistics of each vector:\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity: " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
} // Destructor Test



static void templateTest(myvector<double> &doubleVector, myvector<int> &intVector, myvector<char> &strVector) {
    // Append values
    for (int i = 0 ; i < 4; i++) {
        intVector.pushBack(i);
        doubleVector.pushBack(1.01 * i);
        strVector.pushBack('A' + i);
    }

    // Test
    for (int i = 0; i < 4; i++) {
        if (intVector[i] != i or doubleVector[i] != 1.01 * i or strVector[i] != 'A' + i) {
            std::cout << "T12: Templates failed!!!\n";
            exit(1);
        }
    }
    std::cout << "T12: Templates passed!\n";

    // Print out the vectors
    std::cout << "intVector: { ";
    for (int i = 0;  i < 4; i++) {
        if (i < 3) {
            std::cout << intVector[i] << ", ";
        } else {
            std::cout << intVector[i];
        }

    }
    std::cout << " }\n";

    std::cout << "doubleVector: { ";
    for (int i = 0;  i < 4; i++) {
        if(i < 3) {
            std::cout << doubleVector[i] << ", ";
        } else {
            std::cout << doubleVector[i];
        }

    }
    std::cout << " }\n";

    std::cout << "strVector: { ";
    for (int i = 0;  i < 4; i++) {
        if (i < 3) {
            std::cout << strVector[i] << ", ";
        } else {
            std::cout << strVector[i];
        }
    }
    std::cout << " }\n\n";

} // Template Test

static void booleanOperatorOverloadTest(myvector<int> &intVector) {
    myvector<int> intCopy(intVector);

    if(intVector != intCopy or
    intVector > intCopy or
    intVector < intCopy) { // Compare and see if any values are not the same, fail the test.
        std::cout << "T13: Boolean operator overload failed!!!\n";
        exit(1);
    }
    if (intVector == intCopy or
    intVector >= intCopy or
    intVector <= intCopy) { // Compare and see if all the values are the same, pass the test.
        std::cout << "T13: Boolean operator overload passed!\n\n";
    }
} // Boolean operator overload test.

int main(int argc, const char * argv[]) {

    myvector<int> testVector(4);
    myvector<int> testVector2(10);
    myvector<int> testVector3(129);
    myvector<int> intVector(4);
    myvector<double> doubleVector(4);
    myvector<char> strVector(4);
    myvector<int> stlVector;
    



    // T1: Make Vector Test
    makeVectorTest(testVector, testVector2, testVector3);

    // T2: pushBack Test
    pushBackTest(testVector, testVector2, testVector3);

    // T9: Copy Constructor Test
    CopyConstructorTest(testVector);

    // T10, T11: Operation Overload Test
    OperationOverloadTest(testVector);

    // T3: get Test
    getTest(testVector, testVector2, testVector3);

    // T4: set Test
    setTest(testVector, testVector2, testVector3);

    // T5: growVector Test
    growVectorTest(testVector, testVector2, testVector3);

    // T6: pushBack Test
    popBackTest(testVector, testVector2, testVector3);

    // T7: Destructor Test
    DestructorTest(testVector, testVector2, testVector3);

    // T12: Template Test
    templateTest(doubleVector, intVector, strVector);

    // T13: Boolean Operator Overload Test
    booleanOperatorOverloadTest(intVector);
    
    // T14: STL
    
    stlVector.pushBack(5);
    stlVector.pushBack(-1);
    stlVector.pushBack(32);
    stlVector.pushBack(3);
    stlVector.pushBack(100);
    stlVector.pushBack(9);
    
    std::cout << "Working with STL:\n";
    std::cout << "Print out the elements in your vector with a for each loop:                                      { ";
    std::for_each(stlVector.begin(), stlVector.end(),[](int i){ std::cout << i << " ";});
    std::cout << "}\n";
    
    std::sort(stlVector.begin(), stlVector.end());
    std::cout << "Print out the elements in your sorted vector with a for each loop:                               { ";
    std::for_each(stlVector.begin(), stlVector.end(),[](int i){ std::cout << i << " ";});
    std::cout << "}\n"
    ;
    int *minElement = std::min_element(stlVector.begin(), stlVector.end());
    std::cout << "Find the minimum element:                                                                        " << *minElement << "\n";
    
    int init = 0;
    int sum = std::accumulate(stlVector.begin(), stlVector.end(), init);
    std::cout << "Find the sum:                                                                                    " << sum << "\n";
    
    std::count_if(stlVector.begin(), stlVector.end(),[](int i) { return i % 2 == 0; });
    int count = std::count_if(stlVector.begin(), stlVector.end(), [](int i) { return i % 2 == 0; });
    std::cout << "Find the number of even numbers:                                                                 " << count << "\n";

    std::cout << "[******************** ALL TESTS PASSED! ********************]\n\n";



    return 0;
}
