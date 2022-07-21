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
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
