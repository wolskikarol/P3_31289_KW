#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <thread>
#include <vector>


void monteCarloThread(int num_points, int& num_inside_circle) {
    std::srand(std::time(nullptr));

    for (int i = 0; i < num_points; i++) {
        double x = ((double)std::rand() / RAND_MAX) * 2 - 1;
        double y = ((double)std::rand() / RAND_MAX) * 2 - 1;
        if (std::pow(x, 2) + std::pow(y, 2) <= 1) {
            num_inside_circle++;
        }
    }
}

int main() {
    const int num_points = 10000000;
    int num_inside_circle = 0;
    int num_threads = std::thread::hardware_concurrency();

    std::vector<std::thread> threads;

   
    for (int i = 0; i < num_threads; i++) {
        int points_per_thread = num_points / num_threads;
        threads.emplace_back(monteCarloThread, points_per_thread, std::ref(num_inside_circle));
    }

 
    for (std::thread& thread : threads) {
        thread.join();
    }

    double pi = 4.0 * num_inside_circle / num_points;
    std::cout << "Approximate value of Pi: " << pi << std::endl;

    return 0;
}
