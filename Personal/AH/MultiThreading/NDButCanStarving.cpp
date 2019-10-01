#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

void worker1(mutex& m1, mutex& m2) {  // worker1�� mutex ���￡�� �켱���� ���´�
	for(int i = 0; i < 10; i++) {
		m1.lock();
		m2.lock();
		cout << "Worker1 Hi! " << i << "\n";

		m2.unlock();
		m1.unlock();
	}
}

void worker2(mutex& m1, mutex& m2) {
	for (int i = 0; i < 10; i++) {
		while (true) {
			m2.lock();

			if (!m1.try_lock()) {  // m1�� �̹� lock�Ǿ������� m1�� ȣ���� thread�� ������ ��ĥ �� �ֵ��� m2�� unlock�Ѵ�
				m2.unlock();
				continue;
			}

			cout << "Worker2 Hi! " << i << "\n";
			m1.unlock();
			m2.unlock();
			break;  // worker2�� �ٸ� thread�� worker1�� �����ϰ����� �ʾ� m1�� m2�� ��� ���� �� ���� �� ������ ��ġ�� while���� ����������
		}
	}
}

int main() {
	mutex m1, m2;
	thread t1(worker1, ref(m1), ref(m2));
	thread t2(worker2, ref(m1), ref(m2));

	t1.join();
	t2.join();

	cout << "Done!" << "\n";

	return 0;
}