#pragma once

enum class SCSTATE
{
	RUN,
	JUMP,
	SPIN
};

class Sonic
{
public:
	ObRect*		col;
	ObImage*	run;
	ObImage*	spin;

	SCSTATE		state;

	float		time;
	float		gravity;

	bool		isDamaged;
	float		damageTime;
	bool		doubleJump;

public:
	Sonic();
	~Sonic();

	void Update();
	void Render();

	void SetDamage()
	{
		isDamaged = true;
		damageTime = 0.2f;
	}

};

