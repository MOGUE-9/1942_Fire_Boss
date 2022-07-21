#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	bg = new ObImage(L"Oven1.png");
	bg->scale = Vector2(569.0f, 320.0f) * 2.5f;
	bg->space = SPACE::SCREEN;

	bg2 = new ObImage(L"Oven2.png");
	bg2->scale = Vector2(862.0f, 320.0f) * 2.5f;
	bg2->space = SPACE::SCREEN;

	for (int i = 0; i < FMAX; i++)
	{
		floor[i].col= new ObRect();
		floor[i].col->scale = Vector2(79.0f, 10.0f) * 3.0f;
		floor[i].col->pivot = OFFSET_LT;
		floor[i].col->isFilled = false;
		floor[i].col->SetWorldPos(Vector2(-800.0f + (79.0f * 3.0f * i) , -400.0f + (48.0f * 3.0f)));
		floor[i].col->collider = COLLIDER::RECT;

		floor[i].img = new ObImage(L"floor.bmp");
		floor[i].img->scale = Vector2(79.0f, 48.0f) * 3.0f;
		floor[i].img->pivot = OFFSET_LT;
		//floor[i].img->SetWorldPos(Vector2(-800.0f + (79.0f * 3.0f * i), -400.0f + (48.0f * 3.0f)));

		floor[i].img->SetParentRT(*floor[i].col);
		floor[i].isVisible = true;
	}

	for (int i = 0; i < RMAX; i++)
	{
		rock[i] = new ObImage(L"Rock.bmp");
		rock[i]->scale = Vector2(60.0f, 60.0f) * 2.5f;
		rock[i]->pivot = OFFSET_B;
		rock[i]->SetWorldPos(Vector2(800.0f + i * 450.0f, -130.0f * RANDOM->Int(1, 2)));
		rock[i]->collider = COLLIDER::CIRCLE;
	}

	sonic = new Sonic();
}

void Main::Release()
{

}

void Main::Update()
{
	ImGui::SliderFloat("TestScale", &testScale, 1.0f, 10.0f);
	//test->scale = Vector2(79.0f, 48.0f) * testScale;
	ImGui::SliderFloat("DeltaScale", &app.deltaScale, 1.0f, 10.0f);

	//1초에 100픽셀 움직여라
	bg->uv.x += DELTA / bg->scale.x * 50.0f;
	bg->uv.z += DELTA / bg->scale.x * 50.0f;

	bg2->uv.x += DELTA / bg2->scale.x * 100.0f;
	bg2->uv.z += DELTA / bg2->scale.x * 100.0f;

	//bg->uv.y += DELTA * 0.1f;
	//bg->uv.w += DELTA * 0.1f;

	for (int i = 0; i < FMAX; i++)
	{
		if (sonic->col->GetWorldPos().x - floor[i].col->GetWorldPos().x > 600.0f)
		{
			floor[i].col->MoveWorldPos(Vector2(79.0f * 3.0f * FMAX, 0.0f));

			if (RANDOM->Int(0,5) == 5)
			{
				floor[i].isVisible = false;
			}

		}
		floor[i].img->Update();
		floor[i].col->Update();
	}

	for (int i = 0; i < RMAX; i++)
	{
		if (sonic->col->GetWorldPos().x - rock[i]->GetWorldPos().x > 600.0f)
		{
			rock[i]->MoveWorldPos(Vector2(2000.0f, 0.0f));

			rock[i]->SetWorldPosY(-130.0f * RANDOM->Int(1, 2));
		}
		rock[i]->Update();
	}

	sonic->Update();
	bg->Update();
	bg2->Update();

}

void Main::LateUpdate()
{
	for (int i = 0; i < FMAX; i++)
	{
		if (!floor[i].isVisible) continue;

		if (floor[i].col->Intersect(sonic->col->GetWorldPos()))
		{
			sonic->col->SetWorldPosY(-256.0f);
			sonic->gravity = 0.0f;

			if (sonic->state == SCSTATE::JUMP)
			{
				sonic->state = SCSTATE::RUN;
				sonic->run->visible = true;
				sonic->spin->visible = false;
			}
			sonic->col->Update();
			sonic->run->Update();
			sonic->spin->Update();
		}
	}

	for (int i = 0; i < RMAX; i++)
	{
		if (rock[i]->Intersect(sonic->col))
		{
			sonic->SetDamage();
		}
	}

}

void Main::Render()
{
	bg->Render();
	bg2->Render();
	sonic->Render();

	
	for (int i = 0; i < FMAX; i++)
	{
		if (!floor[i].isVisible) continue;

		floor[i].img->Render();
		floor[i].col->Render();
	}

	for (int i = 0; i < RMAX; i++)
	{
		rock[i]->Render();
	}

}

void Main::ResizeScreen()
{

}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(1400,800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}