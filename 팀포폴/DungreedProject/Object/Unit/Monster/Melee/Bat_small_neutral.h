#pragma once
#include"Object/Unit/Monster/Monster.h"

class Bat_small_neutral : public Monster
{
public:

public:
	Bat_small_neutral();
	~Bat_small_neutral();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�

};

