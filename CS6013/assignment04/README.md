#MyMalloc
##Introduction
This is a custom implementation of the of `malloc()` and `free()` system calls. This project is built primarily 
using `mmap()` and `munmap()` system calls. There is no use of C++ helpers such as `new` or `malloc()` within the 
implementation of this program. This is merely an exercise to understand system programming better.

##Tests
The `main.cpp` will automatically drive 3 tests, i.e.
* Hash Table Test to check the implementation of the custom hash table class.
* MyMalloc Test to check the implementation of the MyMalloc class.
* Timed Experiment that times and compares the MyMalloc `allocate()` and `deallocate()` to the `malloc()` and `free()` 
  system functions respectively.

##Instructions
To use this program, uncomment code block on `line 14` and comment out `line 118` - `line 120`. Then you may use 
`malloc()` and `free()` just as you would normally since they will be overridden if you follow the instructions 
correctly.

##Why is my program much slower than the default `malloc()` and `free()`?
There can be several reasons that can justify the question above. Some of which are as follows:
* Slow Hashing Function - My hashing function is much slower than the one used in system functions, can result in 
  more collisions, therefore slowing down the program.
* Linear Probing Hash Table - My hash table is linear probing which results in more collisions which in turn takes 
  more time to insert, remove and search entries that can dramatically slow down the program.
* Alignment - Some memory alignments can be much faster than other memory alignments.
* Fragmentation - Intermediate implementation of allocating and freeing memory can leave fragments in the memory 
  that can cause the program to bloat.
* Performance - Communicating with the OS for more memory can result in slowing down the program.
* Lack of Targeted Solutions - Not having smaller pieces of program resolving and optimising every bit of potential 
  time can result in wasting time.


##What can be done to optimise this program?
Some ways to optmise the program are as follows:
* Keep track of pointer locations and their sizes and then allocate the memory in a more aligned manner. This will 
  avoid creating holes between chunks of memory and will also reduce bloat.
* Work tightly with the system page size and possibly create different algorithms for different page sizes.
* Divide and conquer small potential areas that can be optimised to further accelerate the program.
* Use a better type of hash table for different algorithms to suit the needs better. Linear probed tables are very 
  slow compared to the other more advanced types.
* Use a good hashing function to avoid collisions and to generate more unique hashes.
