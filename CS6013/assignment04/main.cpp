#include <iostream>
#include "HashTable.h"
#include "MyAlloc.h"

int main() {
    HashTable table;
    int *a = new int ;
    table.insert(a , 5);
    return 0;
}
