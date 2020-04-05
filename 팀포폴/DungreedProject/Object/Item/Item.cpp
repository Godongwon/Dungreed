#include "stdafx.h"
#include "Item.h"

void Item::set_multiples(double multiply)
{
	_MULTIPLE_STORE *= multiply;
	_MULTIPLE_INVEN *= multiply;
	_MULTIPLE_FIELD *= multiply;
}
void Item::release_imgs()
{
	_item_img_store->release();
	_item_img_store = nullptr;
	_item_img_inven->release();
	_item_img_inven = nullptr;
	_item_img_field->release();
	_item_img_field = nullptr;
}

Item::Item()
{
}
Item::~Item()
{
}

HRESULT Item::init()
{
	return S_OK;
}

void Item::release()
{
}

void Item::update()
{
}

void Item::render()
{
}
void Item::render(HDC hdc, RENDER_LOCATION location, POINT center)
{
	switch (location)
	{
	case LOCATION_STORE:
		_item_rect = RectMakeCenter(center.x, center.y,
			_item_img_store->getWidth(), _item_img_store->getHeight());
		_item_img_store->render(hdc, _item_rect.left, _item_rect.top);
		break;
	case LOCATION_INVENTORY:
		_item_rect = RectMakeCenter(center.x, center.y,
			_item_img_inven->getWidth(), _item_img_inven->getHeight());
		_item_img_inven->render(hdc, _item_rect.left, _item_rect.top);
		break;
	case LOCATION_FIELD:
		_item_rect = RectMakeCenter(center.x, center.y,
			_item_img_field->getWidth(), _item_img_field->getHeight());
		_item_img_field->render(hdc, _item_rect.left, _item_rect.top);
		break;
	}
}
void Item::frameRender(HDC hdc, POINT center)
{
	RECT rect = RectMakeCenter(center.x, center.y,
		_item_img_field->getWidth(), _item_img_field->getHeight());
	_item_img_field->frameRender(hdc, rect.left, rect.top);
}

void Item::frameRender(HDC hdc)
{
	_item_img_field->frameRender(hdc, _item_rect.left, _item_rect.top);
}
