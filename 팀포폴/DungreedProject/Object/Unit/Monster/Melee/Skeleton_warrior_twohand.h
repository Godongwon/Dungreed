#pragma once
#include"Object/Unit/Monster/Monster.h"

class Skeleton_warrior_twohand : public Monster
{
public:

public:
	Skeleton_warrior_twohand();
	~Skeleton_warrior_twohand();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�

};

