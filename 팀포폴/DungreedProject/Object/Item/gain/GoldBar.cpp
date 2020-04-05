#include "stdafx.h"
#include "GoldBar.h"


GoldBar::GoldBar()
{
}


GoldBar::~GoldBar()
{
}

HRESULT GoldBar::init()
{
	// �������� �⺻ ������.
	_itemName = "����";
	_kinditem = GAIN;
	_itemPrice = 100;

	_item_img_field = new image;
	// �������� ����� ���̽� �̹�����.
	_item_img_field->init("resource/image/item/gain/GoldBar.bmp",
		(int)(140 * _MULTIPLE_FIELD), (int)(9 * _MULTIPLE_FIELD), 7, 1);
	_item_img_field->set_frameSection(1, 0, 6, 5, 1);
	_item_img_field->setFrameX(0);
	return S_OK;
}

void GoldBar::release()
{
}

void GoldBar::update()
{
	_item_img_field->frameUpdate(false);
}

void GoldBar::render()
{
}
