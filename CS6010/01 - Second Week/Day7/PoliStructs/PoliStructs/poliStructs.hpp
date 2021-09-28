//
//  poliStructs.hpp
//  PoliStructs
//
//  Created by Anirudh Lath on 8/31/21.
//

#ifndef poliStructs_hpp
#define poliStructs_hpp

#include <stdio.h>
#include <string>
#include <vector>

struct Politician {
    std::string name;
    std::string party;
    std::string classification;
};

std::vector<Politician> javacans( std::vector<Politician> poli);
std::vector<Politician> federalCplusers( std::vector<Politician> poli);

#endif /* poliStructs_hpp */
