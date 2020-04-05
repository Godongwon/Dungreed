#include "stdafx.h"
#include "LongSword.h"


LongSword::LongSword()
{
}
LongSword::~LongSword()
{
}

HRESULT LongSword::init()
{
	_itemName = "���";
	_kinditem = MAIN_HAND;
	_itemAtk = 10;
	_itemDef = 0;
	_itemPrice = 2000;
	_item_img_store = new image;
	_item_img_inven = new image;
	_item_img_field = new image;
	// �������� ����� ���̽� �̹�����.
	_item_img_store->init("resource/image/item/weapon/���.bmp",
		(int)(6 * _MULTIPLE_STORE), (int)(22 * _MULTIPLE_STORE));
	_item_img_inven->init("resource/image/item/weapon/���.bmp",
		(int)(6 * _MULTIPLE_INVEN), (int)(22 * _MULTIPLE_INVEN));
	_item_img_field->init("resource/image/item/weapon/���.bmp",
		(int)(6 * _MULTIPLE_FIELD), (int)(22 * _MULTIPLE_FIELD));
	return S_OK;
}
void LongSword::release()
{
	release_imgs();
}
void LongSword::update()
{
}
void LongSword::render()
{
}
