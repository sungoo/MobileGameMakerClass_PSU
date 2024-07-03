#include "pch.h"
#include "AlcanoidScene.h"
#include "Alcanoid/Ship.h"
#include "Alcanoid/Alca_Block.h"
#include "Alcanoid/Ball.h"

AlcanoidScene::AlcanoidScene()
{
	Vector2 offset = { 80, 30 };

	_player = make_shared<Ship>();
	_blocks.reserve(MAXWIDTHCNT);

	for (int i = 0; i < MAXWIDTHCNT; i++)
	{
		vector<shared_ptr<Alca_Block>> blocks_X;
		blocks_X.reserve(MAXHIGHTCNT);

		for (int j = 0; j < MAXHIGHTCNT; j++)
		{
			Vector2 blockOffset = offset + Vector2(100.0f * i, 50.0f * j);

			shared_ptr<Alca_Block> block = make_shared<Alca_Block>();

			block->SetCenter(blockOffset);
			blocks_X.push_back(block);
		}
		_blocks.push_back(blocks_X);
	}
}

AlcanoidScene::~AlcanoidScene()
{
}

void AlcanoidScene::Update()
{
	_player->Update();

	for (auto blocks_x : _blocks) {
		for (auto block : blocks_x) {
			block->Update();
		}
	}
	for (auto blocks_x : _blocks) {
		for (auto block : blocks_x) {
			_player->GetBall()->BlockCrash(block);
		}
	}
	
}

void AlcanoidScene::Render(HDC hdc)
{
	_player->Render(hdc);
	for (auto blocks_x : _blocks) {
		for (auto block : blocks_x) {
			block->Render(hdc);
		}
	}
}
