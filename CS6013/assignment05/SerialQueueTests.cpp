#include <iostream>
#include "SerialQueue.hpp"

using namespace std;

int main() {
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

    if (*a != 7)
        cout << "Dequeue ret failed.\n";

    return 0;
}
