#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>
#include <windows.h>
#include <omp.h>

void DoSomethingFast() {
    Sleep(1000);
}

void DoSomethingLong() {
    Sleep(6000);
}

int main() {
    uint8_t id;

    auto start = std::chrono::high_resolution_clock::now();
    DoSomethingFast();
    auto end = std::chrono::high_resolution_clock::now();

    printf("Szybkie wykonanie: %llu ms\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::high_resolution_clock::now();
    DoSomethingLong();
    end = std::chrono::high_resolution_clock::now();

    printf("D³ugie wykonanie: %llu ms\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::high_resolution_clock::now();
#pragma omp parallel num_threads(2) private(id)
    {
        id = omp_get_thread_num();

        if (id % 2) {
            DoSomethingLong();
        }
        else {
            DoSomethingFast();
        }

        printf("W¹tek %d zakoñczy³ pracê i oczekuje na barierze\n", id);

#pragma omp barrier

        printf("W¹tek %d zakoñczy³ pracê i zakoñczy³ ju¿ wykonanie\n", id);
    }

    end = std::chrono::high_resolution_clock::now();
    printf("Równoleg³e wykonanie z 2 w¹tkami: %llu ms\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::high_resolution_clock::now();
#pragma omp parallel num_threads(4) private(id)
    {
        id = omp_get_thread_num();

        if (id % 2) {
            DoSomethingLong();
        }
        else {
            DoSomethingFast();
        }

        printf("W¹tek %d zakoñczy³ pracê i oczekuje na barierze\n", id);

#pragma omp barrier

        printf("W¹tek %d zakoñczy³ pracê i zakoñczy³ ju¿ wykonanie\n", id);
    }

    end = std::chrono::high_resolution_clock::now();
    printf("Równoleg³e wykonanie z 4 w¹tkami: %llu ms\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::high_resolution_clock::now();
#pragma omp parallel num_threads(8) private(id)
    {
        id = omp_get_thread_num();

        if (id % 2) {
            DoSomethingLong();
        }
        else {
            DoSomethingFast();
        }

        printf("W¹tek %d zakoñczy³ pracê i oczekuje na barierze\n", id);

#pragma omp barrier

        printf("W¹tek %d zakoñczy³ pracê i zakoñczy³ ju¿ wykonanie\n", id);
    }

    end = std::chrono::high_resolution_clock::now();
    printf("Równoleg³e wykonanie z 8 w¹tkami: %llu ms\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).
