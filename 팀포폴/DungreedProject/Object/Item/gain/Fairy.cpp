#include "stdafx.h"
#include "Fairy.h"


Fairy::Fairy()
{
}
Fairy::~Fairy()
{
}
HRESULT Fairy::init()
{
	// �������� �⺻ ������.
	_itemName = "����";
	_kinditem = GAIN;
	_itemHp = 10;

	_item_img_field = new image;
	// �������� ����� ���̽� �̹�����.
	_item_img_field->init("resource/image/item/gain/Fairy.bmp",
		(int)(144 * _MULTIPLE_FIELD), (int)(11 * _MULTIPLE_FIELD), 16, 1);
	_item_img_field->set_frameSection(1, 0, 15, 5, 1);
	_item_img_field->setFrameX(0);
	return S_OK;
}

void Fairy::release()
{
}

void Fairy::update()
{
	_item_img_field->frameUpdate(false);
}

void Fairy::render()
{
}
