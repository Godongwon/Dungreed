#include "stdafx.h"
#include "Jukdo.h"


Jukdo::Jukdo()
{
}
Jukdo::~Jukdo()
{
}

HRESULT Jukdo::init()
{
	_itemName = "�׵�";
	_kinditem = MAIN_HAND;
	_itemAtk = 15;
	_itemDef = 0;
	_itemPrice = 3000;
	_item_img_store = new image;
	_item_img_inven = new image;
	_item_img_field = new image;
	// �������� ����� ���̽� �̹�����.
	_item_img_store->init("resource/image/item/weapon/�׵�.bmp",
		(int)(5 * _MULTIPLE_STORE), (int)(20 * _MULTIPLE_STORE));
	_item_img_inven->init("resource/image/item/weapon/�׵�.bmp",
		(int)(5 * _MULTIPLE_INVEN), (int)(20 * _MULTIPLE_INVEN));
	_item_img_field->init("resource/image/item/weapon/�׵�.bmp",
		(int)(5 * _MULTIPLE_FIELD), (int)(20 * _MULTIPLE_FIELD));

	return S_OK;
}
void Jukdo::release()
{
	release_imgs();
}
void Jukdo::update()
{
}
void Jukdo::render()
{
}
