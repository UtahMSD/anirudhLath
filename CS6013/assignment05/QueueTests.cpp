#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>
#include "ConcurrentQueue.hpp"
#include "SerialQueue.hpp"

//https://www.cs.rochester.edu/~scott/papers/1996_PODC_queues.pdf

void staticTest();
void dynamicTest();
bool concurrentQueueTest1(int producers, int consumers, int count);
bool concurrentQueueTest2(int producers, int consumers, int count);
bool concurrentQueueTest3(int producers, int consumers, int count);

using namespace std;

int main(int argc, char **argv) {
    cout << "Running static allocation tests on SerialQueue class...\n";
    staticTest();
    cout << "Passed.\n";
    cout << "Running dynamic allocation tests on SerialQueue class...\n";
    dynamicTest();
    cout << "Passed.\n";
    cout << "Attempting to run tests on ConcurrentQueue class...\n";

    if (argc != 4) {
        throw runtime_error("Cannot continue testing further, invalid arguments, please enter ./assignment05 "
                            "<PRODUCERS> <CONSUMERS> "
                            "<PAYLOAD "
                            "COUNT>\n");
    }

    int producers = stoi(argv[1]);
    int consumers = stoi(argv[2]);
    int count     = stoi(argv[3]);
    cout << "Running tests on ConcurrentQueue class...\n";

    if (concurrentQueueTest1(producers, consumers, count)) {
        cout << "Passed test 1.\n";
    }
    else {
        cout << "Failed test 1.\n";
    }

    if (concurrentQueueTest2(producers, consumers, count)) {
        cout << "Passed test 2.\n";
    }
    else {
        cout << "Failed test 2.\n";
    }

    concurrentQueueTest3(producers, consumers, count);
    cout << "Passed test 3.\n";
    cout << "Passed.\n";

    return 0;
}

void staticTest() {
    int *a = new int;
    bool result = false;
    SerialQueue<int> queue{};
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

    delete a;
}

void dynamicTest() {
    int **a = new int *;
    bool result = false;
    int *b = new int(2);
    int *c = new int(3);
    int *d = new int(4);
    auto *queue = new SerialQueue<int*>;
    queue->enqueue(b);
    queue->enqueue(b);
    queue->enqueue(c);
    queue->enqueue(c);
    queue->enqueue(d);
    queue->enqueue(d);

    if (queue->size() != 6)
        cout << "Enqueue failed.\n";
    for (int i = 0; i < 6; ++i) {
        result = queue->dequeue(a);
        if (!result)
            cout << "Dequeue failed.\n";
    }

    if (queue->dequeue(a))
        cout << "Dequeue failed.\n";
    if (queue->size() != 0)
        cout << "Dequeue failed.\n";

    if (**a != 4)
        cout << "Dequeue ret failed.\n";

    delete a;
    delete b;
    delete c;
    delete d;
    delete queue;
}

bool concurrentQueueTest1(int producers, int consumers, int count) {
    vector<thread> producer, consumer;
    producer.reserve(producers);
    consumer.reserve(consumers);
    ConcurrentQueue<int> queue{};
    mutex m;
    int *ret = new int;
    for (int i = 0; i < producers; ++i) {
        producer.push_back(thread([&,i]() {
            for (int j = 0; j < count; ++j) {
                queue.enqueue(j);
            }
        }));
    }
    for (int i = 0; i < producers; ++i) {
        producer[i].join();
    }
    for (int i = 0; i < consumers; ++i) {
        consumer.push_back(thread([&,i]() {
            for (int j = 0; j < count; ++j) {
                queue.dequeue(ret);
            }
        }));
    }
    for (int i = 0; i < consumers; ++i) {
        consumer[i].join();
    }
    delete ret;
    return queue.size() == (producers - consumers) * count;

}
bool concurrentQueueTest2(int producers, int consumers, int count) {
    vector<thread> producer, consumer;
    producer.reserve(producers);
    consumer.reserve(consumers);
    ConcurrentQueue<int> queue{};
    mutex m;
    int *ret = new int;
    for (int i = 0; i < producers; ++i) {
        producer.push_back(thread([&,i]() {
            for (int j = 0; j < count; ++j) {
                queue.enqueue(j);
            }
        }));
    }
    sleep(5);
    for (int i = 0; i < consumers; ++i) {
        consumer.push_back(thread([&,i]() {
            for (int j = 0; j < count; ++j) {
                queue.dequeue(ret);
            }
        }));
    }
    for (int i = 0; i < producers; ++i) {
        producer[i].join();
    }
    for (int i = 0; i < consumers; ++i) {
        consumer[i].join();
    }
    delete ret;
    return queue.size() == (producers - consumers) * count;

}
bool concurrentQueueTest3(int producers, int consumers, int count) {
    vector<thread> producer, consumer;
    producer.reserve(producers);
    consumer.reserve(consumers);
    ConcurrentQueue<int> queue{};
    mutex m;
    int *ret = new int;
    for (int i = 0; i < producers; ++i) {
        producer.push_back(thread([&,i]() {
            for (int j = 0; j < count; ++j) {
                queue.enqueue(j);
            }
        }));
    }
    for (int i = 0; i < consumers; ++i) {
        consumer.push_back(thread([&,i]() {
            for (int j = 0; j < count; ++j) {
                queue.dequeue(ret);
            }
        }));
    }
    for (int i = 0; i < producers; ++i) {
        producer[i].join();
    }
    for (int i = 0; i < consumers; ++i) {
        consumer[i].join();
    }
    delete ret;
    return true;
}
