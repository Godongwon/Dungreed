#pragma once
#include"Object/Unit/Monster/Monster.h"

class Skeleton_warrior_onehand : public Monster
{
public:

public:
	Skeleton_warrior_onehand();
	~Skeleton_warrior_onehand();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�

};

