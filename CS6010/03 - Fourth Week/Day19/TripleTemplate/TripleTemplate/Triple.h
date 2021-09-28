//
//  Triple.h
//  TripleTemplate
//
//  Created by Anirudh Lath on 9/17/21.
//

#ifndef Triple_h
#define Triple_h

template <typename T>
struct Triple {
    T a;
    T b;
    T c;
   
public:
    T sum() { return a + b + c; }
};

#endif /* Triple_h */
