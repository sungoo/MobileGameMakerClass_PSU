#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

AccountManager* AccountManager::_instance = nullptr;
void AccountManager::Login()
{
	WRITE_LOCK;

	//login 성공, ..?
	//-> 어떤 유저인지 확인
	cout << "Login 시도!" << endl;

	//DeadLock 유발
	User* user = UserManager::GetInstance()->GetUser(10);

	//User 확인 성공 및 클라이언트의 메시지

	return;
}
