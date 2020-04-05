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

	RECT ground;//테스트용 바닥 -> 나중에 지워라
	
	bool b_isDungeonstance;
	bool b_isDoorOpen = true;
	int _DungeonstanceCount=0;
public:
	stage();
	~stage();
	void stage_Make(SCENE_KIND sceneKind);
	RECT getGroud() { return ground; }

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳

};



