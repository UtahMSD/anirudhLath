//
//  main.cpp
//  ArrayCopy
//
//  Created by Anirudh Lath on 9/13/21.
//

#include <iostream>

using namespace std;

int* f(){
    
    int x = 5;
    cout << &x << endl;
    return &x;
    
}

double* CopyArray(double nums[], int numArrSize) {
    //cout << &nums[0] << " " << nums[0] << endl;
    double numbers[numArrSize];
    for( int i = 0; i < numArrSize; i++ ) {
        numbers[i] = nums[i];
    }
    //cout << &numbers[0] << " " << numbers[0] << endl;
    return &numbers[0];
}



int main(int argc, const char * argv[]) {
    
    double* pX = new double[5];
    CopyArray(pX, 5);
    
    //int* y = f(); //Commented out due to mem breakpoints.
    //cout << *y << " " << y << " " << &y << endl;
    //The bug is that the function f() is pointing to the address of its local variable x. Which is stored in the heap memory and cleared and unallocated after its been run. Therefore the memory is not allocated to this program. While it may work but that is a memory error because it is accessing and treating a decommissioned buffer as if it was allocated to the program and will not cause any bugs.
}
