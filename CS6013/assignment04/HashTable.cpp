//
// Created by Anirudh Lath on 3/23/22.
//

#include <unistd.h>
#include <sys/mman.h>
#include <cstdlib>
#include <iostream>
#include "HashTable.h"

HashTable::HashTable() {
    this->capacity = 10000; // Set to 10000 to avoid time spent growing for timing experiment.
    this->size = 0;
    this->table = (HashNode *) mmap(nullptr, capacity * sizeof(HashNode), PROT_READ | PROT_WRITE,
                                    MAP_ANONYMOUS |
    MAP_PRIVATE, 0, 0);

    if(table == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }
}

bool HashTable::insert(void *ptr, size_t memSize) {

    if( size > capacity / 2 ) {
        grow();
    }

    int hashIndex = hashCode(ptr);

    while(table[hashIndex].ptr != nullptr) {
        if(table[hashIndex].ptr == ptr) {
            return false;
        }
        hashIndex++;
        hashIndex %= capacity;

    }
    size++;
    table[hashIndex].ptr = ptr;
    table[hashIndex].size = memSize;
    return true;

/*    if(table[hashIndex].ptr == nullptr) {

    }
    return false;*/
}

int HashTable::hashCode(void *ptr) {
    int result = 10;
    int c = (size_t) ptr;
    result = 37 * result + c;

    return abs(result) % capacity;
}

bool HashTable::remove(void *ptr) {

    int hashIndex = hashCode(ptr);
    int count = 0;
    while (table[hashIndex].ptr != ptr) {
        hashIndex++;
        count++;
        if( count > capacity) {
            return false;
        }
        hashIndex %= capacity;
    }
    table[hashIndex].ptr = nullptr;
    table[hashIndex].size = NULL;
    size--;
    return true;

}

size_t HashTable::search(void *ptr) {

    int hashIndex = hashCode(ptr);
    int count = 0;
    while (table[hashIndex].ptr != ptr) {
        hashIndex++;
        count++;
        if( count > capacity) {
            return NULL;
        }
        hashIndex %= capacity;
    }
    return table[hashIndex].size;

    /*int hashIndex = hashCode(ptr);
    int counter = 0;
    while (table[hashIndex].ptr != nullptr) {
        if(counter++ > capacity) {
            std::cout << "not found\n";
            return NULL;
        }
        if(table[hashIndex].ptr == ptr) {
            std::cout << "found\n";
            return table[hashIndex].size;
        }
        hashIndex++;
        hashIndex %= capacity;
    }

    return NULL;*/
}

int HashTable::length() {
    return size;
}

void HashTable::grow() {
    int oldCapacity = this->capacity;
    HashNode *old = this->table;
    this->capacity = oldCapacity * 2;
    HashNode *temp = (HashNode *) mmap(nullptr, capacity * sizeof(HashNode), PROT_READ | PROT_WRITE,
                                       MAP_ANONYMOUS |
                                       MAP_PRIVATE, 0, 0);
    if(temp == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }
    this->table = temp;
    this->size = 0;
    for (int i = 0; i < oldCapacity; ++i) {
        if(old[i].ptr != nullptr) {
            insert(old[i].ptr, old[i].size);
/*            HashNode *node = (HashNode*) mmap(NULL, sizeof(HashNode), PROT_READ | PROT_WRITE ,
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
            }*/
        }
    }
}

HashTable::~HashTable() {
    this->table = nullptr;
    this->size = NULL;
    this->capacity = NULL;
}

