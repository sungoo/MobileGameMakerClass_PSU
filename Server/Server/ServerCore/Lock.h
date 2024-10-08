#pragma once

uint64 bitflag = 0x0000'0000;

// [WWWWWWWW] [WWWWWWWW] : Write Lock을 걸은 ThreadID 기입
// [RRRRRRRR] [RRRRRRRR] : Read  Lock을 걸었을 때 몇 번이나 걸었는지 횟수
// [WWWWWWWW] [WWWWWWWW] [RRRRRRRR] [RRRRRRRR] => 32비트 플래그
// W : Write Flag (상호 베타적, Thread ID)
// R : Read Flag (Shared Lock Count)

class Lock
{
	enum : uint32
	{
		ACQUIRE_TIMEOUT_TICK = 10000,
		MAX_SPIN_COUNT = 5000,
		WRITE_THREAD_MASK = 0xFFFF'0000,
		READ_COUNT_MASK = 0x0000'FFFF,
		EMPTY_FLAG = 0x0000'0000
	};
public:
	void WriteLock();
	void WriteUnlock();
	void ReadLock();
	void ReadUnlock();
private:
	Atomic<uint32> _lockFlag = EMPTY_FLAG;
	uint16 _writeCount = 0;

};

//RAII(Resource Acquisition Is Initialization) 패턴
class ReadLockGuard
{
public:
	ReadLockGuard(Lock& lock)
	:_lock(lock)
	{
		_lock.ReadLock();
	}

	~ReadLockGuard()
	{
		_lock.ReadUnlock();
	}
private:
	Lock& _lock;
};

class WriteLockGuard
{
public:
	WriteLockGuard(Lock& lock)
	:_lock(lock)
	{
		_lock.WriteLock();
	}

	~WriteLockGuard()
	{
		_lock.WriteUnlock();
	}
private:
	Lock& _lock;
};