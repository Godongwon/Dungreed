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

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�

};

