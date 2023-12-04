#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

// Function to sum elements between 1 and N
long sumNumbers(int N) {
    long sum = 0;
    for (int i = 1; i <= N; ++i) {
        sum += i;
    }
    return sum;
}

// Function for each thread to calculate the sum and store in the sum vector
void threadFunction(int threadID, int N, std::vector<long>& sum) {
    sum[threadID] = sumNumbers(N);
    std::cout << "Thread " << threadID << ": Sum = " << sum[threadID] << std::endl;
}

// Function to perform multi-threading
void multiThread(int NumT, int N) {
    std::vector<long> sum(NumT, 0); // Initialize the sum vector

    // Vector to store thread objects
    std::vector<std::thread> threads;

    // Create and start threads
    for (int i = 0; i < NumT; ++i) {
        threads.push_back(std::thread(threadFunction, i, N, std::ref(sum)));
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }
}

// Function to perform sequential execution
void singleThread(int NumT, int N) {
    std::vector<long> sum(NumT, 0); // Initialize the sum vector

    // Sequentially invoke sumNumbers NumT times
    for (int i = 0; i < NumT; ++i) {
        sum[i] = sumNumbers(N);
        std::cout << "Sequen " << i << ": Sum = " << sum[i] << std::endl;
    }
}

// Function to compare sequential vs parallel execution time
void compareSequentialVsParallel(int NumT, int N) {
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    singleThread(NumT, N);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    multiThread(NumT, N);
    std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();

    double duration1 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    double duration2 = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();

    std::cout << "Execution time (Sequential): " << duration1 << " microseconds\n";
    std::cout << "Execution time (Parallel): " << duration2 << " microseconds\n";
}

int main() {
    int NumT = 4; // Number of threads
    int N = 1000000; // Value of N

    compareSequentialVsParallel(NumT, N);

    return 0;
}
