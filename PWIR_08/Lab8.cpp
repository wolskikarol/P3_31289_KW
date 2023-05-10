#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>
#include <time.h>
#include <omp.h>

// Matrix * Vector

#define MATRIX_H 30000
#define MATRIX_W 30000
#define VECTOR_S 30000

uint16_t** matrix;
uint16_t* vector;
uint16_t* result;

int32_t i;
int32_t k;

void matrixVectorMultiplication() {
#pragma omp parallel for
    for (i = 0; i < MATRIX_H; i++) {
        for (k = 0; k < MATRIX_W; k++) {
            result[i] += matrix[i][k] * vector[k];
        }
    }
}

int main() {
    srand(time(NULL));

    // Check if vector size == matrix width
    assert(MATRIX_W == VECTOR_S);

    // Allocate matrix
    matrix = new uint16_t * [MATRIX_H];
    for (i = 0; i < MATRIX_H; i++) {
        matrix[i] = new uint16_t[MATRIX_W];
    }

    // Allocate vectors
    vector = new uint16_t[VECTOR_S];
    result = new uint16_t[VECTOR_S];

    // Fill matrix with random data
    for (i = 0; i < MATRIX_H; i++) {
        for (k = 0; k < MATRIX_W; k++) {
            matrix[i][k] = rand() % 100;
        }
    }

    // Fill vector with random data
    for (i = 0; i < VECTOR_S; i++) {
        vector[i] = rand() % 100;
        result[i] = 0;
    }

    int numIterations = 10; // Number of matrix-vector multiplications

    auto start = std::chrono::high_resolution_clock::now();

    for (int iteration = 0; iteration < numIterations; iteration++) {
        matrixVectorMultiplication();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    double totalTime = duration.count();

    printf("Total time for %d matrix-vector multiplications: %f seconds\n", numIterations, totalTime);

    // Free memory
    delete[] vector;
    delete[] result;

    for (i = 0; i < MATRIX_H; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
