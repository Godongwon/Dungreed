#pragma once
#include"Object/Missile/Missile.h"
#include "Object/Unit/player/Player.h"
class Darkball : public Missile
{
private:

public:
	Darkball();
	~Darkball();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};
