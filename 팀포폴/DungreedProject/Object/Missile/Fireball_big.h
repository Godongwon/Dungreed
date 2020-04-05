#pragma once
#include"Object/Missile/Missile.h"

class Fireball_big : public Missile
{
public:
	Fireball_big();
	~Fireball_big();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳
};
