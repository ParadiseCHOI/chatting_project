#include <iostream>
#include <thread>  // C++ 11���� thread�� ǥ�ؿ� �߰��Ǿ� ��������� �߰��ϴ� ������ thread�� ������ �� �ִ�
using std::thread;
using namespace std;

void func1() {
	for (int i = 0; i < 10; i++) {
		cout << "Activate Thread1! \n";
	}
}

void func2() {
	for (int i = 0; i < 10; i++) {
		cout << "Activate Thread2! \n";
	}
}

void func3() {
	for (int i = 0; i < 10; i++) {
		cout << "Activate Thread3! \n";
	}
}

int main() {
	thread t1(func1);  // thread ��ü�� �����Ѵ�. �� �� �������ڷ� �� �Լ��� �� thread���� �����Ѵ�
	thread t2(func2);
	thread t3(func3);

	t1.join();  // �� thread���� ������ �����ϸ� join()�� return�Ѵ�
	t2.join();  // thread�� ���� ������ �������. t2�� t1���� ���� ������ ��� t1�� join()�� ���� return�ϰ� t2�� ����Ǿ������� �ٷ� t2�� join()�� return�Ѵ�
	t3.join();
	
	return 0;
}