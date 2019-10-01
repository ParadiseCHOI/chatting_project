#include <iostream>
#include <thread>  // C++ 11부터 thread가 표준에 추가되어 헤더파일을 추가하는 것으로 thread를 생성할 수 있다
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
	thread t1(func1);  // thread 객체를 생성한다. 이 때 전달인자로 준 함수를 새 thread에서 실행한다
	thread t2(func2);
	thread t3(func3);

	t1.join();  // 각 thread들이 실행을 종료하면 join()이 return한다
	t2.join();  // thread의 종료 순서는 상관없다. t2가 t1보다 먼저 종료할 경우 t1의 join()이 먼저 return하고 t2가 종료되어있으면 바로 t2의 join()이 return한다
	t3.join();
	
	return 0;
}