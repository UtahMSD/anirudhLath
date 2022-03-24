//
// Created by Anirudh Lath on 3/23/22.
//

#include <unistd.h>
#include <sys/mman.h>
#include <cstdlib>
#include "HashTable.h"

HashTable::HashTable() {
    this->capacity = getpagesize() / sizeof(HashNode);
    this->size = 0;
    this->table = (HashNode**) mmap(NULL, capacity * sizeof(HashNode), PROT_READ | PROT_WRITE | PROT_EXEC,
                                    MAP_ANONYMOUS |
    MAP_PRIVATE, 0, 0);

    if(table == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    for(int i = 0; i < capacity; i++) {
        table[i] = NULL;
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

    while(table[hashIndex] != NULL) {
        hashIndex++;
        hashIndex %= capacity;
    }

    if(table[hashIndex] == NULL) {
        size++;
        table[hashIndex] = temp;
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
    while (table[hashIndex] != NULL) {
        if(table[hashIndex]->ptr == ptr) {
            table[hashIndex]->ptr = NULL;
            table[hashIndex]->size = NULL;
            table[hashIndex] = NULL;
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
    while (table[hashIndex] != NULL) {
        if(counter++ > capacity) {
            return NULL;
        }
        if(table[hashIndex]->ptr == ptr) {
            return table[hashIndex]->size;
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
    HashNode **temp = (HashNode**) mmap(NULL, capacity * sizeof(HashNode), PROT_READ | PROT_WRITE | PROT_EXEC,
                                        MAP_ANONYMOUS |
                                        MAP_PRIVATE, 0, 0);
    this->size = 0;
    for (int i = 0; i < capacity; ++i) {
        if(table[i] != NULL) {
            HashNode *node = (HashNode*) mmap(NULL, sizeof(HashNode), PROT_READ | PROT_WRITE | PROT_EXEC,
                                              MAP_ANONYMOUS |
                                              MAP_PRIVATE, 0, 0);
            node->ptr = table[i]->ptr;
            node->size = table[i]->size;

            int hashIndex = hashCode(node->ptr);

            while(temp[hashIndex] != NULL) {
                hashIndex++;
                hashIndex %= capacity;
            }

            if(temp[hashIndex] == NULL) {
                size++;
                temp[hashIndex] = node;
            }
        }
    }
    this->table = temp;
}

