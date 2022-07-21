#pragma once
#define BMAX 30

class Main : public Scene
{
private:
	ObImage*	bg;
	ST_Player*	pl;
	
	ST_Bullet*	bullet;
	Boss*		boss;

	//ObImage* bullet;
	//ObImage* boss;

	float shootTime = 0.0f;


public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
