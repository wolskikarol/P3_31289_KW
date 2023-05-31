#include "mpi.h"
#include <cstdio>
#include <iostream>
#include <time.h>

void mainProcess(int size) {
    srand(time(NULL));

    unsigned int vectorSize;
    std::cout << "Podaj rozmiar wektora: ";
    std::cin >> vectorSize;

    // Przekazanie rozmiaru wektora do procesów roboczych
    MPI_Bcast(&vectorSize, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // Alokacja wektorów
    unsigned int* va = new unsigned int[vectorSize * (size - 1)];
    unsigned int* vb = new unsigned int[vectorSize * (size - 1)];
    unsigned int* vc = new unsigned int[vectorSize * (size - 1)];

    // Inicjalizacja wektorów
    for (unsigned int i = 0; i < vectorSize * (size - 1); i++) {
        va[i] = rand() % 10;
        vb[i] = rand() % 10;
        vc[i] = 0;
    }

    // Broadcast wektora `va` do procesów roboczych
    MPI_Bcast(va, vectorSize * (size - 1), MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // Broadcast wektora `vb` do procesów roboczych
    MPI_Bcast(vb, vectorSize * (size - 1), MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // Odbieranie wyników od procesów roboczych
    MPI_Request* requests = new MPI_Request[size - 1];
    MPI_Status* statuses = new MPI_Status[size - 1];
    for (unsigned int i = 0; i < size - 1; i++) {
        MPI_Irecv(vc + i * vectorSize, vectorSize, MPI_UNSIGNED, i + 1, 0, MPI_COMM_WORLD, &requests[i]);
    }
    MPI_Waitall(size - 1, requests, statuses);

    // Wypisywanie wyników
    for (unsigned int i = 0; i < (vectorSize * (size - 1)); i++) {
        printf("%d\t", va[i]);
    }
    printf("\r\n");
    for (unsigned int i = 0; i < (vectorSize * (size - 1)); i++) {
        printf("%d\t", vb[i]);
    }
    printf("\r\n");
    for (unsigned int i = 0; i < (vectorSize * (size - 1)); i++) {
        printf("%d\t", vc[i]);
    }
    printf("\r\n");

    // Zwalnianie pamiêci
    delete[] va;
    delete[] vb;
    delete[] vc;
    delete[] requests;
    delete[] statuses;
}

void workerProcess(int id, int size) {
    unsigned int vectorSize;

    // Odbieranie rozmiaru wektora od procesu g³ównego
    MPI_Bcast(&vectorSize, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // Alokacja wektorów
    unsigned int* va = new unsigned int[vectorSize * (size - 1)];
    unsigned int* vb = new unsigned int[vectorSize * (size - 1)];

    // Odbieranie wektorów `va` i `vb` od procesu g³ównego
    MPI_Bcast(va, vectorSize * (size - 1), MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast(vb, vectorSize * (size - 1), MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // Obliczanie sumy
    unsigned int* v = new unsigned int[vectorSize];
    for (unsigned int i = 0; i < vectorSize; i++) {
        v[i] = va[(id - 1) * vectorSize + i] + vb[(id - 1) * vectorSize + i];
    }

    // Wysy³anie wyniku do procesu g³ównego
    MPI_Send(v, vectorSize, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);

    // Zwalnianie pamiêci
    delete[] va;
    delete[] vb;
    delete[] v;
}




int main()
{
	int PID, PCOUNT;

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &PID);
	MPI_Comm_size(MPI_COMM_WORLD, &PCOUNT);

	if (PID == 0) { //jestem procesem g³ównym
		mainProcess(PCOUNT);
	}
	else { //jestem procesem roboczym
		workerProcess(PID, PCOUNT);
	}
	
	MPI_Finalize();
	
	return 0;
}

