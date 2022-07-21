#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	bg = new ObImage(L"bg.png");
	bg->scale = Vector2(224.0f, 2144.0f) * 2.0f;
	bg->space = SPACE::SCREEN;

	bg->pivot = OFFSET_B;
	bg->SetWorldPosY(-app.GetHalfHeight());

	pl = new ST_Player();

	bullet = new ST_Bullet[BMAX];

	boss = new Boss();
}

void Main::Release()
{
	SafeDelete(bg);
	SafeDelete(pl);
}

void Main::Update()
{
	bg->uv.y -= DELTA / bg->scale.y * 100.0f;
	bg->uv.w -= DELTA / bg->scale.y * 100.0f;

	bg->Update();

	if (INPUT->KeyUp(VK_SHIFT))
	{
		for (int i = 0; i < BMAX; i++)
		{
			if (bullet[i].Shoot(pl->GetWorldPos()))
			{
				shootTime = 0.0f;
				break;
			}
		}
	}

	//if (INPUT->KeyPress(VK_SHIFT))
	//{
	//	for (int i = 0; i < BMAX; i++)
	//	{
	//		if (TIMER->GetTick(shootTime, 0.5f))
	//		{
	//			if (bullet[i].Shoot(pl->GetWorldPos()))
	//			{
	//				shootTime = 0.0f;
	//				break;
	//			}
	//		}
	//	}
	//}

	for (int i = 0; i < BMAX; i++)
	{
		bullet[i].Update();
	}

	boss->Update();
	pl->Update();
}

void Main::LateUpdate()
{
	for (int i = 0; i < BMAX; i++)
	{
		if (bullet[i].col->Intersect(boss->boss))
		{
			boss->isDamaged = true;
			bullet[i].Attack();
		}
		bullet[i].col->Update();
		boss->Update();

	}
	pl->LateUpdate();

}

void Main::Render()
{
	bg->Render();
	for (int i = 0; i < BMAX; i++)
	{
		bullet[i].Render();
	}
	//bullet->Render();

	boss->Render();

	pl->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(224.0f * 2.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}