#pragma once
enum class ITEMTYPE
{
	NONE,
	PLAYERSPEED,
};

class Block
{
private:
	
	ITEMTYPE item;

public:
	int life;
	ObRect* block;

	Block();
	void Update();
	void Render();
};

