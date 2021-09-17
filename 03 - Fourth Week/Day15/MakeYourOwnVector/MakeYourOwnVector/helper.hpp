//
//  helper.hpp
//  MakeYourOwnVector
//
//  Created by Anirudh Lath on 9/13/21.
//

#ifndef helper_hpp
#define helper_hpp

#include <stdio.h>

class myvector {
private:
    
    // Variables
    int* index;
    int capacity;
    int size;
    
public:
    
    // Constructor
    myvector();
    myvector( int initialCapacity );
    myvector(const myvector & vec);
    
    
    
    // Public Methods
    void growVector();
    int getSize() const;
    int* getAddress() const;
    int getCapacity() const;
    int getIndex(int i) const;
    void pushBack(int num);
    void popBack();
    int get(int i) const;
    void set(int i, int newValue);
    
    // Destructor
    ~myvector();
    
    // Operation overload
    myvector& operator=(const myvector & rhs);
    int operator[](int i) const;
    int & operator[](int i);
    
};

#endif /* helper_hpp */
