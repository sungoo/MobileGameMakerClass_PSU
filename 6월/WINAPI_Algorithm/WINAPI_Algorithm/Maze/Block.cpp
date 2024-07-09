#include "pch.h"
#include "Block.h"

Block::Block():
	RectCollider(Vector2(), Vector2(5, 5))
{
	_brushes.push_back(CreateSolidBrush(GREEN));
	_brushes.push_back(CreateSolidBrush(RED));
	_brushes.push_back(CreateSolidBrush(BLUE));
	_brushes.push_back(CreateSolidBrush(INDIGO));

	SetGreen();
}

Block::~Block()
{
	for (auto brush : _brushes) {
		DeleteObject(brush);
	}
}

void Block::Update()
{
	RectCollider::Update();
}

void Block::Render(HDC hdc)
{
	SelectObject(hdc, _brushes[static_cast<int>(_type)]);
	RectCollider::Render(hdc);
}

void Block::SetPosition(Vector2 pos)
{
	_center = pos;
}

void Block::SetBlockType(BlockType type)
{
	_type = type;
	_curPen = _pens[static_cast<int>(_type)];
}
