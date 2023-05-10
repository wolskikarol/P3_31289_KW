#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

#define VECTOR_SIZE 10000

std::vector<int> createRandomVector()
{
    std::vector<int> vec(VECTOR_SIZE);

    
    std::srand(std::time(nullptr));

    for (int i = 0; i < VECTOR_SIZE; ++i)
    {
        vec[i] = std::rand() % 11; 
    }

    return vec;
}
int calculateVectorLength(const std::vector<int>& vec)
{
    int sum = 0;

    for (int i = 0; i < VECTOR_SIZE; ++i)
    {
        sum += vec[i] * vec[i];
    }

    return std::sqrt(sum);
}

int main()
{
    std::vector<int> vec = createRandomVector();

    auto start = std::chrono::high_resolution_clock::now();
    int length = calculateVectorLength(vec);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> durationSeq = end - start;

    std::cout << "Dlugosc wektora (wersja sekwencyjna): " << length << std::endl;
    std::cout << "Czas wykonania (wersja sekwencyjna): " << durationSeq.count() << " ms" << std::endl;

    int lengthParallel = 0;

    start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for reduction(+: lengthParallel)
    for (int i = 0; i < VECTOR_SIZE; ++i)
    {
        lengthParallel += vec[i] * vec[i];
    }

    lengthParallel = std::sqrt(lengthParallel);

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> durationParallel = end - start;

    std::cout << "Dlugosc wektora (wersja zrownoleglona): " << lengthParallel << std::endl;
    std::cout << "Czas wykonania (wersja zrownoleglona): " << durationParallel.count() << " ms" << std::endl;

    return 0;
}
