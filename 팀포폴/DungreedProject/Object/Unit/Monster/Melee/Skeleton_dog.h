#pragma once
#include"Object/Unit/Monster/Monster.h"

class Skeleton_dog : public Monster
{
public:

public:
	Skeleton_dog();
	~Skeleton_dog();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�

};


