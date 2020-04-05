#pragma once
#include"Object/Unit/Monster/Monster.h"
#include"Object/Missile/Note.h"
class Banshee : public Monster
{
private:
	Note * _note;
protected:
	void compareAttack_Banshees();
public:
	Banshee();
	~Banshee();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳

};

