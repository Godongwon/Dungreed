#pragma once
#include"Object/Missile/Missile.h"
#include "Object/Unit/player/Player.h"
class Beliar_DeadEffect : public Missile
{
private:

public:
	Beliar_DeadEffect();
	~Beliar_DeadEffect();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};
