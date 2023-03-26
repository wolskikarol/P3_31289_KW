#include <thread>
#include <cstdio>
#include <windows.h>
#include <iostream>

const int NUM_THREADS = 10;
const int ARRAY_SIZE = 100;

unsigned int counter = 0;
int tablica[ARRAY_SIZE];

void increment(int id) {
    int sum = 0;
    for (int i = id * 10; i < (id + 1) * 10; i++) {
        sum += tablica[i];
    }
    counter += sum;
    thread_local unsigned int local_counter = 0;
    local_counter += sum;
    Sleep(300);
    printf("Watek %d -> %u\n", id, local_counter);
}

int main() {

    for (int i = 0; i < ARRAY_SIZE; i++) {
        tablica[i] = rand() % 10 + 1;
    }

    std::thread threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = std::thread(increment, i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    printf("Suma globalna: %u\n", counter);

    return 0;
}
