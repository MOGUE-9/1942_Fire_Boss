#include "stdafx.h"

Block::Block()
{
	life = RANDOM->Int(1,3);

	block = new ObRect();
	//block->color = Color(life/3.0f, life / 3.0f, life / 3.0f, 1.0f);

	if (RANDOM->Int(1, 10) == 4)
	{
		item = ITEMTYPE::PLAYERSPEED;
	}
}

void Block::Update()
{
	block->Update();
}

void Block::Render()
{
	switch (life)
	{
	case 1:
		block->color = Color(1.0f, 0.5f, 0.5f, 1.0f);
		break;
	case 2:
		block->color = Color(0.5f, 1.0f, 0.5f, 1.0f);
		break;
	case 3:
		block->color = Color(0.5f, 0.5f, 1.0f, 1.0f);
		break;
	}

	if (life == 0)
	{
		return;
	}
	else
	{
		block->Render();
	}
	
}
