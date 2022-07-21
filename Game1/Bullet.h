#pragma once

struct Bullet
{
	ObLine arrow;
	ObCircle arrowPet;
	Vector2 firePos;

	//ฝ๎ดย บคลอ
	float scalar;
	Vector2 fireDir;

	//ม฿ทย
	float gravity;

	Bullet();
	
	bool Shoot(Vector2 fireDir, float scalar, Vector2 firePos);
	void Update();
	void LateUpdate();
	void Render();
};

