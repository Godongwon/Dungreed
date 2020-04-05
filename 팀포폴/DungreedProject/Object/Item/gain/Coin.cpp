#include "stdafx.h"
#include "Coin.h"
Coin::Coin()
{
}
Coin::~Coin()
{
}

HRESULT Coin::init()
{
	// �������� �⺻ ������.
	_itemName = "����";
	_kinditem = GAIN;
	_itemPrice = 10;

	_item_img_field = new image;
	// �������� ����� ���̽� �̹�����.
	_item_img_field->init("resource/image/item/gain/Coin.bmp",
		(int)(56 * _MULTIPLE_FIELD), (int)(7 * _MULTIPLE_FIELD), 8, 1);
	_item_img_field->set_frameSection(1, 0, 7, 5, 1);
	_item_img_field->setFrameX(0);
	return S_OK;
}

void Coin::release()
{
}

void Coin::update()
{
	_item_img_field->frameUpdate(false);
}

void Coin::render()
{
	//_item_img_field->frameRender()
}
