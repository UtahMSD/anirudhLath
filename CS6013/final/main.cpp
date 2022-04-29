#include <iostream>

extern "C" {
    long fib(long num);
}

using namespace std;

int main() {
    cout << fib(6) << endl;
    return 0;
}