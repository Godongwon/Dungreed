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

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};

