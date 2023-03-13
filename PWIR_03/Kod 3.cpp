#include <chrono>
#include <cstdio>
#include <windows.h>
#include <fstream> 
#include <iostream>
int main() {
    auto start = std::chrono::steady_clock::now();
    //długie operacje
    std::fstream fs("test.txt", std::fstream::in | std::fstream::out);
    fs.close();
    auto end = std::chrono::steady_clock::now();

    printf("Czas trwania otwarcia i zamkniecia pliku: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    auto start2 = std::chrono::steady_clock::now();

    
    int fib[40];
    fib[0] = 0; 
    fib[1] = 1; 

    for (int i = 2; i < 40; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
   
    for (int i = 0; i < 40; i++) {
        std::cout << fib[i] << " ";
    }
    auto end2 = std::chrono::steady_clock::now();
    printf("Czas generowania 40-el ciagu fib: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count());
    return 0;
}