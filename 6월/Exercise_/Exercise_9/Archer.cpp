#include "Archer.h"
#include "Pet.h"

Archer::Archer(Pet* pet) : _pet(pet)
{
	
}

Archer::Archer(int hp) : Player(hp), _pet(nullptr)
{
}

Archer::~Archer()
{
	// Áñ°Å¿ü´Ù ³» Æê :(
	_pet = nullptr;
}

void Archer::AddHp(int value)
{
	Player::AddHp(value);

	// Á×¾úÀ¸¸é Æêµµ ³¯¸°´Ù
	if (IsDead())
	{
		
		_pet = nullptr;
	}
}
