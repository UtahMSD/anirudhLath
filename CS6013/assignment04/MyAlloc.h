//
// Created by Anirudh Lath on 3/23/22.
//

#ifndef ASSIGNMENT04_MYALLOC_H
#define ASSIGNMENT04_MYALLOC_H

#include "HashTable.h"

class MyMalloc {
public:
    HashTable table;
    MyMalloc();
    void* allocate(size_t bytesToAllocate);
    void deallocate(void* ptr);
};
#endif //ASSIGNMENT04_MYALLOC_H
