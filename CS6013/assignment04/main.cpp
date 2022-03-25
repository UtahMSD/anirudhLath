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
    test();

    return 0;
}



