#include "pch.h"
#include "Line2Scene.h"

Line2Scene::Line2Scene()
{
	_line1 = make_shared<Line>(Vector2(50, 50), Vector2(50, 50));
	_line2 = make_shared<Line>(Vector2(50, 600), Vector2(800, 50));

	_circle = make_shared<CircleCollider>(Vector2(300, 300), 5);
}

Line2Scene::~Line2Scene()
{
}

void Line2Scene::Update()
{
	_line1->_end = mousePos;

	HResult hitresult = _line1->IsCollision(_line2);

	if (hitresult.isCollision) {
		_line1->SetGreen();
		_line2->SetGreen();
		_circle->_center = hitresult.hitPoint;
	}
	else {
		_line1->SetRed();
		_line2->SetRed();
	}

	_line1->Update();
	_line2->Update();
	_circle->Update();
}

void Line2Scene::Render(HDC hdc)
{
	_line1->Render(hdc);
	_line2->Render(hdc);
	_circle->Render(hdc);
}
