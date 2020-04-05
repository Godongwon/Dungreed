#pragma once
#include "base/gameNode.h"
enum NPC_WAY
{
	NPC_WAY_LEFT = 0,//왼쪽
	NPC_WAY_RIGHT//오른쪽
};
class NPC : public gameNode
{
protected:
	NPC_WAY _npcWay;//NPC방향
	RECT _npcRC;//NPC렉트
	image* _npcImg; //NPC이미지
	animation* _npcAni;//NPC에니메이션

	int _focousNpcX;//NPC중점
	

public:
	NPC();
	~NPC();


	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

