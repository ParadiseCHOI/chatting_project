#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

void worker1(mutex& m1, mutex& m2) {  // worker1은 mutex 경쟁에서 우선권을 갖는다
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

			if (!m1.try_lock()) {  // m1이 이미 lock되어있으면 m1을 호출한 thread가 실행을 마칠 수 있도록 m2를 unlock한다
				m2.unlock();
				continue;
			}

			cout << "Worker2 Hi! " << i << "\n";
			m1.unlock();
			m2.unlock();
			break;  // worker2는 다른 thread가 worker1을 실행하고있지 않아 m1과 m2를 모두 얻을 수 있을 때 수행을 마치고 while문을 빠져나간다
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