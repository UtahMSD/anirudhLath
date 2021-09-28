//
//  main.cpp
//  CommandLineArgs
//
//  Created by Anirudh Lath on 9/3/21.
//

#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    
    // The first element of the array (argv[0]) is the program name that is ./main"
    // Therefore the loop starts at 1 since the lab is asking us for printing just the commandline arguments.
    for(int i = 1; i < argc; i++) {
        cout << argv[i] << " ";
//        while (char a = **argv) {
//            cout << a;
//        }
    }
    cout << endl;
    return 0;
}
