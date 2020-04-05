#pragma once
#include "Object/Unit/NPC/NPC.h"
#include "Object/Unit/stage.h"
#include "Object/Item/Item.h"

class weaponNpc:public NPC
{
private:
	typedef map<string, Item*> mItem;
private:
	stage* _stage;
	
	image* _weaponShop;//������� �޹��
	RECT _weaponShopRC;//������� �޹��
	// ������ ����Ʈ�� �����ֱ� ���� STL::map
	mItem _itemlist;

	image* _touchNPCkeyImg;
	RECT   _touchNPCkeyRC;

	// ���� �������� ���� ����
	int _weaponNPCImgnum;//NPC�̹��� ũ�� ���ϴ� ��
	int _weaponImgnumX;//�����̹��� ũ�� ���ϴ� ��
	int _weaponImgnumY;//�����̹��� ũ�� ���ϴ� ��
	
	bool b_touchWeaponNPC; //����npc�� ��ġ���̳�
	bool b_openWeaponshop;



protected:
	//���� �߰� (�̸�,��������, �̹���Ű�̸�,���ݷ�,����,����)
	//void addItem(string name, KIND_ITEM kinditem, string imageKeyName, int itemnum,int Atk, int Def, int price);
	void init_itemlist();
	void npcWay();
	void npcTouch();//NPC��ġ�ϴ� �Լ�
	void npcTouch_IMG();
public:
	weaponNpc();
	~weaponNpc();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

