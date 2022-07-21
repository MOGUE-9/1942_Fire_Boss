#include "stdafx.h"

ST_Bullet::ST_Bullet()
{
	col = new ObRect();
	col->scale = Vector2(14.0f, 50.0f); //
	col->pivot = OFFSET_B;
	col->isFilled = false;
	col->collider = COLLIDER::RECT;
	col->visible = false;

	bullet = new ObImage(L"PlayeBullet.png");
	bullet->SetParentRT(*col);
	bullet->scale = Vector2(68.0f / 4.0f , 48.0f) * 2.0f;
	bullet->maxFrame.x = 4;
	bullet->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	bullet->pivot = OFFSET_B;
	bullet->visible = false;

}

ST_Bullet::~ST_Bullet()
{
}

bool ST_Bullet::Shoot(Vector2 plPos)
{
	//지금 안보이는 애들만 들어오게
	if (!isShoot)
	{
		col->SetWorldPos(plPos);
		bullet->visible = true;
		isShoot = true;
		return true;
	}
	return false;
}

void ST_Bullet::Update()
{
	//cout << app.GetHalfHeight() << endl;

	if (isShoot)
	{
		col->MoveWorldPos(UP * 500.0f * DELTA);

		if (col->GetWorldPos().y > app.GetHalfHeight())
		{
			bullet->visible = false;
			isShoot = false;
		}
	}
	if (isAttack)
	{
		bullet->visible = false;
		isAttack = false;
	}


	col->Update();
	bullet->Update();
}

void ST_Bullet::LateUpdate()
{
}

void ST_Bullet::Render()
{

	col->Render();
	bullet->Render();
}
