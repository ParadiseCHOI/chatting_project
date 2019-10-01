#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

void worker(int& result, mutex& m) {
	for (int i = 0; i < 10000; i++) {
		m.lock();  // mutex m을 소유한 thread가 lock()을 호출하면 다른 모든 thread는 m을 얻을 때까지 무한정 대기한다
		result += 1;  // critical section
		m.unlock();  // m을 소유한 thread가 unlock() 호출로 m을 반환하면 다른 thread가 m을 얻어 위의 critical section에 진입할 수 있다
	}
}

int main() {
	int counter = 0;
	mutex m;  // mutex 객체를 선언한다

	vector<thread> workers;
	for (int i = 0; i < 4; i++) {
		workers.push_back(thread(worker, ref(counter), ref(m)));  // thread에서 worker함수를 실행한다. 함수의 전달인자로 counter와 mutex m의 referrence를 각각 사용한다
	}

	for (int i = 0; i < 4; i++) {
		workers[i].join();
	}
	cout << "Counter value : " << counter << "\n";

	return 0;
}