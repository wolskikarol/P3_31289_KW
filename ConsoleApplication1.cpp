#include <cstdio>
#include <thread>
#include <windows.h>
#include <iostream>
using namespace std;

int action(int id, int time) {
	printf("Uruchamiam watek %d\n", id);
	Sleep(time * 1000); //10 sekund
	printf("Koncze watek %d\n", id);
	return 0;
}

int main() {
	//tworzenie wątku
	std::thread t1(action, 1,5); //konstruktor klasy t1 przyjmuje minimum wskaźnik na funckje do wykonania
	std::thread::id t1_id = t1.get_id();
	std::thread t2(action, 2,10); //funckja ta może coś zwracać, ale może zwaracać też void
	std::thread::id t2_id = t2.get_id();
	std::thread t3(action, 3,2); //dalsze parametry zostaną przekazane do podanej funckji
	std::thread::id t3_id = t3.get_id();
	std::cout << "t1 id: " << t1_id << '\n';
	std::cout << "t2 id: " << t2_id << '\n';
	std::cout << "t3 id: " << t3_id << '\n';

	t1.join();  //synchronizacja
	t2.join();  //wątek główny ma tu poczekać na te 3 wątki
	t3.join();  //inaczej program by się zakończył wcześniej bo wątki trwają minimum 10 sekund

	printf("Koniec programu \r\n");

	return 0;
}