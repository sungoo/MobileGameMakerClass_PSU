#include "pch.h"
#include "MazeScene.h"
#include "Maze/Block.h"
#include "Maze/Maze.h"
#include "Maze/Player.h"

MazeScene::MazeScene()
{
	_maze = make_shared<Maze>();
	_mazeRunner = make_shared<Player>(_maze);

	_mazeRunner->BeginPlay();
}

MazeScene::~MazeScene()
{
}

void MazeScene::Update()
{
	_maze->Update();
	_mazeRunner->Update();
}

void MazeScene::Render(HDC hdc)
{
	wstring temp = L"hello Maze";

	_maze->Render(hdc);
	TextOut(hdc, CENTER._x, CENTER._y, temp.c_str(), temp.size());
}
