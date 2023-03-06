#include <cstdio>
#include <thread>
#include <windows.h>
#include <iostream>
#include <vector>


void action(int id) {
	printf("Uruchamiam watek %d\n", id);
	Sleep(5 * 1000); //5 sekund
	printf("Koncze watek %d\n", id);
}

int main() {
	int thread_count = 0;
	std::cout << "Podaj ilosc watkow" << std::endl;
	std::cin >> thread_count;

	std::vector<std::thread*> threads(thread_count);

	//otwieranie wątków
	for (int i = 0; i < thread_count; i++) {
		threads[i] = new std::thread(action, i); //wykorzystuje i jako id danego wątku
	}

	//watki pracują, ale trzeba je zsynchronizować
	for (int i = 0; i < thread_count; i++) {
		threads[i]->join();
	}

	//alokowaliśmy pamięć więc pasuje ją zwolnić
	for (int i = 0; i < thread_count; i++) {
		delete threads[i];
	}
	delete[] threads;

	printf("Koniec programu \r\n");

	return 0;
}


