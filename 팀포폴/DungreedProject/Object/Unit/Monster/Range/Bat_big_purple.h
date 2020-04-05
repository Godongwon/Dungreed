#pragma once
#include"Object/Unit/Monster/Monster.h"
#include"Object/Missile/Fireball_small.h"
class Bat_big_purple : public Monster
{
private:
	Fireball_small * _fireball_small;
protected:
	void compareAttack_bats_big_purple();
	void makeFireBall_small_bat_big_purple();
	int makeCount;
public:
	Bat_big_purple();
	~Bat_big_purple();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�

};

