#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void worker(int start, int end, int* result) {
	// thread�� return ���� ��ȯ�ϴ� �Լ��� �ƴϹǷ� main �Լ��� ������� �����ϰ��� �� ��� �����͸� �̿��Ѵ�
	int sum = 0;
	for (int i = start; i < end; ++i) {
		sum += i;
	}
	*result = sum;

	thread::id this_id = this_thread::get_id();  // get_id �Լ��� �̿��Ͽ� thread�� ����id�� �˾Ƴ���
	printf("The sum result of %d to %d at Thread %x : %d\n", start, (end - 1), this_id, sum);  // �� ������ ��µǴ� ������ ������ ũ�� ������ �ƴ϶� thread�� ���� ������ ������
	// cout�� ����ϸ� "<<"�� �ݺ��� �� context switch�� �Ͼ �ٸ� thread�� ��� ����� �ڼ��� ��Ÿ�� �� �ִ�
}

int main() {
	// 1���� 10000���� ���ϴ� ���α׷�
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