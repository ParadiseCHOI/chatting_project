#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

void worker1(mutex& m1, mutex& m2) {
	for (int i = 0; i < 10000; i++) {
		lock_guard<mutex> lock1(m1);
		lock_guard<mutex> lock2(m2);
	}
}

void worker2(mutex& m1, mutex& m2) {
	for (int i = 0; i < 10000; i++) {
		lock_guard<mutex> lock2(m2);
		lock_guard<mutex> lock1(m1);
	}
}

int main() {
	int counter = 0;
	mutex m1, m2;

	thread t1(worker1, ref(m1), ref(m2));
	thread t2(worker2, ref(m1), ref(m2));

	t1.join();
	t2.join();

	cout << "Done!" << "\n";

	return 0;
}