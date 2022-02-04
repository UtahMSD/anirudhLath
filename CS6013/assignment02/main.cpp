#include <iostream>
#include <sys/time.h>

extern "C" {
	void _sayHello();
	int myPuts(const char* s, int len);
	timeval myGTOD();

}

int main() {
	const char *s;
	int len = 3;

	_sayHello();
	myPuts(s, len);
	std::cout << myGTOD().tv_sec;
	std::cout << myGTOD().tv_usec;
	return 0;
}
