#include <iostream>
#include <cmath>
#include <omp.h>

double calculateVectorLength(double* vector, int size) {
    double length = 0.0;

#pragma omp parallel num_threads(4)
    {
        int tid = omp_get_thread_num();
        double localLength = 0.0;

#pragma omp sections
        {
#pragma omp section
            {
                for (int i = 0; i < size / 4; i++) {
                    localLength += vector[i] * vector[i];
                }
                std::cout << "Section 1 - Thread " << tid << " working..." << std::endl;
            }

#pragma omp section
            {
                for (int i = size / 4; i < size / 2; i++) {
                    localLength += vector[i] * vector[i];
                }
                std::cout << "Section 2 - Thread " << tid << " working..." << std::endl;
            }

#pragma omp section
            {
                for (int i = size / 2; i < 3 * size / 4; i++) {
                    localLength += vector[i] * vector[i];
                }
                std::cout << "Section 3 - Thread " << tid << " working..." << std::endl;
            }

#pragma omp section
            {
                for (int i = 3 * size / 4; i < size; i++) {
                    localLength += vector[i] * vector[i];
                }
                std::cout << "Section 4 - Thread " << tid << " working..." << std::endl;
            }
        }

#pragma omp critical
        {
            length += localLength;
        }
    }

    return std::sqrt(length);
}

int main() {
    const int size = 100000;
    double vector[size];

    // Inicjalizacja wektora
    for (int i = 0; i < size; i++) {
        vector[i] = i + 1;
    }

    // Obliczenie d³ugoœci wektora na czterech w¹tkach
    double length = calculateVectorLength(vector, size);

    std::cout << "Vector length: " << length << std::endl;

    return 0;
}
