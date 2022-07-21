#include "stdafx.h"

Bullet::Bullet()
{
	//화살
	arrow.SetWorldPos(Vector2(2000.0f, 2000.0f));
	arrow.scale.x = 15.0f;
	arrow.scale.y = 15.0f;
	arrow.visible = false;

	arrowPet.SetParentRT(arrow);
	arrowPet.SetLocalPos(Vector2(30.0f, 30.0f));
	arrowPet.scale.x = 15.0f;
	arrowPet.scale.y = 15.0f;
	arrowPet.axis = true;
	arrowPet.visible = false;
}

Bullet::~Bullet()
{
}

bool Bullet::Shoot(Vector2 fireDir, float scalar, Vector2 firePos)
{
	if (arrow.visible == false)
	{
		arrow.visible = true;
		arrowPet.visible = true;

		//발사 시점에서 플레이어 위치를 받아옴
		//arrow.SetWorldPos(player.GetWorldPos());
		arrow.SetWorldPos(firePos);

		this->fireDir = fireDir;
		this->scalar = scalar * 6.0f;

		gravity = 0.0f;
		arrowPet.rotation2 = 0.0f;

		//this->scalar = scalar;
		//				150 ~ 450
		//this->scalar = -scalar * 2.0f;

		return true;
	}

	return false;
}

void Bullet::Update()
{
	if (not arrow.visible) return;

	//scalar += 300.0f * DELTA;
	//cout << scalar << endl;

	gravity += 600.0f * DELTA;

	Vector2 velocity = fireDir * scalar + DOWN * gravity;
	//Vector2 velocity = fireDir * scalar;

	arrow.MoveWorldPos(velocity * DELTA); //화살 움직임
	arrowPet.rotation2 += 360.0f * ToRadian * DELTA;

	arrow.rotation = Utility::DirToRadian(velocity);

	arrow.Update();
	arrowPet.Update();

	//Vector2 dis = player.GetWorldPos() - arrow.GetWorldPos();
	//float length = dis.Length();

	//if (length > 1468)
	//{
	//	arrow.visible = false;
	//	arrowPet.visible = false;
	//}
}

void Bullet::LateUpdate()
{
	//충돌판정

	//위에 벽
	if (arrow.GetWorldPos().y >= app.GetHeight() * 0.5f + CAM->position.y)
	{
		/*arrow.visible = false;
		arrowPet.visible = false;*/

		//방향전환
		fireDir.y *= -1.0f;
		gravity *= -1.0f;

		gravity *= 0.8f;
		scalar *= 0.8f;

		//위치전환
		arrow.SetWorldPosY(app.GetHeight() * 0.5f + CAM->position.y);
	}

	//아래 벽
	if (arrow.GetWorldPos().y <= -app.GetHeight() * 0.5f + CAM->position.y)
	{
		/*arrow.visible = false;
		arrowPet.visible = false;*/

		//방향전환
		fireDir.y *= -1.0f;
		gravity *= -1.0f;

		gravity *= 0.8f;
		scalar *= 0.8f;

		//위치전환
		arrow.SetWorldPosY(-app.GetHeight() * 0.5f + CAM->position.y);
	}

	//양쪽벽
	if (arrow.GetWorldPos().x >= app.GetWidth() * 0.5f + CAM->position.x)
	{
		/*arrow.visible = false;
		arrowPet.visible = false;*/

		//방향전환
		fireDir.x *= -1.0f;

		scalar *= 0.8f;

		//위치전환
		arrow.SetWorldPosX(app.GetWidth() * 0.5f + CAM->position.x);
	}

	if (arrow.GetWorldPos().x <= -app.GetWidth() * 0.5f + CAM->position.x)
	{
		/*arrow.visible = false;
		arrowPet.visible = false;*/

		//방향전환
		fireDir.x *= -1.0f;

		scalar *= 0.8f;

		//위치전환
		arrow.SetWorldPosX(-app.GetWidth() * 0.5f + CAM->position.x);
	}
}

void Bullet::Render()
{
	arrow.Render();
	arrowPet.Render();
}
