//
//  main.cpp
//  MakeYourOwnVector
//
//  Created by Anirudh Lath on 9/13/21.
//
#include "helper.hpp"
#include <iostream>



void makeVectorTest(const myvector &testVector, const myvector &testVector2, const myvector &testVector3) {
    if (testVector.getCapacity() == 4 && testVector.getSize() == 0
        && testVector2.getCapacity() == 10 && testVector2.getSize() == 0
        && testVector3.getCapacity() == 129 && testVector3.getSize() == 0)
    {
        std::cout << "T1: makeVector() passed!\n";
    } else {
        std::cout << "T1: makeVector() failed!!!\n";
        exit(1);
    }
    std::cout << " Statistics of each vector:\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity:   " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity:  " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
}

static void pushBackTest(myvector &testVector, myvector &testVector2, myvector &testVector3) {
    for(int i = 0; i < 150; i++) {
        testVector.pushBack(i);
        testVector2.pushBack(i);
        testVector3.pushBack(i);
        if (testVector.getSize() != i + 1 && testVector.getIndex(i) != i
            && testVector2.getSize() != i + 1 && testVector2.getIndex(i) != i
            && testVector3.getSize() != i + 1 && testVector3.getIndex(i) != i) {
            std::cout << "T2: pushBack() failed!!!\n";
            exit(1);
        }
    }
    
    std::cout << "T2: pushBack() passed!\n";
    std::cout << " Statistics of each vector:\n";
    std::cout << " *** NOTICE THE ADDRESS CHANGED DUE TO growVector() ***\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity: " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
}

static void CopyConstructorTest(myvector &testVector) {
    myvector testCopy(testVector);
    
    for(int i = 0; i < 150; i++) {
        if(testCopy[i] != testVector[i] or testCopy.getSize() != testVector.getSize() or testCopy.getCapacity() != testVector.getCapacity() or testCopy.getAddress() == testVector.getAddress()) {
            std::cout << "T9: Copy Constructor failed!!!\n\n";
            exit(1);
        }
    }
    
    std::cout << "T9: Copy Constructor passed!!!\n";
    std::cout << " Statistics of each vector:\n";
    std::cout << " *** NOTICE THE ADDRESS CHANGED ***\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testCopy    ===> Size = " << testCopy.getSize() << " | Capacity: " << testCopy.getCapacity() << " | Address: " << testCopy.getAddress() << "\n\n";
}

static void OperationOverloadTest(myvector &testVector) {
    myvector testOperator;
    testOperator = testVector;
    int beforeValue = testVector[10];
    
    testVector[10] = 1000;
    //std::cout << "Testing operator testVector[10] = 1000 ==> " << testVector[10] << std::endl;
    if (testVector[10] != 1000) {
        std::cout << "T10: Operation Overload '[]' failed!!!\n";
        exit(1);
    }
    std::cout << "T10: Operation Overload '[]' passed!\n";
    std::cout << "testVector[10] before assignment was: " << beforeValue << std::endl;
    std::cout << "testVector[10] before assignment is:  " << testVector[10] << "\n";
    std::cout << "testOperator[10] value after assign:  " <<testOperator[10] << "\n";
    testVector[10] = 10;
    std::cout << " *** TestVector[10] reverted to a value of " << beforeValue << " ***\n\n";
    
    for(int i = 0; i < 150; i++) {
        if(testOperator[i] != testVector[i] or testOperator.getSize() != testVector.getSize() or testOperator.getCapacity() != testVector.getCapacity() or testOperator.getAddress() == testVector.getAddress()) {
            std::cout << "T11: Operation Overload '=' failed!!!\n";
            exit(1);
        }
    }
    std::cout << "T11: Operation Overload '=' passed!\n";
    
    std::cout << " Statistics of each vector:\n";
    std::cout << " *** NOTICE THE ADDRESS CHANGED ***\n";
    std::cout << " testVector   ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testOperator ===> Size = " << testOperator.getSize() << " | Capacity: " << testOperator.getCapacity() << " | Address: " << testOperator.getAddress() << "\n\n";
    
}

static void getTest(const myvector &testVector, const myvector &testVector2, const myvector &testVector3) {
    for (int i = 0; i < 150; i++) {
        if (testVector.get(i) != i
            && testVector2.get(i) != i
            && testVector3.get(i) != i ) {
            std::cout << "T3: get() failed!!!\n";
            exit(1);
        }
    }
    
    std::cout << "T3: get() passed!\n";
    std::cout << " Statistics of each vector:\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity: " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
}

static void setTest(myvector &testVector, myvector &testVector2, myvector &testVector3) {
    for (int i = 150; i > 0; i--) {
        testVector.set(i - 1, 150 - i);
        testVector2.set(i - 1, 150 - i);
        testVector3.set(i - 1, 150 - i);
        if (   testVector.get(i - 1) != 150 - i
            && testVector2.get(i - 1) != 150 - i
            && testVector3.get(i - 1) != 150 - i) {
            std::cout << "T4: set() failed!!!\n";
            exit(1);
        }
    }
    std::cout << "T4: set() passed!\n";
    std::cout << " Statistics of each vector:\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity: " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
}

static void growVectorTest(myvector &testVector, myvector &testVector2, myvector &testVector3) {
    int vec1 = testVector.getCapacity();
    int vec2 = testVector2.getCapacity();
    int vec3 = testVector3.getCapacity();
    testVector.growVector();
    testVector2.growVector();
    testVector3.growVector();
    
    if (   testVector.getCapacity() != vec1 * 2
        && testVector2.getCapacity() != vec2 * 2
        && testVector3.getCapacity() != vec3 * 2) {
        std::cout << "T5: growVector() failed!!!\n";
        exit(1);
    }
    std::cout << "T5: growVector() passed!\n";
    std::cout << " Statistics of each vector:\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity: " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
}

static void pushBackTests(myvector &testVector, myvector &testVector2, myvector &testVector3) {
    for(int i = 0; i < 150; i++) {
        testVector.popBack();
        testVector2.popBack();
        testVector3.popBack();
        if (testVector.getSize() != 150 - i - 1 && testVector.getIndex(i) != 0
            && testVector2.getSize() != 150 - i - 1 && testVector2.getIndex(i) != 0
            && testVector3.getSize() != 150 - i - 1 && testVector3.getIndex(i) != 0) {
            std::cout << "T6: popBack() failed!!!\n";
            exit(1);
        }
    }
    std::cout << "T6: popBack() passed!\n";
    std::cout << " Statistics of each; vector:\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity: " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
}

static void DestructorTest(myvector &testVector, myvector &testVector2, myvector &testVector3) {
    int *myvec1 = testVector.getAddress();
    int *myvec2 = testVector2.getAddress();
    int *myvec3 = testVector3.getAddress();
    
    myvector vec4(testVector);
    
    testVector.~myvector();
    testVector2.~myvector();
    testVector3.~myvector();
    
    if (   testVector.getAddress() == myvec1
        && testVector2.getAddress() == myvec2
        && testVector3.getAddress() == myvec3) {
        std::cout << "T7: ~myvector() failed!!!\n";
        exit(1);
    }
    std::cout << "T7: ~myvector() passed!\n";
    
    std::cout << " Statistics of each vector:\n";
    std::cout << " testVector  ===> Size = " << testVector.getSize() << " | Capacity: " << testVector.getCapacity() << " | Address: " << testVector.getAddress() << "\n";
    std::cout << " testVector2 ===> Size = " << testVector2.getSize() << " | Capacity: " << testVector2.getCapacity() << " | Address: " << testVector2.getAddress() << "\n";
    std::cout << " testVector3 ===> Size = " << testVector3.getSize() << " | Capacity: " << testVector3.getCapacity() << " | Address: " << testVector3.getAddress() << "\n\n";
}



int main(int argc, const char * argv[]) {
    
    myvector testVector(4);
    myvector testVector2(10);
    myvector testVector3(129);
    
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
    pushBackTests(testVector, testVector2, testVector3);
    
    // T7: Destructor Test
    DestructorTest(testVector, testVector2, testVector3);
    
    
    
    std::cout << "[******************** ALL TESTS PASSED! ********************]\n\n";
    
    
    
    return 0;
}
