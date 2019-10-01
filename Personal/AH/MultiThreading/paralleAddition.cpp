#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void worker(int start, int end, int* result) {
	// thread는 return 값을 반환하는 함수가 아니므로 main 함수에 결과값을 전달하고자 할 경우 포인터를 이용한다
	int sum = 0;
	for (int i = start; i < end; ++i) {
		sum += i;
	}
	*result = sum;

	thread::id this_id = this_thread::get_id();  // get_id 함수를 이용하여 thread의 고유id를 알아낸다
	printf("The sum result of %d to %d at Thread %x : %d\n", start, (end - 1), this_id, sum);  // 이 문장이 출력되는 순서는 숫자의 크기 순서가 아니라 thread의 실행 순서를 따른다
	// cout을 사용하면 "<<"가 반복될 때 context switch가 일어나 다른 thread의 출력 내용과 뒤섞여 나타날 수 있다
}

int main() {
	// 1부터 10000까지 더하는 프로그램
	int partial_sums[4];

	vector<thread> workers;
	for (int i = 0; i < 4; i++) {
		workers.push_back(thread(worker, i * 2500 + 1, (i + 1) * 2500 + 1, &partial_sums[i]));
	}

	for (int i = 0; i < 4; i++) {
		workers[i].join();
	}

	int total = 0;
	for (int i = 0; i < 4; i++) {
		total += partial_sums[i];
	}
	cout << "Total : " << total << "\n";
}