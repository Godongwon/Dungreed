#pragma once
#include"Object/Unit/Monster/Monster.h"

class Skeleton_warrior : public Monster
{
public:

public:
	Skeleton_warrior();
	~Skeleton_warrior();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�

};


