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
	
	image* _weaponShop;//무기상점 뒷배경
	RECT _weaponShopRC;//무기상점 뒷배경
	// 아이템 리스트를 보여주기 위한 STL::map
	mItem _itemlist;

	image* _touchNPCkeyImg;
	RECT   _touchNPCkeyRC;

	// 상점 아저씨를 위한 변수
	int _weaponNPCImgnum;//NPC이미지 크기 곱하는 수
	int _weaponImgnumX;//무기이미지 크기 곱하는 수
	int _weaponImgnumY;//무기이미지 크기 곱하는 수
	
	bool b_touchWeaponNPC; //무기npc와 터치중이냐
	bool b_openWeaponshop;



protected:
	//무기 추가 (이름,무기종류, 이미지키이름,공격력,방어력,가격)
	//void addItem(string name, KIND_ITEM kinditem, string imageKeyName, int itemnum,int Atk, int Def, int price);
	void init_itemlist();
	void npcWay();
	void npcTouch();//NPC터치하는 함수
	void npcTouch_IMG();
public:
	weaponNpc();
	~weaponNpc();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

