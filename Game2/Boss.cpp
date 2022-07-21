#include "stdafx.h"

Boss::Boss()
{
	boss = new ObImage(L"zzangu_3.jpg");
	boss->scale = Vector2(401.0f, 400.0f) * 0.5f;
	boss->SetWorldPosX(0.0f);
	boss->SetWorldPosY(300.0f);
	boss->collider = COLLIDER::RECT;

	
}

Boss::~Boss()
{
}

void Boss::Update()
{
	if (isDamaged)
	{
		damageTime -= DELTA;
		boss->color = Color(RANDOM->Float(0.5f, 1.0f), 0.5f, 0.5f, 1.0f);

		if (damageTime < 0.0f)
		{
			boss->color = Color(0.5f, 0.5f, 0.5f, 1.0f);
			damageTime = 2.0f;
			isDamaged = false;
		}
	}

	//248

	boss->MoveWorldPos(direction * 5.0f * DELTA);
	//boss->SetLocalPosX(Utility::Saturate(boss->GetWorldPos().x, -124.0f, 124.0f));

	if (boss->GetWorldPos().x < -app.GetHalfWidth() + boss->scale.x * 0.5f)
	{
		//boss->SetWorldPosX(-24.0f);
		direction = RIGHT;
	}
	else if (boss->GetWorldPos().x > app.GetHalfWidth() - boss->scale.x * 0.5f)
	{
		//boss->SetWorldPosX(24.0f);
		direction = LEFT;
	}



	boss->Update();
}

void Boss::LateUpdate()
{
}

void Boss::Render()
{
	boss->Render();
}
