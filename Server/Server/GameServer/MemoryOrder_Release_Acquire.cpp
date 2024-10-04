#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

atomic<int32> flag;
int32 value;

void Producer()
{
	value = 10;

	flag.store(1, memory_order_release); //seq_cst ... 이 위로 모든 값들이 보장된다.
}

void Consumer()
{
	while (flag.load(memory_order_acquire) != 1)
	{
		//release는 이 위로 모든 값들 보장
		//acquire는 이 아래로 모든 값들 보장
		//항상 둘은 짝지어야 한다.
	};

	cout << value << endl;
}

int main()
{
	flag.store(0, memory_order_seq_cst);
	value = 0;

	thread t1(Producer);
	thread t2(Consumer);

	t1.join();
	t2.join();

	//Memory 정책
	// 1. seq_cst (sequential consistency) 순서적 일관성 => 매우 엄격
	//  - 코드 재배치 x, 가시성 o
	// 
	// 2. acquire - release => 중도
	// 
	// 3. relaxed => 컴파일러 최적화 여지가 많다.
	//

	return 0;
}