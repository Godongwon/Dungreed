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
	_itemName = "��ġ";
	_kinditem = MAIN_HAND;
	_itemAtk = 80;
	_itemDef = 0;
	_itemPrice = 15000;
	_item_img_store = new image;
	_item_img_inven = new image;
	_item_img_field = new image;
	// ���⼭ ������ �ٽ� �����Ѵ�.
	set_multiples(0.8);
	// �������� ����� ���̽� �̹�����.
	_item_img_store->init("resource/image/item/weapon/��ġ.bmp",
		(int)(25 * _MULTIPLE_STORE), (int)(41 * _MULTIPLE_STORE));
	_item_img_inven->init("resource/image/item/weapon/��ġ.bmp",
		(int)(25 * _MULTIPLE_INVEN), (int)(41 * _MULTIPLE_INVEN));
	_item_img_field->init("resource/image/item/weapon/��ġ.bmp",
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
