#include "stdafx.h"
#include "AllItemList.h"

void AllItemList::init_weaponKeysAll()
{
	_itemKeys.push_back("�۶��콺");
	_itemKeys.push_back("�׵�");
	_itemKeys.push_back("���");
	_itemKeys.push_back("�ܰ�");
	_itemKeys.push_back("�б�");
	_itemKeys.push_back("��ġ");
}
void AllItemList::delete_weaponKeysAll()
{
	auto iter = _itemKeys.begin();
	for (;iter != _itemKeys.end();)
	{
		iter = _itemKeys.erase(iter);
	}
	swap(_itemKeys, vItemKey());
}

Item * AllItemList::make_item(string strKey)
{
	Item * item = nullptr;
	// ����� ������ ����
	if (strKey.compare("�۶��콺") == 0) { item = new Gladius; }
	else if (strKey.compare("�׵�") == 0) { item = new Jukdo; }
	else if (strKey.compare("���") == 0) { item = new LongSword; }
	else if (strKey.compare("�ܰ�") == 0) { item = new ShortSword; }
	else if (strKey.compare("�б�") == 0) { item = new Mace; }
	else if (strKey.compare("��ġ") == 0) { item = new WarHammer; }
	// ������ ������°� ���� �� ����
	else if (strKey.compare("����") == 0) { item = new Coin; }
	else if (strKey.compare("����") == 0) { item = new GoldBar; }
	else if (strKey.compare("����") == 0) { item = new Fairy; }

	if (item != nullptr) { item->init(); }
	return item;
}

Item * AllItemList::make_item_toField(string strKey, POINT center)
{
	Item * item = nullptr;
	item = make_item(strKey);
	image image = item->get_item_img_field();
	RECT rect = RectMakeCenter(center.x, center.y,
		image.getWidth(), image.getHeight());
	item->set_item_rect(rect);
	return item;
}

void AllItemList::push_itemList(Item * item)
{
	_itemList.push_back(item);
}

void AllItemList::delete_itemListAll()
{
	auto iter = _itemList.begin();
	for (;iter != _itemList.end(); )
	{
		iter = _itemList.erase(iter);
	}
	swap(_itemList, vItem());
}

void AllItemList::update_itemList()
{
	auto iter = _itemList.begin();
	for (;iter != _itemList.end();iter++)
	{
		(*iter)->update();
	}
}

void AllItemList::draw_itemList()
{
	auto iter = _itemList.begin();
	for (;iter != _itemList.end();iter++)
	{
		if ((*iter)->get_kinditem() == GAIN)
		{
			(*iter)->frameRender(getMemDC());
		}
		else
		{
			(*iter)->render();
		}
	}
}

AllItemList::AllItemList()
{
}
AllItemList::~AllItemList()
{
}

HRESULT AllItemList::init()
{
	init_weaponKeysAll();
	return S_OK;
}

void AllItemList::release()
{
	delete_weaponKeysAll();
}

void AllItemList::update()
{
}

void AllItemList::render()
{
}
