#include "Knight.h"
#include <iostream>
using namespace std;


Knight::Knight() 
{

}

Knight::Knight(int hp) : Player(hp)
{

}

Knight::~Knight()
{

}

void Knight::PrintInfo()
{
	cout << "------ KnightInfo ------" << endl;
	cout << "HP: " << _hp << endl;
	cout << "ATT: " << _attack << endl;
}

