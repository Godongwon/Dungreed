#pragma once
#include"Object/Missile/Missile.h"
#include "Object/Unit/player/Player.h"
class Fireball_small : public Missile
{
private:
	//float _delay = 0;
public:
	//void init_delay(float delay) { _delay = delay; }
public:
	Fireball_small();
	~Fireball_small();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};
