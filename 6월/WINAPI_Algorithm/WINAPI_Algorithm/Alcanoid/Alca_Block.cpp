#include "pch.h"
#include "Alca_Block.h"

Alca_Block::Alca_Block()
{
	_col = make_shared<RectCollider>(CENTER, Vector2(40, 20));
}

Alca_Block::~Alca_Block()
{
}

void Alca_Block::Update()
{
}

void Alca_Block::Render(HDC hdc)
{
	if (_isBreak) return;

	_col->Render(hdc);
}

void Alca_Block::SetCenter(Vector2 position)
{
	_col->_center = position;
}

void Alca_Block::Hit()
{
	SetBrake(true);
}
