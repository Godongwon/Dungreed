#include "stdafx.h"
#include "ShortSword.h"


ShortSword::ShortSword()
{
}
ShortSword::~ShortSword()
{
}

HRESULT ShortSword::init()
{
	_itemName = "단검";
	_kinditem = MAIN_HAND;
	_itemAtk = 5;
	_itemDef = 0;
	_itemPrice = 1000;
	_item_img_store = new image;
	_item_img_inven = new image;
	_item_img_field = new image;
	// 아이템을 출력할 베이스 이미지다.
	_item_img_store->init("resource/image/item/weapon/단검.bmp",
		(int)(7 * _MULTIPLE_STORE), (int)(18 * _MULTIPLE_STORE));
	_item_img_inven->init("resource/image/item/weapon/단검.bmp",
		(int)(7 * _MULTIPLE_INVEN), (int)(18 * _MULTIPLE_INVEN));
	_item_img_field->init("resource/image/item/weapon/단검.bmp",
		(int)(7 * _MULTIPLE_FIELD), (int)(18 * _MULTIPLE_FIELD));
	return S_OK;
}

void ShortSword::release()
{
	release_imgs();
}

void ShortSword::update()
{
}

void ShortSword::render()
{
}
