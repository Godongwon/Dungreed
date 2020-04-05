#include "stdafx.h"
#include "Gladius.h"


Gladius::Gladius()
{
}
Gladius::~Gladius()
{
}

HRESULT Gladius::init()
{
	// 아이템의 기본 정보다.
	_itemName = "글라디우스";
	_kinditem = MAIN_HAND;
	_itemAtk = 25;
	_itemDef = 0;
	_itemPrice = 6000;
	_item_img_store = new image;
	_item_img_inven = new image;
	_item_img_field = new image;
	// 아이템을 출력할 베이스 이미지다.
	_item_img_store->init("resource/image/item/weapon/글라디우스.bmp",
		(int)(5 * _MULTIPLE_STORE), (int)(20 * _MULTIPLE_STORE));
	_item_img_inven->init("resource/image/item/weapon/글라디우스.bmp",
		(int)(5 * _MULTIPLE_INVEN), (int)(20 * _MULTIPLE_INVEN));
	_item_img_field->init("resource/image/item/weapon/글라디우스.bmp",
		(int)(5 * _MULTIPLE_FIELD), (int)(20 * _MULTIPLE_FIELD));
	return S_OK;
}

void Gladius::release()
{
	release_imgs();
}

void Gladius::update()
{
}

void Gladius::render()
{
}
