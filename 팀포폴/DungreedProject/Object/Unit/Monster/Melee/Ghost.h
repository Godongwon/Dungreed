#pragma once
#include"Object/Unit/Monster/Monster.h"

class Ghost : public Monster
{
public:

public:
	Ghost();
	~Ghost();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�

};

