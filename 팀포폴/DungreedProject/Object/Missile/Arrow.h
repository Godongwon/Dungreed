#pragma once
#include"Object/Missile/Missile.h"
#include "Object/Unit/player/Player.h"
class Arrow : public Missile
{
public:
	//RECT _arrow;
public:
	Arrow();
	~Arrow();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};
