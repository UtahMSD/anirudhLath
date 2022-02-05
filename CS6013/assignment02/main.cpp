#include <iostream>
#include <sys/time.h>

extern "C" {
	void sayHello();
	int myPuts(const char* s, int len);
	timeval myGTOD();

}

int main() {
	const char *s = "Hello, world!";
	int len = 13;
	struct timeval currentTime;

	std::cout << "\nsayHello():\n";
	sayHello();

	std::cout << "\nmyPuts():\n";
	myPuts(s, len);

	std::cout << "\n\nmyGTOD():\n";
	struct timeval mygtod = myGTOD();
	std::cout << mygtod.tv_sec << std::endl;
	std::cout << mygtod.tv_usec << std::endl;

	gettimeofday(&currentTime, NULL);
        std::cout << "\ngettimeofday():\n";
        std::cout << currentTime.tv_sec << std::endl;
        std::cout << currentTime.tv_usec << std::endl;

	// TEST
	// sayHello() and myPuts()
	std::cout << "\nPlease check the console output for sayHello() section and confirm if the output says 'hello'\n";
	std::cout << "Please check the console output for myPuts() section and confirm if the output says 'Hello, world!'\n";
	// myGTOD()
	if(mygtod.tv_sec != currentTime.tv_sec) {
		std::cout << "The test for myGTOD() has failed! The program will now exit!\n";
		exit(1);
	} else {
		std::cout << "myGTOD() test has passed!\n";
	}

	return 0;
}
