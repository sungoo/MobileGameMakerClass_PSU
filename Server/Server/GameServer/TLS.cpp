#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

//TLS 영역
// 각 스레드마다 갖고 있는 고유 메모리 저장공간
// 
// 거실에 일감이 있다.
// -> 거실에 있는 일감을 4명이서 분배해 일을 하고 싶다
// -> 4명이서 거실에 다 같이 일을 하려고 한다.
// -> 일감을 조금씩 떼어서 각자 자기 방에 들어가 일을 해놓고
//    다시 거실에 갖다놓는다면?
//
// TLS (Thread Local Storage)

thread_local int32 LThreadId; //TLS 영역

void MySetThreadId(int32 id)
{
	LThreadId = id;

	while (true)
	{
		cout << "Hi, Im thread : " << LThreadId << endl;
		this_thread::sleep_for(1000ms);
	}
}

int main()
{
	vector<thread> threads;

	for (int i = 0; i < 10; i++)
	{
		threads.push_back(thread(MySetThreadId, (i + 1)));
	}
	for (auto& t : threads)
	{
		t.join();
	}

	return 0;
}