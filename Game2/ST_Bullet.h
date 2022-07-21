#pragma once
class ST_Bullet
{
private:
	ObImage*	bullet;

	bool		isShoot{ false };
	bool		isAttack{ false };

	Vector2		position;

public:
	ST_Bullet();
	~ST_Bullet();

	ObRect* col;


	bool Shoot(Vector2 plPos);
	void Attack() 
	{
		isAttack = true;
	};

	void Update();
	void LateUpdate();

	void Render();
};

