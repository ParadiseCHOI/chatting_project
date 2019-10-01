#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

void worker(int& result, mutex& m) {
	for (int i = 0; i < 10000; i++) {
		m.lock();  // mutex m�� ������ thread�� lock()�� ȣ���ϸ� �ٸ� ��� thread�� m�� ���� ������ ������ ����Ѵ�
		result += 1;  // critical section
		m.unlock();  // m�� ������ thread�� unlock() ȣ��� m�� ��ȯ�ϸ� �ٸ� thread�� m�� ��� ���� critical section�� ������ �� �ִ�
	}
}

int main() {
	int counter = 0;
	mutex m;  // mutex ��ü�� �����Ѵ�

	vector<thread> workers;
	for (int i = 0; i < 4; i++) {
		workers.push_back(thread(worker, ref(counter), ref(m)));  // thread���� worker�Լ��� �����Ѵ�. �Լ��� �������ڷ� counter�� mutex m�� referrence�� ���� ����Ѵ�
	}

	for (int i = 0; i < 4; i++) {
		workers[i].join();
	}
	cout << "Counter value : " << counter << "\n";

	return 0;
}