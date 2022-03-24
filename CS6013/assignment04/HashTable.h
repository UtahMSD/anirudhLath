//
// Created by Anirudh Lath on 3/23/22.
//

#ifndef ASSIGNMENT04_HASHTABLE_H
#define ASSIGNMENT04_HASHTABLE_H

#include <cstdio>

class HashNode {
public:
    void *ptr;
    size_t size;
    bool flag;

    HashNode(void *ptr, size_t size) {
        this->ptr = ptr;
        this->size = size;
        this->flag = false;
    }

    HashNode() {
        this->size = NULL;
        this->ptr = nullptr;
        this->flag = false;
    }

};

class HashTable {
private:

    void grow();
    uint64_t hashCode(void *ptr);

public:
    HashTable();
    bool insert(void *ptr, size_t memSize);
    bool remove(void *ptr);
    size_t search(void *ptr);
    int length();
    ~HashTable();

    size_t capacity;
    size_t size;
    HashNode *table;
};

#endif //ASSIGNMENT04_HASHTABLE_H
