#include <iostream>
#include <vector>
#include <cstdlib>
#include "HashTable.h"
#include "MyAlloc.h"
#include "chrono"

using namespace std;
using namespace std::chrono;

MyMalloc myMalloc1;

// Commented out the overidden functions to time test functions.
/*void *malloc(size_t size) {
    return myMalloc1.allocate(size);
}

void free(void *ptr) {
    myMalloc1.deallocate(ptr);
}*/

void malloctest(){
    MyMalloc myMalloc;
    std::vector<void*> vector;

    for(int i = 0; i < 1000; i++) {
        void* ptr = myMalloc.allocate((rand() % 100) + 10);
        vector.push_back(ptr);
    }

    for(int i = 0; i < vector.size(); i++){
        myMalloc.deallocate(vector[i]);
    }
}

void hashtest() {
    HashTable table;
    vector<void*> vector;

    for(int i = 0; i < 100; i++) {
        int *ptr = new int;
        table.insert(ptr, rand() % 100 + 1);
        vector.push_back(ptr);
    }

    for(int i = 0; i < vector.size(); i++) {
        if(!table.remove(vector[i])) {
            cout << i << endl;
            cout << "test failed" << endl;
            exit(1);
        }
    }
}

void timedMallocTest() {
    MyMalloc myMalloc; // Create the allocator
    int LOOP_SIZE = 10000;
    vector<void *> mypointers; // Create a vector of pointers to allocate
    vector<void *> pointers; // Create a vector of pointers to allocate
    vector<size_t> sizes; // Create a vector of sizes to allocate

    for (int i = 0; i < LOOP_SIZE; ++i) {
        int *a = new int;
        size_t s = (rand() % 1000) + 1;
        pointers.push_back(a);
        sizes.push_back(s);
    }

    // Record time taken to allocate memory using my allocator.
    auto start = high_resolution_clock::now();
    for (int i = 0; i < LOOP_SIZE; ++i) {
        mypointers.push_back(myMalloc.allocate(sizes[i]));
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    int myMallocTime = duration.count();


    // Record time taken to allocate memory using malloc() system function
    start = high_resolution_clock::now();
    for (int i = 0; i < LOOP_SIZE; ++i) {
        pointers.push_back(malloc(sizes[i]));
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    int mallocTime = duration.count();

    // Record time taken to free memory using my deallocator
    start = high_resolution_clock::now();
    for (int i = 0; i < LOOP_SIZE; ++i) {
        myMalloc.deallocate(mypointers[i]);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    int myDeallocTime = duration.count();

    // Record time taken to free memory using free() system function
    start = high_resolution_clock::now();
    for (int i = 0; i < LOOP_SIZE; ++i) {
        free(pointers[i]);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    int freeTime = duration.count();


    cout << "------ MyMalloc Timings ------" << endl;
    cout << "Allocation per unit    : ~" << myMallocTime/LOOP_SIZE << " ns" << endl;
    cout << "De-allocation per unit : ~" << myDeallocTime/LOOP_SIZE << " ns" << endl << endl;

    cout << "------ System Timings -------" << endl;
    cout << "Allocation per unit    : ~" << mallocTime/LOOP_SIZE << " ns" << endl;
    cout << "De-allocation per unit : ~" << freeTime/LOOP_SIZE << " ns" << endl;

}

int main() {
    hashtest();
    malloctest();
    timedMallocTest();
    return 0;
}



