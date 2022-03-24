#include <iostream>
#include <vector>
#include "HashTable.h"
#include "MyAlloc.h"

using namespace std;

void test(){

    // HashTable test
//    HashTable table;
//    int *a = new int ;
//    int *b = new int ;
//    int *c = new int ;
//    int *d = new int ;
//    int *e = new int ;
//    int *f = new int ;
//    int *g = new int ;
//    int *h = new int ;
//    int *i = new int ;
//    cout << table.insert(a , 5);
//    cout << table.insert(a , 5);
//    cout << table.insert(b , 5);
//    cout << table.insert(c , 5);
//    cout << table.insert(d , 5);
//    cout << table.insert(e , 5);
//    cout << table.insert(f , 5);
//    cout << table.insert(g , 5);
//    cout << table.insert(h , 5);
//    cout << table.insert(i , 5);
//    cout << table.insert(a , 5);
//    cout << table.search(a);
//    cout << table.remove(a);
//    cout << table.remove(a);
//    cout << table.length();

    MyMalloc myMalloc;
    std::vector<void*> vector;

    for(int i = 0; i < 100; i++) {
        void* ptr = myMalloc.allocate((rand() % 100) + 10);
        vector.push_back(ptr);
    }

    for(int i = 0; i < vector.size(); i++){
        myMalloc.deallocate(vector[i]);
    }
}

int main() {
//    test();
    MyMalloc myMalloc2;
    std::vector<int> vector2;
    for(int i =0; i< 10000; i++){
        vector2.push_back(rand() % 10000 + 1);
    }

    std::chrono::time_point<std::chrono::system_clock> start, end; // timing start to end
    std::chrono::duration<double> durations; // to time a period of time
    std::vector<void*> myAllocator;

    // timing my own malloc:
    start = std::chrono::system_clock::now();// initialize starting time
    for(int i = 0; i < 10000; i ++){
        void* pointer = myMalloc2.allocate(vector2[i]);
        myAllocator.push_back(pointer); // allocate pointer into the myAllocator

    }
    // deAllocate:
    for(int i = 0; i < 10000; i++){
        myMalloc2.deallocate(myAllocator[i]);

    }
    //end time
    end = std::chrono::system_clock::now();// initialize end time
    durations = end - start;
    std::cout<< "my own Malloc running time: " << durations.count() <<std::endl; // to get malloc running time

    //Timing builtin Malloc:
    std::vector<void*> buildingAllocator;
    start = std::chrono::system_clock::now();// initialize starting time
    for(int i = 0; i < 10000; i++){
        void* pointer = malloc(vector2[i]);
        buildingAllocator.push_back(pointer);

    }
    // free malloc:
    for(int i = 0; i < 10000; i ++){
        free(buildingAllocator[i]);

    }

    end = std::chrono::system_clock::now();// initialize end time
    durations = end - start;
    std::cout<< "builtin malloc running time: " << durations.count() <<std::endl;

    //-> my malloc it is slower than the builtin malloc below
    //my own Malloc running time: 0.016135
    //builtin malloc running time: 0.004542
    return 0;
}



