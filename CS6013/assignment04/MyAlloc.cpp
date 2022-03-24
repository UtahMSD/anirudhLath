//
// Created by Anirudh Lath on 3/23/22.
//

#include <sys/mman.h>
#include <cstdlib>
#include "MyAlloc.h"
#include "iostream"

MyMalloc::MyMalloc() : table(HashTable()) {
    std::cout << "Initialized hashtable" << std::endl;
}
