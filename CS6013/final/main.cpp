//
// Created by Anirudh Lath on 4/29/22.
//

#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <condition_variable>

using namespace std;

class Barrier {
private:
    int count_; // Total number of threads
    mutex m_; // Mutex to lock
    condition_variable cv_; // Condition variable to make the threads wait for the others

public:
    Barrier(int count) { // Constructor
        count_ = count;
    }

    void wait() {
        unique_lock<mutex> lock(m_); // Lock because changing a member variable that may be accessed at the same time
        // by the other threads
        if(--count_ == 0) { // If all threads have finished running, notify all the other threads.
            cv_.notify_all();
        }
        else {
            cv_.wait(lock, [this] {return count_ == 0;}); // If all the threads have finished
            // running,
            // return true
            // and unlock all threads to let them continue onto the next task. This will also prevent spurious wakes.
        }
    }
};
int main() {
    Barrier bar(10); // Create barrier that will stop 10 threads
    vector<thread> threads; // List of threads
    threads.reserve(10); // Reserve space for all threads
    mutex m;
    mutex n;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([i, &m, &bar, &n](){
            for (int j = 0; j < 5; j++) {
                lock_guard<mutex> lock(m); // lock for cout
                cout << "hello thread #" << i << " times " << j << endl;
            }
            bar.wait(); // wait for all threads to finish
            for (int j = 0; j < 5; j++) {
                lock_guard<mutex> lock(n);
                cout << "goodbye thread #" << i << " times " << j << endl;
            }
        });
    }

    for (int i = 0; i < 10; ++i) {
        threads[i].join(); // join threads
    }
    cout << "FINISHED!" << endl;
    return 0;
}