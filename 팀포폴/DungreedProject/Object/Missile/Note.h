#pragma once
#include"Object/Missile/Missile.h"
#include "Object/Unit/player/Player.h"

class Note : public Missile
{
public:
	Note();
	~Note();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};
