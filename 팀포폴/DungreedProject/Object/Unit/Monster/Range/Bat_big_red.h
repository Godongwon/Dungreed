#pragma once
#include"Object/Unit/Monster/Monster.h"
#include"Object/Missile/Fireball_small.h"
class Bat_big_red : public Monster
{
private:
	Fireball_small * _fireball_small;
protected:
	void compareAttack_bats_big_red();
	void makeFireBall_small_bat_big_red();

public:
	Bat_big_red();
	~Bat_big_red();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�

};