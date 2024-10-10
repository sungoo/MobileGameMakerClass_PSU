#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

#include "ThreadManager.h"
#include "Lock.h"

void Login()
{
	while (true)
	{
		AccountManager::GetInstance()->Login();
	}
}

void Save()
{
	while (true)
	{
		UserManager::GetInstance()->Save();
	}
}

int main()
{
	CoreGlobal::Create();

	AccountManager::Create();
	UserManager::Create();

	//dead lock
	TM_M->Launch(Login);
	TM_M->Launch(Save);

	CoreGlobal::Instance()->TM()->Join();

	AccountManager::Delete();
	UserManager::Delete();

	CoreGlobal::Delete();
}