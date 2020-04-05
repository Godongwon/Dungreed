#pragma once
#include"Object/Unit/Monster/Monster.h"

class Minotaurs : public Monster
{
public:

public:
	Minotaurs();
	~Minotaurs();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳
};


