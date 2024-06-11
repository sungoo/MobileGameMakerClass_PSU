#include "Archer.h"

Archer::Archer()
{
	// 이런 저런 정보 채울 예정~
	if(_pet == nullptr)
		_pet = new Pet();
}

Archer::Archer(int hp) : Player(hp)
{
	// 이런 저런 정보 채울 예정~
	if (_pet == nullptr)
		_pet = new Pet();
}

Archer::~Archer()
{
	// 즐거웠다 내 펫 :(
	if (_pet != nullptr)
		delete _pet;
}

