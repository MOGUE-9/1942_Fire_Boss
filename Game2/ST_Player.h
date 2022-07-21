#pragma once
class ST_Player
{
private:
	ObImage*	LR;
	ObImage*	boost;
	ObRect*		col;

	bool		isBoosting;
	float		LRkey;

	Vector2		dir;

public:
	ST_Player();
	~ST_Player();

	Vector2 GetWorldPos();

	void Update();
	void LateUpdate();
	void Render();

};

