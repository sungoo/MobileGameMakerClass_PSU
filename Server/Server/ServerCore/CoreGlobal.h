#pragma once

class ThreadManager;

class CoreGlobal
{
private:
	CoreGlobal();
	~CoreGlobal();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new CoreGlobal();
	}

	static void Delete()
	{
		if (_instance != nullptr)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

	static CoreGlobal* Instance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	ThreadManager* TM() { return _threadManager; }

private:
	static CoreGlobal* _instance;

	ThreadManager* _threadManager;
};
