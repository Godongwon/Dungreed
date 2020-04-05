#include "stdafx.h"
#include "WarHammer.h"


WarHammer::WarHammer()
{
}
WarHammer::~WarHammer()
{
}

HRESULT WarHammer::init()
{
	_itemName = "망치";
	_kinditem = MAIN_HAND;
	_itemAtk = 80;
	_itemDef = 0;
	_itemPrice = 15000;
	_item_img_store = new image;
	_item_img_inven = new image;
	_item_img_field = new image;
	// 여기서 배율을 다시 조정한다.
	set_multiples(0.8);
	// 아이템을 출력할 베이스 이미지다.
	_item_img_store->init("resource/image/item/weapon/망치.bmp",
		(int)(25 * _MULTIPLE_STORE), (int)(41 * _MULTIPLE_STORE));
	_item_img_inven->init("resource/image/item/weapon/망치.bmp",
		(int)(25 * _MULTIPLE_INVEN), (int)(41 * _MULTIPLE_INVEN));
	_item_img_field->init("resource/image/item/weapon/망치.bmp",
		(int)(25 * _MULTIPLE_FIELD), (int)(41 * _MULTIPLE_FIELD));
	return S_OK;
}

void WarHammer::release()
{
	release_imgs();
}

void WarHammer::update()
{
}

void WarHammer::render()
{
}
