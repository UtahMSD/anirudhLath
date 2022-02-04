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

	std::cout << "_sayHello():\n";
	_sayHello();

	std::cout << "\nmyPuts():\n";
	myPuts(s, len);

	std::cout << "\nmyGTOD():\n";
	std::cout << myGTOD().tv_sec;
	std::cout << myGTOD().tv_usec << std::endl;
	return 0;
}
