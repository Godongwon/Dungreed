#pragma once
#include"Object/Unit/Monster/Monster.h"

class Bat_small_neutral : public Monster
{
public:

public:
	Bat_small_neutral();
	~Bat_small_neutral();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳

};

