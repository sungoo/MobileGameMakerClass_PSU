#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

#include "ThreadManager.h"
#include "Lock.h"

const int MAX_NUMBER = 100'00000;

bool IsPrime(int num)
{
	int FindNum = (int)sqrt(num);

	if (num == 2 || num == 3)
		return true;

	if (num < 2)
		return false;

	for (int i = 2; i <= FindNum; i++)
	{
		if (num % i == 0)
			return false;
	}
	return true;
}

atomic<int> result = 0;

void PrimeRange(int start, int end)
{
	//primeNum이면 result를 1 올린다.
	for (int i = start; i < end; i++)
	{
		if (IsPrime(i))
			result.fetch_add(1);
	}
}

int solution()
{
	vector<thread> threads;

	//스레드 개수 반환
	int coreCount = thread::hardware_concurrency();

	int work = MAX_NUMBER / coreCount;

	/*int answer = 0;
	for (int i = 2; i < MAX_NUMBER; i++)
	{
		if (IsPrime(i))
			answer++;
	}*/
	for (int i = 0; i < coreCount; i++)
	{
		//0 ~ MAX
		int start = work * i;
		int end = work * (i + 1);
		if (end > MAX_NUMBER || i == coreCount - 1) end = MAX_NUMBER;

		threads.push_back(thread(PrimeRange, start, end));
	}

	for (auto& thread : threads)
		thread.join();

	return result;
}

int main()
{
	CoreGlobal::Create();

	int64 start = ::GetTickCount64();

	int answer = 0;

	answer = 0;

	answer = solution();

	cout << answer << endl;

	int64 end = ::GetTickCount64();

	cout << "걸린 시간 : " << end - start << "ms" << endl;

	CoreGlobal::Delete();
}