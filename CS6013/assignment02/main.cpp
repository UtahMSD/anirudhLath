#include <iostream>

extern "C" {
    void sayHello();
}

extern puts;

int main() {
    sayHello();
    return 0;
}
