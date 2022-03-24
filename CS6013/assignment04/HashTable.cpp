//
// Created by Anirudh Lath on 3/23/22.
//

#include <unistd.h>
#include <sys/mman.h>
#include <cstdlib>
#include <iostream>
#include "HashTable.h"

HashTable::HashTable() {
    this->capacity = 10;
    this->size = 0;
    this->table = (HashNode *) mmap(NULL, capacity * sizeof(HashNode), PROT_READ | PROT_WRITE,
                                    MAP_ANONYMOUS |
    MAP_PRIVATE, 0, 0);

    if(table == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }
}

bool HashTable::insert(void *ptr, size_t memSize) {

    if( size > capacity - 5) {
        grow();
    }

    uint64_t hashIndex = hashCode(ptr);

    while(table[hashIndex].ptr != nullptr) {
        if(table[hashIndex].ptr == ptr) {
            return false;
        }
        hashIndex++;
        hashIndex %= capacity;

    }

    if(table[hashIndex].ptr == nullptr) {
        size++;
        table[hashIndex].ptr = ptr;
        table[hashIndex].size = memSize;
        return true;
    }
    return false;
}

uint64_t HashTable::hashCode(void *ptr) {
    uint64_t temp = (uint64_t ) ptr;

    return temp % capacity;
}

bool HashTable::remove(void *ptr) {
    int hashIndex = hashCode(ptr);
    while (table[hashIndex].ptr != nullptr) {
        if(table[hashIndex].ptr == ptr) {
            table[hashIndex].ptr = nullptr;
            table[hashIndex].size = NULL;
            size--;
            return true;
        }
        hashIndex++;
        hashIndex %= capacity;
    }
    return false;
}

size_t HashTable::search(void *ptr) {
    int hashIndex = hashCode(ptr);
    int counter = 0;
    while (table[hashIndex].ptr != nullptr) {
        if(counter++ > capacity) {
            return NULL;
        }
        if(table[hashIndex].ptr == ptr) {
            return table[hashIndex].size;
        }
        hashIndex++;
        hashIndex %= capacity;
    }
    return NULL;
}

int HashTable::length() {
    return size;
}

void HashTable::grow() {
    std::cout << "Growing arr";
    capacity = capacity * 2;
    HashNode *temp = (HashNode *) mmap(NULL, capacity * sizeof(HashNode), PROT_READ | PROT_WRITE ,
                                        MAP_ANONYMOUS |
                                        MAP_PRIVATE, 0, 0);
    this->size = 0;
    for (int i = 0; i < capacity / 2; ++i) {
        if(table[i].ptr != nullptr) {
            HashNode *node = (HashNode*) mmap(NULL, sizeof(HashNode), PROT_READ | PROT_WRITE ,
                                              MAP_ANONYMOUS |
                                              MAP_PRIVATE, 0, 0);
            node->ptr = table[i].ptr;
            node->size = table[i].size;

            int hashIndex = hashCode(node->ptr);

            while(temp[hashIndex].ptr != nullptr) {
                if(temp[hashIndex].ptr == node->ptr) {
                    break;
                    std::cout << "Error growing";
                }
                hashIndex++;
                hashIndex %= capacity;
            }

            if(temp[hashIndex].ptr == nullptr) {
                size++;
                temp[hashIndex].ptr = node->ptr;
                temp[hashIndex].size = node->size;
            }
        }
    }
    this->table = temp;
}

HashTable::~HashTable() {
    this->table = nullptr;
    this->size = NULL;
    this->capacity = NULL;
}

