#include "pch.h"
#include "UserManager.h"
#include "AccountManager.h"

UserManager* UserManager::_instance = nullptr;
void UserManager::Save()
{
	WRITE_LOCK;

	//Account 확인
	cout << "Save 시도!!" << endl;

	//DeadLock 유발
	Account* account = AccountManager::GetInstance()->GetAccount(10);

	//계정정보 수정 혹은 저장
	//DB에 저장

	return;
}
