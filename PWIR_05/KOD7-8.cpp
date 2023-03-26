#include <thread>
#include <cstdio>
#include <windows.h>
#include <mutex>
#include <chrono>

std::mutex counter_mutex;
unsigned int counter = 0;

void increment() {
    int count = 0;
    for (;;) {
        counter_mutex.lock();
        counter++;
        counter_mutex.unlock();
        Sleep(2000);
        count++;
        if (count == 10) {  
            break;
        }
    }
}

void parity() {
    int count = 0;
    for (;;) {
        counter_mutex.lock();
        if (counter % 2) {
            printf("%u jest nieparzyste\r\n", counter);
        }
        else {
            printf("%u jest parzyste\r\n", counter);
        }
        counter_mutex.unlock();
        Sleep(2000);
        count++;
        if (count == 10) {  
            break;
        }
    }
}

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    std::thread inc(increment);
    std::thread par(parity);

    inc.join();
    par.join();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    printf("Done\r\n");
    printf("Czas wykonania programu: %lld ms\r\n", duration.count());

    return 0;
}
