#include <iostream>
#include <vector>
#include <thread>

void factorialThread(const std::vector<int>& numbers, int startIndex, int endIndex, std::vector<long long>& results) {
    for (int i = startIndex; i < endIndex; i++) {
        int number = numbers[i];
        long long factorial = 1;

        for (int j = 1; j <= number; j++) {
            factorial *= j;
        }

        results[i] = factorial;
    }
}

int main() {
    const int vectorSize = 10;
    const int numThreads = std::thread::hardware_concurrency();

    std::vector<int> numbers = { 5, 3, 6, 4, 7, 2, 8, 1, 9, 10 };
    std::vector<long long> factorials(vectorSize);
    std::vector<std::thread> threads(numThreads);
    int chunkSize = vectorSize / numThreads;
    int startIndex = 0;

    for (int i = 0; i < numThreads; i++) {
        int endIndex = startIndex + chunkSize;
        if (i == numThreads - 1) {
            endIndex = vectorSize;
        }

        threads[i] = std::thread(factorialThread, std::ref(numbers), startIndex, endIndex, std::ref(factorials));
        startIndex = endIndex;
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    for (int i = 0; i < vectorSize; i++) {
        std::cout << "Factorial of " << numbers[i] << ": " << factorials[i] << std::endl;
    }

    return 0;
}
