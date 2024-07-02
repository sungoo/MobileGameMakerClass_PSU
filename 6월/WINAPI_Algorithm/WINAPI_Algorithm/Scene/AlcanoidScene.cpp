#include "pch.h"
#include "AlcanoidScene.h"
#include "Alcanoid/Ship.h"

AlcanoidScene::AlcanoidScene()
{
	_player = make_shared<Ship>();
}

AlcanoidScene::~AlcanoidScene()
{
}

void AlcanoidScene::Update()
{
	_player->Update();
}

void AlcanoidScene::Render(HDC hdc)
{
	_player->Render(hdc);
}
