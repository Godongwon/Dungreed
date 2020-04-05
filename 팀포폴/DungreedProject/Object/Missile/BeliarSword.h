#pragma once
#include"Object/Missile/Missile.h"
#include "Object/Unit/player/Player.h"
class BeliarSword : public Missile
{
private:
	float _beliarSwordAngle;
public:
	BeliarSword();
	~BeliarSword();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳
};
