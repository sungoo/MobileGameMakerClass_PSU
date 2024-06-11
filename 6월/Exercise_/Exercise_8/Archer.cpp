#include "Archer.h"
#include "Pet.h"

Archer::Archer(Pet* pet) :Player(), _pet(pet)
{
	
}

Archer::Archer(int hp) : Player(hp)
{
}

Archer::~Archer()
{
	// Áñ°Å¿ü´Ù ³» Æê :(
	//if (_pet != nullptr)
	//	delete _pet;
}

