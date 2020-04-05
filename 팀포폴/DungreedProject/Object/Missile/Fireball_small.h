#pragma once
#include"Object/Missile/Missile.h"
#include "Object/Unit/player/Player.h"
class Fireball_small : public Missile
{
private:
	//float _delay = 0;
public:
	//void init_delay(float delay) { _delay = delay; }
public:
	Fireball_small();
	~Fireball_small();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳
};
