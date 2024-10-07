#include "pch.h"
#include "Lock.h"

//Lock 정책
// 1. Read는 상호베타적일 필요 없이 공유 Count만 올린다
// 2. Write는 무조건 상호베타적이여야 한다.
// -> Write중에는 다른 스레드에서 Read 할 수 없다.
// -> Read 중에 다른 스레드에서 Write를 시도할 수 없다.
//    * 내 스레드에서 Write하고 Read는 가능하다.
//    * 하지만 내 스레드라도 Read하고 Write는 불가능.
//

//[WWWWWWWW] [WWWWWWWW] [RRRRRRRR] [RRRRRRRR]
//&
//[11111111] [11111111] [00000000] [00000000]
// 
//[wwwwwwww] [wwwwwwww]

void Lock::WriteLock()
{
	const uint32 lockThreadID = (_lockFlag & WRITE_THREAD_MASK) >> 16;

	//같은 thread가 WriteLock을 재귀로 잡았을 때 통과
	if (LThreadID == lockThreadID)
	{
		_writeCount++;
		return;
	}

	const int64 beginTick = ::GetTickCount64();

	//한번도 lock이 안 걸려있었거나, 다른 스레드에서 이미 lock을 잡아놨을 때
	//Spin Lock : CAS (Compare and Swap)
	//한번도 lock이 안 걸려있었으면 (Expected) WriteCount++ 하고 통과.
	//그게 아니라면(다른 애가 lock), spin
	const int32 desired = (LThreadID << 16) & WRITE_THREAD_MASK;
	while (true)
	{
		for (uint32 spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
		{
			uint32 expected = EMPTY_FLAG;
			if (_lockFlag.compare_exchange_strong(OUT expected, desired))
			{
				_writeCount++;
				return;
			}
		}

		if (::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
			CRASH("Lock TimeOut");

		this_thread::yield();
	}
}

void Lock::WriteUnlock()
{
	//Write Lock 상태 ...-> Read..(X)
	//Read Lock 상태 ... -> Write (X)
	//ReadLock을 다 풀기 전에는 WirteUnlock 불가능

	//자기 자신이 ReadLock을 건 다음에 WriteLock이 걸리면 안되는데 걸렸을 때 예외처리
	if ((_lockFlag.load() & READ_COUNT_MASK) != 0)
		CRASH("INVALID_UNLOCK_ORDER");

	const int32 lockCount = --_writeCount;
	if (lockCount == 0)
		_lockFlag.store(EMPTY_FLAG);
}

void Lock::ReadLock()
{
	//lock 건 애가 자기 자신이면 통과
	const uint32 lockThreadID = (_lockFlag & WRITE_THREAD_MASK) >> 16;

	//같은 thread가 WriteLock을 재귀로 잡았을 때 통과
	if (LThreadID == lockThreadID)
	{
		_writeCount++;
		return;
	}

	//lock을 건 애가 따로 있으면... 불가
	//read lock 만 걸려있거나 아무도 lock을 잡지 않으면 통과
	const int64 beginTick = ::GetTickCount64();
	while (true)
	{
		//uint32 desired = (_lockFlag.load() & READ_COUNT_MASK) + 1;
		for (uint64 spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
		{
			//threadID를 무시(0으로 밀기)하고 ReadCount만 체크
			uint32 expected = (_lockFlag.load() & READ_COUNT_MASK);
			if (_lockFlag.compare_exchange_strong(expected, expected + 1))
				return;
		}

		if (::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
			CRASH("Lock TimeOut");

		this_thread::yield();
	}
}

void Lock::ReadUnlock()
{
	//Read를 동시에 두 번 풀어주면 안되는데, 그렇게 되면 CRASH
	if ((_lockFlag.fetch_sub(1) & READ_COUNT_MASK) == 0)
		CRASH("MULTIPLE_UNLOCK");
}
