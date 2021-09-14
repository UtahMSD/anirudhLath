//
//  helper.hpp
//  MakeYourOwnVector
//
//  Created by Anirudh Lath on 9/13/21.
//

#ifndef helper_hpp
#define helper_hpp

#include <stdio.h>

struct vector {
    int* index;
    int capacity;
    int size;
};

vector makeVector( int initialCapacity );
void freeVector(vector &MyVec);
void pushBack(vector &myVec, int num);
void popBack(vector &myVec);
int get(vector myVec, int index);
void set(vector &myVec, int index, int newValue);
void growVector( vector &myVec );

#endif /* helper_hpp */
