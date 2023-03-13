#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>

#define SIZE 100
#define NUM_THREADS 10
#define BLOCK_SIZE 10

void add(int id, int* a, int* b, int* c) {
    int start_index = id * BLOCK_SIZE;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        c[start_index + i] = a[start_index + i] + b[start_index + i];
    }
}

int main() {
    srand(time(NULL));
    int a[SIZE];
    int b[SIZE];
    int c[SIZE];

    for (int i = 0;i < SIZE;i++) {
        a[i] = rand() % 100 + 1; //1 do 100
        b[i] = rand() % 100 + 1;
    }

    //wypisanie na ekranie A
    for (int i = 0;i < SIZE;i++) {
        printf("%u ", a[i]);
    }
    printf("\n");

    //wypisanie na ekranie B
    for (int i = 0;i < SIZE;i++) {
        printf("%u ", b[i]);
    }
    printf("\n");

    std::thread** threads = new std::thread * [NUM_THREADS];
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0;i < NUM_THREADS;i++) {
        threads[i] = new std::thread(add, i, a, b, c); //wykorzystuje i jako id danego wątku
    }

    for (int i = 0;i < NUM_THREADS;i++) {
        threads[i]->join();
    }
    auto end_time = std::chrono::high_resolution_clock::now();

    for (int i = 0;i < NUM_THREADS;i++) {
        delete threads[i];
    }
    delete[] threads;

    //wypisanie na ekranie C
    for (int i = 0;i < SIZE;i++) {
        printf("%u ", c[i]);
    }

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    printf("\nZajelo to: %ld milisekund\n", duration);

    return 0;
}