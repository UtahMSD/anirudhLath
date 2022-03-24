//
// Created by Anirudh Lath on 3/23/22.
//

#include <unistd.h>
#include <sys/mman.h>
#include <cstdlib>
#include "HashTable.h"

HashTable::HashTable() {
    this->capacity = 20;
    this->size = 0;
    this->table = (HashNode *) mmap(NULL, capacity * sizeof(HashNode), PROT_READ | PROT_WRITE | PROT_EXEC,
                                    MAP_ANONYMOUS |
    MAP_PRIVATE, 0, 0);

    if(table == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }
}

bool HashTable::insert(void *ptr, size_t memSize) {

    if( size < capacity - 1) {
        grow();
    }

    HashNode *temp = (HashNode*) mmap(NULL, sizeof(HashNode), PROT_READ | PROT_WRITE | PROT_EXEC,
                                       MAP_ANONYMOUS |
                                       MAP_PRIVATE, 0, 0);
    temp->ptr = ptr;
    temp->size = size;

    int hashIndex = hashCode(ptr);

    while(table[hashIndex].ptr != nullptr) {
        hashIndex++;
        hashIndex %= capacity;
    }

    if(table[hashIndex].ptr == nullptr) {
        size++;
        table[hashIndex].ptr = temp->ptr;
        table[hashIndex].size = temp->size;
        return true;
    }
    return false;
}

int HashTable::hashCode(void *ptr) {
    uintptr_t temp = (uintptr_t ) ptr;
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
    capacity = capacity * 2;
    HashNode *temp = (HashNode *) mmap(NULL, capacity * sizeof(HashNode), PROT_READ | PROT_WRITE | PROT_EXEC,
                                        MAP_ANONYMOUS |
                                        MAP_PRIVATE, 0, 0);
    this->size = 0;
    for (int i = 0; i < capacity; ++i) {
        if(table[i].ptr != nullptr) {
            HashNode *node = (HashNode*) mmap(NULL, sizeof(HashNode), PROT_READ | PROT_WRITE | PROT_EXEC,
                                              MAP_ANONYMOUS |
                                              MAP_PRIVATE, 0, 0);
            node->ptr = table[i].ptr;
            node->size = table[i].size;

            int hashIndex = hashCode(node->ptr);

            while(temp[hashIndex].ptr != nullptr) {
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

