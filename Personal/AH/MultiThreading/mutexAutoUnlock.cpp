#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

void worker(int& result, mutex& m) {
	for (int i = 0; i < 10000; i++) {
		lock_guard<mutex> lock(m);  // lock_guard�� mutex�� ���ڷ� �޾� ��ü�� �����Ѵ�
		result += 1;
	}  // scope�� ������ ������ lock_guard lock�� �Ҹ�Ǹ� �ڵ����� m�� unlock�Ѵ�
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