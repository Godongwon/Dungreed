#pragma once
#include"Object/Missile/Missile.h"
#include "Object/Unit/player/Player.h"
class BeliarSword : public Missile
{
private:
	float _beliarSwordAngle;
public:
	BeliarSword();
	~BeliarSword();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};
