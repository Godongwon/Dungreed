#pragma once
#include"Object/Unit/Monster/Monster.h"

class Minotaurs : public Monster
{
public:

public:
	Minotaurs();
	~Minotaurs();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};


