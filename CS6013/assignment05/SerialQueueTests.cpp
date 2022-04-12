#include <iostream>
#include "SerialQueue.hpp"

void staticTest();
void dynamicTest();

using namespace std;

int main() {
    staticTest();
    dynamicTest();

    return 0;
}

void staticTest() {
    int *a = new int;
    bool result = false;
    SerialQueue<int> queue;
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6);
    queue.enqueue(7);
    if (queue.size() != 6)
        cout << "Enqueue failed.\n";
    for (int i = 0; i < 6; ++i) {
        result = queue.dequeue(a);
        if (!result)
            cout << "Dequeue failed.\n";
    }

    if (queue.dequeue(a))
        cout << "Dequeue failed.\n";
    if (queue.size() != 0)
        cout << "Dequeue failed.\n";

    if (*a != NULL)
        cout << "Dequeue ret failed.\n";

    delete a;
}

void dynamicTest() {
    int **a = new int *;
    bool result = false;
    int *b = new int(2);
    int *c = new int(3);
    int *d = new int(4);
    SerialQueue<int*> queue;
    queue.enqueue(b);
    queue.enqueue(b);
    queue.enqueue(c);
    queue.enqueue(c);
    queue.enqueue(d);
    queue.enqueue(d);

    if (queue.size() != 6)
        cout << "Enqueue failed.\n";
    for (int i = 0; i < 6; ++i) {
        result = queue.dequeue(a);
        if (!result)
            cout << "Dequeue failed.\n";
    }

    if (queue.dequeue(a))
        cout << "Dequeue failed.\n";
    if (queue.size() != 0)
        cout << "Dequeue failed.\n";

    if (*a != NULL)
        cout << "Dequeue ret failed.\n";

    delete a;
}
