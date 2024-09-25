#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

AccountManager* AccountManager::_instance = nullptr;
void AccountManager::Login()
{
	std::lock_guard<std::mutex> lg(_mutex);

	//login 성공, ..?
	//-> 어떤 유저인지 확인
	User* user = UserManager::GetInstance()->GetUser(10);

	//User 확인 성공 및 클라이언트의 메시지

	return;
}
