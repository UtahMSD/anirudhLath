#include <iostream>
#include <atomic>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <omp.h>
#include <math.h>
using namespace std;
using namespace std::chrono;

template<typename T>
struct Result {
    T data;
    int duration;
};

template<typename T>
auto parallel_sum_std(T a[], size_t N, size_t num_threads) {
    num_threads %= N;
    auto start = high_resolution_clock::now();
    size_t remainder = N % num_threads;
    size_t numPerThread = N / num_threads;

    vector<T> sumArr(num_threads, NULL);
    vector<thread> threads;
    threads.reserve(num_threads);
    atomic<T> sum;
    sum = 0;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&, a, i] () {
            int startIdx = (i * numPerThread);
            int endIdx = (i * numPerThread) + numPerThread;
            for (int j = startIdx; j < endIdx; ++j) {
                sumArr[i] += a[j];
            }
            sum += sumArr[i];
        });
    }


    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }
    if (remainder > 0) {
        for (int i = (num_threads * numPerThread); i < N; ++i) {
            sum += a[i];
        }
    }

    auto stop = high_resolution_clock::now();
    Result<T> result{};
    result.data = sum;
    result.duration = duration_cast<microseconds>(stop - start).count();
    return result;
}

template<typename T>
T calculate_sum(T a[], size_t N, size_t num_threads, int id, vector<T> &partialSums) {
    num_threads %= N;
//    cout << "run" << endl;

    size_t numPerThread = N / num_threads;
    int startIdx = id * numPerThread;
    int endIdx = (id * numPerThread) + numPerThread;
    for (int j = startIdx; j < endIdx; ++j) {
        partialSums[id] += a[j];
    }
    return partialSums[id];
}

template<typename T>
auto parallel_sum_omp1(T a[], size_t N, size_t threads) {
    threads %= N;
    atomic<T> sum;
    sum = 0;
    vector<T> partialSums(threads, NULL);
    auto start = high_resolution_clock::now();
    size_t remainder = N % threads;
    size_t numPerThread = N / threads;

    omp_set_dynamic(0);
    omp_set_num_threads(threads);


#pragma omp parallel
    {
        int id = omp_get_thread_num();

        int startIdx = id * numPerThread;
        int endIdx = (id * numPerThread) + numPerThread;
        int count = 0;
        for (int j = startIdx; j < endIdx; ++j) {
            partialSums[id] += a[j];
        }
    }
#pragma omp single
        {
            for (int i = 0; i < threads; ++i) {
                sum += partialSums[i];
            }
            if (remainder > 0) {
                for (int i = (threads * numPerThread); i < N; ++i) {
                    sum += a[i];
                }
            }
        }

    auto stop = high_resolution_clock::now();
    Result<T> result{};
    result.data = sum;
    result.duration = duration_cast<microseconds>(stop - start).count();
    return result;

}

template<typename T>
auto parallel_sum_omp_builtin(T a[], size_t N, size_t threads) {
    int sum = 0;
    auto start = high_resolution_clock::now();
    omp_set_dynamic(0);
    omp_set_num_threads(threads);

#pragma omp parallel for num_threads(threads) reduction(+:sum)
    {
        for (int i = 0; i < N; ++i) {
            sum += a[i];
        }
    }

    auto stop = high_resolution_clock::now();
    Result<T> result{};
    result.data = sum;
    result.duration = duration_cast<microseconds>(stop - start).count();
    return result;

}

Result<int> sum1( int a[], int N) {
    auto start = high_resolution_clock::now();
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += a[i];
    }
    auto stop = high_resolution_clock::now();
    Result<int> res{};
    res.data = sum;
    res.duration = duration_cast<microseconds>(stop - start).count();
    return res;
}

void graph(int N, int thread_count) {
    int a[N];
    for (int i = 0; i < N; ++i) {
        a[i] = rand() % 100;
    }
    int totalDuration = 0;
    for (int i = 0; i < 10000; ++i) {
        totalDuration += parallel_sum_omp_builtin(a, N, thread_count).duration;
    }
    cout << N << ", " << thread_count << ", " << totalDuration / 10000 << endl;



}

int main() {
//    for (int i = 1000; i < 10000; i += 1000) {
//        graph(i, i / 1000);
//    }
/*    for (int i = pow(2,10); i < pow(2,16); i *= 2) {
        for (int j = 1; j <= 16; ++j) {
            graph(i, j);
        }
    }*/
    int arrSize = 1000000;
    int a[arrSize];//= {34,445,45,23,56,57,67,68,232,5,7,8,78,89,75,2,45,3,3};
    for (int i = 0; i < arrSize; ++i) {
        a[i] = rand() % 100;
    }
    size_t numThreads = 7;
    Result<int> resultThreaded = parallel_sum_std(a, arrSize, numThreads);
    Result<int> resultThreadedOmp = parallel_sum_omp1(a, arrSize, numThreads);
    Result<int> resultThreadedOmpRed = parallel_sum_omp_builtin(a, arrSize, numThreads);
    Result<int> resultNotThreaded = sum1(a, arrSize);
    cout << resultThreaded.data << endl;
    cout << resultThreaded.duration << endl;
    cout << resultThreadedOmp.data << endl;
    cout << resultThreadedOmp.duration << endl;
    cout << resultThreadedOmpRed.data << endl;
    cout << resultThreadedOmpRed.duration << endl;
    cout << resultNotThreaded.data << endl;
    cout << resultNotThreaded.duration << endl;
    return 0;
}
