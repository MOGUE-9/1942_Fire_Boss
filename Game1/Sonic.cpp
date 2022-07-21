#include "stdafx.h"


Sonic::Sonic()
{
	col = new ObRect();
	col->scale = Vector2(150.0f / 4.0f, 60.0f) * 2.5f;
	col->isFilled = false;
	col->pivot = OFFSET_B;
	col->SetWorldPosX(-500.0f);
	col->SetWorldPosY(-400.0f + (48.0f * 3.0f));
	col->collider = COLLIDER::RECT;

	run = new ObImage(L"run.bmp");
	run->SetParentRT(*col);
	run->visible = true;
	run->scale = Vector2(192.0f / 4.0f, 60.0f) * 2.5f;
	run->pivot = OFFSET_B;
	run->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	run->maxFrame.x = 4;

	spin = new ObImage(L"spin.bmp");
	spin->SetParentRT(*col);
	spin->visible = false;
	spin->scale = Vector2(48.0f, 48.0f) * 2.5f;
	spin->pivot = OFFSET_B;
	spin->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	spin->maxFrame.x = 5;

	state = SCSTATE::RUN;
	time = 0.0f;
	gravity = 0.0f;

	isDamaged = false;
	damageTime = 0.0f;
}

Sonic::~Sonic()
{
}

void Sonic::Update()
{
	if (isDamaged)
	{
		damageTime -= DELTA;

		run->color = Color(RANDOM->Float(0.5f, 1.0f), 0.5f, 0.5f, 1.0f);
		spin->color = Color(RANDOM->Float(0.5f, 1.0f), 0.5f, 0.5f, 1.0f);

		if (damageTime < 0.0f)
		{
			run->color = Color(0.5f, 0.5f, 0.5f, 1.0f);
			spin->color = Color(0.5f, 0.5f, 0.5f, 1.0f);
			isDamaged = false;
		}

	}

	col->MoveWorldPos(RIGHT * 200.0f * DELTA);
	CAM->position += RIGHT * 200.0f * DELTA;

	col->MoveWorldPos(DOWN * gravity * DELTA);
	gravity += 700.0f * DELTA;

	app.deltaScale += 0.1f * TIMER->GetDelta();
	app.deltaScale = Utility::Saturate(app.deltaScale, 1.0f, 6.0f);

	if (state == SCSTATE::RUN)
	{
		col->scale.y = 60.0f * 2.5f;
		//run -> jump
		if (INPUT->KeyPress(VK_SPACE))
		{
			spin->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
			state = SCSTATE::JUMP;
			run->visible = false;
			spin->visible = true;
			gravity = -700.0f;
			doubleJump = false;
		}


		//run -> spin
		if (INPUT->KeyPress(VK_DOWN))
		{
			spin->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
			state = SCSTATE::SPIN;
			run->visible = false;
			spin->visible = true;
		}
	}
	else if (state == SCSTATE::SPIN)
	{
		col->scale.y = 48.0f * 2.5f;
		//spin -> run
		if (INPUT->KeyUp(VK_DOWN))
		{
			state = SCSTATE::RUN;
			run->visible = true;
			spin->visible = false;
		}

		//spin -> jump
		if (INPUT->KeyPress(VK_SPACE))
		{
			state = SCSTATE::JUMP;
			run->visible = false;
			spin->visible = true;
			gravity = -700.0f;
			doubleJump = false;
		}
	}
	else //jump
	{
		col->scale.y = 48.0f * 2.5f;

		if (INPUT->KeyDown(VK_SPACE) && !doubleJump)
		{
			gravity = -700.0f;
			doubleJump = true;
		}
		
	}

	col->Update();
	run->Update();
	spin->Update();
}

void Sonic::Render()
{
	col->Render();
	run->Render();
	spin->Render();
}
