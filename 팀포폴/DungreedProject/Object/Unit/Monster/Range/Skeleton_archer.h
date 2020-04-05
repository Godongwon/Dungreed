#pragma once
#include"Object/Unit/Monster/Monster.h"
#include "Object/Missile/Arrow.h"
class Skeleton_archer : public Monster
{
private:
	Arrow * _arrow;
protected:
	void compareAttack_Archers();
public:
	Skeleton_archer();
	~Skeleton_archer();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳
};

