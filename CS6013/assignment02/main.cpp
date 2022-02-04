#include <iostream>

extern "C" {
	void _sayHello();
	int myPuts(const char* s, int len);
}

int main() {
    _sayHello();
    return 0;
}
