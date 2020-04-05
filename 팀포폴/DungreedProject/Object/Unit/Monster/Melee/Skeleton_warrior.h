#pragma once
#include"Object/Unit/Monster/Monster.h"

class Skeleton_warrior : public Monster
{
public:

public:
	Skeleton_warrior();
	~Skeleton_warrior();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳

};


