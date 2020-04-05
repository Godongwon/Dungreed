#pragma once
#include "base/gameNode.h"

enum SCENE_KIND
{
	START_SCENE,
	TOWN_SCENE,
	MiNO_ROOM,
	NOMAL_ROOM,
	BANSI_ROOM,
	MAPTOOL
};
class stage : public gameNode
{
private:
	image * _img;

	RECT ground;//�׽�Ʈ�� �ٴ� -> ���߿� ������
	
	bool b_isDungeonstance;
	bool b_isDoorOpen = true;
	int _DungeonstanceCount=0;
public:
	stage();
	~stage();
	void stage_Make(SCENE_KIND sceneKind);
	RECT getGroud() { return ground; }

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�

};



