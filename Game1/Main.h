#pragma once
#define FMAX 8
#define RMAX 3

struct FLOOR
{
	ObImage* img;
	ObRect* col;
	bool	isVisible;
};

class Main : public Scene
{
private:
	ObImage*	test;
	float		testScale;

	Sonic*		sonic;

	FLOOR		floor[FMAX];
	ObImage*	rock[RMAX];

	ObImage*	bg; //배경
	ObImage*	bg2; //불


public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
