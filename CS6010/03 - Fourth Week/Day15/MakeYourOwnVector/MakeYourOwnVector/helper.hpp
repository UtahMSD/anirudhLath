//
//  helper.hpp
//  MakeYourOwnVector
//
//  Created by Anirudh Lath on 9/13/21.
//

#ifndef helper_hpp
#define helper_hpp

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

template <typename T>
class myvector {
private:
    
    // Variables
    T * index;
    int capacity;
    int size;
    
public:
    
    // Constructor
    myvector();
    myvector( int initialCapacity );
    myvector(const myvector<T> & vec);
    
    
    
    // Public Methods
    void growVector();
    int getSize() const {return size;}
    T* getAddress() const {return index;}
    int getCapacity() const {return capacity;}
    //int getIndex(int i) const {return index[i];}
    void pushBack(T data);
    void popBack();
    T get(int i) const;
    void set(int i, T newValue);
    T* begin();
    T* begin() const;
    T* end();
    T* end() const;
    
    // Destructor
    ~myvector();
    
    // Operation overload
    myvector& operator=(const myvector & rhs);
    T operator[](int i) const;
    T & operator[](int i);
    bool operator==(myvector<T> rhs);
    bool operator!=(myvector<T> rhs);
    bool operator>(myvector<T> rhs);
    bool operator>=(myvector<T> rhs);
    bool operator<=(myvector<T> rhs);
    bool operator<(myvector<T> rhs);
    
};

template <typename T>
myvector<T>::myvector(){
    capacity = 10;
    size = 0;
    index = new T[10];
} // Default Constructor

template <typename T>
myvector<T>::myvector( int initialCapacity ) {
    capacity = initialCapacity;
    size = 0;
    index = new T[initialCapacity];
} // Constructor with initial capacity param

template <typename T>
myvector<T>::myvector(const myvector & rhs) {
    T * newData = new T[rhs.capacity]; // Create own memory allocation
    for(int i = 0; i < rhs.size; i++) {
        newData[i] = rhs.index[i];
    }
    capacity = rhs.capacity;
    size = rhs.size;
    index = newData;
    
    if(index == rhs.index) {
        std::cout << "Memory reallocation warning. Please check the code." << std::endl;
        exit(1); // If this and rhs are pointing to the same address in memory, notify the user about it. Simple error check.
    }
} // Copy Constructor

template <typename T>
myvector<T>::~myvector() {
    index = nullptr;
    delete [] index;
    capacity = 0;
} // Destructor

template <typename T>
void myvector<T>::pushBack(T data) {
    if (size < capacity) {
        index[size] = data;
    } else {
        growVector();
        index[size] = data;
    }
    size++;
}

template <typename T>
void myvector<T>::popBack() {
    if (size > 0) {
        size--;
        index[size] = NULL;
    } else {
        std::cout << "There are no elements in this vector to pop." << std::endl;
        exit(1);
    }
    

}

template <typename T>
T myvector<T>::get(int i) const {
    if (i >= size) {
        std::cout << "The index you have entered is out of range." << std::endl;
        exit(1);
    }
    return index[i];
}

template <typename T>
void myvector<T>::set(int i, T newValue) {
    if (i < size) {
        *(index + i) = newValue;
    } else {
        std::cout << "The index you have entered is out of range. Please try again with a valid index." << std::endl;
        exit(1);
    }
}

template <typename T>
void myvector<T>::growVector() {
    capacity *= 2;
    myvector temp(*this);
    this -> ~myvector();
    index = temp.index;
    size = temp.size;
    capacity = temp.capacity;
}

template <typename T>
myvector<T>& myvector<T>::operator=(const myvector & rhs) {
    // Reassignment memory leak protection
    if (this == &rhs) {
        return *this;
    }
    
    T * newData = new T[rhs.capacity];
    for(int i = 0; i < rhs.size; i++) {
        newData[i] = rhs.index[i];
    }
    capacity = rhs.capacity;
    size = rhs.size;
    delete [] index;
    index = newData;
    
    if(index == rhs.index) {
        std::cout << "Memory reallocation warning. Please check the code." << std::endl;
        exit(1); // If this and rhs are pointing to the same address in memory, notify the user about it. Simple error check.
    }
    
    return *this;
}

template <typename T>
T myvector<T>::operator[](int i) const {
    if (i < 0 or i >= size) {
        std::cout << "The index you have entered is out of range. Program will not exit." << std::endl;
        exit(1);
    }
    int value = index[i];
    return value;
}

template <typename T>
T & myvector<T>::operator[](int i) {
    if (i < 0 or i >= size) {
        std::cout << "The index you have entered is out of range. Program will not exit." << std::endl;
        exit(1);
    }
    return index[i];
}

template <typename T>
bool myvector<T>::operator==(myvector<T> rhs) {
    if (size == rhs.size) {
        for(int i = 0; i < size; i++) {
            if (index[i] != rhs.index[i]) {
                return false;
            }
        }
    } else {
        std::cout << "The objects cannot be compared they are of different sizes.";
        exit(1);
    }
    return true;
}

template <typename T>
bool myvector<T>::operator!=(myvector<T> rhs) {
    if (size == rhs.size) {
        for(int i = 0; i < size; i++) {
            if (index[i] == rhs.index[i]) {
                return false;
            }
        }
    } else {
        std::cout << "The objects cannot be compared they are of different sizes.";
        exit(1);
    }
    return true;
}

template <typename T>
bool myvector<T>::operator>(myvector<T> rhs) {
    if (size == rhs.size) {
        for(int i = 0; i < size; i++) {
            if (index[i] <= rhs.index[i]) {
                return false;
            }
        }
    } else {
        std::cout << "The objects cannot be compared they are of different sizes.";
        exit(1);
    }
    return true;
}

template <typename T>
bool myvector<T>::operator>=(myvector<T> rhs) {
    if (size == rhs.size) {
        for(int i = 0; i < size; i++) {
            if (index[i] < rhs.index[i]) {
                return false;
            }
        }
    } else {
        std::cout << "The objects cannot be compared they are of different sizes.";
        exit(1);
    }
    return true;
}

template <typename T>
bool myvector<T>::operator<=(myvector<T> rhs) {
    if (size == rhs.size) {
        for(int i = 0; i < size; i++) {
            if (index[i] > rhs.index[i]) {
                return false;
            }
        }
    } else {
        std::cout << "The objects cannot be compared they are of different sizes.";
        exit(1);
    }
    return true;
}

template <typename T>
bool myvector<T>::operator<(myvector<T> rhs) {
    if (size == rhs.size) {
        for(int i = 0; i < size; i++) {
            if (index[i] >= rhs.index[i]) {
                return false;
            }
        }
    } else {
        std::cout << "The objects cannot be compared they are of different sizes.";
        exit(1);
    }
    return true;
}

template <typename T>
T* myvector<T>::begin() {
    return index;
}

template <typename T>
T* myvector<T>::begin() const {
    return index;
}

template <typename T>
T* myvector<T>::end() {
    return index + (size - 1);
}

template <typename T>
T* myvector<T>::end() const {
    return index + (size - 1);
}

#endif /* helper_hpp */
