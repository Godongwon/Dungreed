#pragma once
#include "base/gameNode.h"
enum NPC_WAY
{
	NPC_WAY_LEFT = 0,//����
	NPC_WAY_RIGHT//������
};
class NPC : public gameNode
{
protected:
	NPC_WAY _npcWay;//NPC����
	RECT _npcRC;//NPC��Ʈ
	image* _npcImg; //NPC�̹���
	animation* _npcAni;//NPC���ϸ��̼�

	int _focousNpcX;//NPC����
	

public:
	NPC();
	~NPC();


	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

