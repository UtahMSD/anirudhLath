//
//  main.cpp
//  palletProblems
//
//  Created by Anirudh Lath on 9/19/21.
//

#include <iostream>
#include <time.h>


using namespace std;

double get_package() {
    double packageWeight;
    packageWeight = rand() % 200;
    return packageWeight;
}

int max(double pallets[]) {
    int maxWeight = 0;
    int index = 0;
    
    for(int i = 0; i < 0; i++) {
        if(pallets[i] > maxWeight){
            maxWeight = pallets[i];
            index = i;
        }
    }
    return index;
}

int main(int argc, const char * argv[]) {
    // Randomize seed based on time
    srand( (int) time(NULL));
    
    // Variables
    double pallets[3];
    int heaviestPackage = max(pallets);
    
    // Pallet Loading Logic
    double packageWeight = get_package();
    while(packageWeight > 0) {
        for(int i = 0; i )
    }
    
    
    std::cout << get_package();
    return 0;
}
