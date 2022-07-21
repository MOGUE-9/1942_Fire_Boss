#pragma once
class Boss
{
public:

	ObRect*		col;
	ObImage*	boss;

	bool		isDamaged;

	float		damageTime{ 0.1f };

	Vector2		direction{ RIGHT };

public:
	Boss();
	~Boss();

	void Update();
	void LateUpdate();

	void Render();
};

