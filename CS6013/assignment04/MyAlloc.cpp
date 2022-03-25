//
// Created by Anirudh Lath on 3/23/22.
//

#include <sys/mman.h>
#include <cstdlib>
#include <unistd.h>
#include "MyAlloc.h"
#include "iostream"

MyMalloc::MyMalloc() : table(HashTable()) {
    std::cout << "Initialized hashtable" << std::endl;
}

void *MyMalloc::allocate(size_t bytesToAllocate) {
    void* ptr =  mmap(NULL, bytesToAllocate, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0); // 0 means file descriptor read, 0 = offset

    if(ptr == MAP_FAILED){
        perror("mmap failed");
        exit(1);
    }
    table.insert(ptr, (bytesToAllocate % getpagesize()));
    return ptr;
}

void MyMalloc::deallocate(void *ptr) {
    std::cout << table.search(ptr) << '\n';
    size_t len = table.search(ptr);
    int rc = munmap(ptr, len);
    if(rc != 0) {
        perror("de-allocation failed");
    }
    else {
        std::cout << "dealloc successful\n";
        table.remove(ptr);
    }
}
