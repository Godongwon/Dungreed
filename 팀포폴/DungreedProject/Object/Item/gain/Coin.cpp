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
	// 아이템의 기본 정보다.
	_itemName = "코인";
	_kinditem = GAIN;
	_itemPrice = 10;

	_item_img_field = new image;
	// 아이템을 출력할 베이스 이미지다.
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
