#include "stdafx.h"
#include "Store.h"
#include "Object/Unit/player/Player.h"
void Store::init_defaultWindow()
{
	_window_img = new image;
	_window_img->init("resource/image/weaponshop/��üâ.bmp",
		(int)(117 * _MULTIPLE), (int)(WINSIZEY));
	_window_rect = RectMake(
		CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2,
		CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2,
		_window_img->getWidth(), _window_img->getHeight());;
	_window_center.x = (LONG)((_window_rect.left + _window_rect.right) * 0.5);
	_window_center.y = (LONG)((_window_rect.top + _window_rect.bottom) * 0.5);
	// ���� ���� ������ ������ �����츦 �ʱ�ȭ�Ѵ�.
	_selfeeWindow_rect = RectMakeCenter(
		_window_center.x,
		(int)(_window_center.y - _window_img->getHeight() * 0.4) - 10,
		_window_img->getWidth() - 20, 75);
	// �������� ������ �����츦 �ʱ�ȭ�Ѵ�.
	_itemWindow_rect = RectMakeCenter(
		_window_center.x,
		_window_center.y + 40,
		_window_img->getWidth() - 20, _window_img->getHeight() - 100);
}
void Store::draw_defaultWindow()
{
	_window_img->render(CAMERAMANAGER->getCameraDC(),
		_window_rect.left, _window_rect.top,
		_window_rect.right, _window_rect.bottom);
	/*ColorRect(CAMERAMANAGER->getCameraDC(), _itemWindow_rect,
		RGB(254, 254, 254));*/
	if (_bDebug == true)
	{
		ColorRect(CAMERAMANAGER->getCameraDC(), _selfeeWindow_rect,
			RGB(254, 254, 254));
	}
}
void Store::init_itemWindow()
{
	int itemWindowW = (int)(_itemWindow_rect.right - _itemWindow_rect.left);
	int itemWindowH = (int)(_itemWindow_rect.bottom - _itemWindow_rect.top);
	int itemW = (int)(23 * _MULTIPLE);
	int itemH = (int)(23 * _MULTIPLE);	// 23�� ����â.bmp �̹����� height
	int blankH = 2;						// ��, �Ʒ� ����
	int blankW = 4;						// ������RECT�� ����RECT�� ���� ����

	_itemLine_img = IMAGEMANAGER->addImage("ItemWindow",
		"resource/image/weaponshop/����â.bmp", itemWindowW, itemH);

	POINT centerTemp;
	int current_top = _itemWindow_rect.top;
	for (int i = 0; i < 6; i++)
	{
		current_top += blankH;
		// ������ ���� 1���� �̹����� �׸��� ���� RECT�� 6�� �ʱ�ȭ�Ѵ�.
		_itemLine_rect[i] = RectMake(_itemWindow_rect.left, current_top,
			_itemLine_img->getWidth(), _itemLine_img->getHeight());
		// ������ �̹����� ����ϱ� ���� RECT�� 6�� �ʱ�ȭ�Ѵ�.
		// _itemLine_rect�� ������ ��� ��ġ�� ��´�.
		centerTemp.x = (LONG)(
			(_itemLine_rect[i].left + _itemLine_rect[i].right) * 0.5);
		centerTemp.y = (LONG)((_itemLine_rect[i].top +
			_itemLine_rect[i].bottom) * 0.5);
		centerTemp.x -= (LONG)(_itemLine_img->getWidth() * 0.5 -
			itemW * 0.5);
		_item_rect[i] = RectMakeCenter(centerTemp.x, centerTemp.y,
			itemW, itemH);
		_item_center[i] = PointMake(centerTemp.x, centerTemp.y);
		// ������ ������ ����ϱ� ���� RECT�� 6�� �ʱ�ȭ�Ѵ�.
		// _item_rect�� right, top�� �������� ��ġ�� ��´�.
		_desc_rect[i] = RectMake(
			(int)(_item_rect[i].right + blankW),
			_item_rect[i].top,
			(int)(itemW * 3.6), itemH);
		current_top += itemH;
	}
}
void Store::draw_itemWindow()
{
	for (int i = 0; i < 6; i++)
	{
		_itemLine_img->render(CAMERAMANAGER->getCameraDC(),
			_itemLine_rect[i].left, _itemLine_rect[i].top);
		if (_bDebug == true)
		{
			ColorRect(CAMERAMANAGER->getCameraDC(), _item_rect[i],
				RGB(254, 254, 254));
			ColorRect(CAMERAMANAGER->getCameraDC(), _desc_rect[i],
				RGB(254, 254, 254));
		}
	}
}
void Store::init_selfee()
{
	POINT center;
	int width, height;
	center.x = (LONG)((_selfeeWindow_rect.left + _selfeeWindow_rect.right) * 0.5);
	center.y = (LONG)((_selfeeWindow_rect.top + _selfeeWindow_rect.bottom) * 0.5);
	width = (int)(249);
	height = (int)(65);
	_selfee_img = new image;
	_selfee_img->init("resource/image/weaponshop/weaponNPC_selfee.bmp",
		width, height);
	_selfee_rect = RectMakeCenter(center.x, center.y, width, height);
}
void Store::draw_selfee()
{
	_selfee_img->render(CAMERAMANAGER->getCameraDC(),
		_selfee_rect.left, _selfee_rect.top);
}
//============================================================
//==			�������� �� ������ �׸��� �κ�					==
//============================================================
void Store::init_goods()
{
	auto itemKeys = _allItem->get_itemKeys();
	const int size = itemKeys.size();
	// 0 ~ size-1 �� �迭�� �־ �����ϰ� ���´�.
	int * randomNum = new int[size];
	for (int i = 0; i < size; i++) { randomNum[i] = i; }
	for (int i = 0; i < 100; i++)
	{
		int sour = RND->getInt(size - 1);
		int dest = RND->getInt(size - 1);
		swap(randomNum[sour], randomNum[dest]);
	}
	// ������ ������ 6���� �ʱ�ȭ�Ѵ�.
	Item * item;
	for (int i = 0; i < 6; i++)
	{
		item = _allItem->make_item(itemKeys[randomNum[i]]);
		item->init();
		_items.push_back(item);
		item = nullptr;
	}
	SAFE_DELETE(randomNum);
}
void Store::draw_goods()
{
	int index = 0;
	// �������� �� �������� �׸���.
	auto iter = _items.begin();
	for (;iter != _items.end(); iter++)
	{
		(*iter)->render(CAMERAMANAGER->getCameraDC(), LOCATION_STORE,
			_item_center[index]);
		index++;
	}
}
//============================================================
//==				�������� ������ ��� �κ�					==
//============================================================
void Store::buy_item()
{
	int index = 0;
	_bBuying = true;
	auto iter = _items.begin();
	for (;iter != _items.end();)
	{
		if (PtInRect(&_itemLine_rect[index], m_ptMouse))
		{
			if (check_enoughMoney(*iter) == true)
			{
				PLAYER->input_itemList(*iter);
				iter = _items.erase(iter);
				index++;
				break;
			}
			else { break; }//else: ���� ������� �ʴ�.
		}// 1. �������� Ŭ�� �ߴٸ� ���� ������� Ȯ���Ѵ�. �÷��̾�� �ְ�, �����, break;
		else
		{
			iter++;
			index++;
		}
	}
}
bool Store::check_enoughMoney(Item * item)
{
	int golds = PLAYER->get_golds();
	int price = item->get_itemPrice();
	if (golds >= price) 
	{
		golds -= price;
		PLAYER->set_golds(golds);
		return true; 
	}
	else{ return false; }
}
Store::Store()
{
}
Store::~Store()
{
}

HRESULT Store::init()
{
	_allItem = new AllItemList;
	_allItem->init();
	init_defaultWindow();
	init_itemWindow();
	init_selfee();
	// ���⼭ ������ �ʱ�ȭ
	init_goods();
	return S_OK;
}
void Store::release()
{
	_window_img->release();
	_window_img = nullptr;
	_itemLine_img = nullptr;
	IMAGEMANAGER->deleteImage("ItemWindow");
	_allItem->release();
	_allItem = nullptr;
}
//============================================================
//==						������Ʈ							==
//============================================================
void Store::update()
{
	if (PLAYER->is_LbuttonDown() == true && _bBuying == false)
	{
		buy_item();
	}//if: �������� �ƴ϶�� ���⼭ ���� Ŭ���� �� ���� �������� �����, �κ��丮�� �ִ´�.
	else if (PLAYER->is_LbuttonUp() == true && _bBuying == true)
	{
		_bBuying = false;
	}
	// ����� ���
	if (KEYMANAGER->isToggleKey('1') == true)
	{
		_bDebug = true;
	}
	else if (KEYMANAGER->isToggleKey('1') == false)
	{
		_bDebug = false;
	}
}
void Store::render()
{
	if (_bShow_store == true)
	{
		draw_defaultWindow();
		draw_itemWindow();
		draw_selfee();
		// ���⼭ ������ ����
		draw_goods();
	}
}