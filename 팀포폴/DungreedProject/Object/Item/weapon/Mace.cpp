#include "stdafx.h"
#include "Mace.h"


Mace::Mace()
{
}
Mace::~Mace()
{
}

HRESULT Mace::init()
{
	_itemName = "�б�";
	_kinditem = MAIN_HAND;
	_itemAtk = 35;
	_itemDef = 0;
	_itemPrice = 8000;
	_item_img_store = new image;
	_item_img_inven = new image;
	_item_img_field = new image;
	// �������� ����� ���̽� �̹�����.
	_item_img_store->init("resource/image/item/weapon/�б�.bmp",
		(int)(9 * _MULTIPLE_STORE), (int)(22 * _MULTIPLE_STORE));
	_item_img_inven->init("resource/image/item/weapon/�б�.bmp",
		(int)(9 * _MULTIPLE_INVEN), (int)(22 * _MULTIPLE_INVEN));
	_item_img_field->init("resource/image/item/weapon/�б�.bmp",
		(int)(9 * _MULTIPLE_FIELD), (int)(22 * _MULTIPLE_FIELD));
	return S_OK;
}

void Mace::release()
{
	release_imgs();
}

void Mace::update()
{
}

void Mace::render()
{
}
