#pragma once
#include"Object/Missile/Missile.h"

class Fireball_big : public Missile
{
public:
	Fireball_big();
	~Fireball_big();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};
