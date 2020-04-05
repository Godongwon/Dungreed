#pragma once
#include"base/gameNode.h"
enum KIND_ITEM
{
	MAIN_HAND,
	SUB_HAND,
	ACC,
	FOOD,
	GAIN
};
enum RENDER_LOCATION
{
	LOCATION_STORE,
	LOCATION_INVENTORY,
	LOCATION_FIELD
};
class Item : public gameNode
{
protected:
	double _MULTIPLE_STORE = 3.5;
	double _MULTIPLE_INVEN = 1.5;
	double _MULTIPLE_FIELD = 3;
protected:
	KIND_ITEM _kinditem;		//아이템종류
	string _itemName;			//아이템이름
	// 아이템을 그릴 정보다.
	RECT _item_rect;			//아이템을 출력하기 위한 렉트
	image* _item_img_store = nullptr;		//상점용 아이템 이미지
	image* _item_img_inven = nullptr;		//인벤토리용 아이템 이미지
	image* _item_img_field = nullptr;		//필드 드랍용 아이템 이미지
	// 아이템이 지닌 정보다.
	int _itemAtk;	// 아이템공격력
	int _itemDef;	// 아이템방어력
	int _itemPrice;	// 가격
	int _itemHp;	// 체력
protected:
	// 배율을 조정한다.
	void set_multiples(double multiply);
	void release_imgs();
public:
	int get_itemPrice() { return _itemPrice; }
	image get_item_img_field() { return *_item_img_field; }
	KIND_ITEM get_kinditem() { return _kinditem; }
	void set_item_rect(RECT rect) { _item_rect = rect; }
public:
	Item();
	~Item();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(HDC hdc, RENDER_LOCATION location, POINT center);
	void frameRender(HDC hdc, POINT center);
	void frameRender(HDC hdc);
};

