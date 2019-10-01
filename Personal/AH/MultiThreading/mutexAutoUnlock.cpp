#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

void worker(int& result, mutex& m) {
	for (int i = 0; i < 10000; i++) {
		lock_guard<mutex> lock(m);  // lock_guard는 mutex를 인자로 받아 객체를 생성한다
		result += 1;
	}  // scope를 나가는 시점에 lock_guard lock이 소멸되며 자동으로 m을 unlock한다
}

int main() {
	int counter = 0;
	mutex m;
	vector<thread> workers;

	for (int i = 0; i < 4; i++) {
		workers.push_back(thread(worker, ref(counter), ref(m)));
	}

	for (int i = 0; i < 4; i++) {
		workers[i].join();
	}
	cout << "Counter value : " << counter << "\n";

	return 0;
}