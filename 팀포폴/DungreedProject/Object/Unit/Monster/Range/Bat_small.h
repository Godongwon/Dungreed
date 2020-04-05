#pragma once
#include"Object/Unit/Monster/Monster.h"
#include "Object/Missile/Fireball_small.h"
class Bat_small : public Monster
{
private:
	Fireball_small * _fireball_small;
protected:
	void compareAttack_bats_small();
public:
	Bat_small();
	~Bat_small();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳

};

