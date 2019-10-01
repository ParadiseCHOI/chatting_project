#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void worker(int& counter) {
	for (int i = 0; i < 10000; i++) {
		counter += 1;
	}
}

int main() {
	int counter = 0;
	vector<thread> workers;

	for (int i = 0; i < 4; i++) {
		workers.push_back(thread(worker, ref(counter)));
	}

	for (int i = 0; i < 4; i++) {
		workers[i].join();
	}

	cout << "Counter value : " << counter << "\n";
}