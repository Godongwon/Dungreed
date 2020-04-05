#include "stdafx.h"
#include "Store.h"
#include "Object/Unit/player/Player.h"
void Store::init_defaultWindow()
{
	_window_img = new image;
	_window_img->init("resource/image/weaponshop/전체창.bmp",
		(int)(117 * _MULTIPLE), (int)(WINSIZEY));
	_window_rect = RectMake(
		CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2,
		CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2,
		_window_img->getWidth(), _window_img->getHeight());;
	_window_center.x = (LONG)((_window_rect.left + _window_rect.right) * 0.5);
	_window_center.y = (LONG)((_window_rect.top + _window_rect.bottom) * 0.5);
	// 상점 주인 사진을 보여줄 윈도우를 초기화한다.
	_selfeeWindow_rect = RectMakeCenter(
		_window_center.x,
		(int)(_window_center.y - _window_img->getHeight() * 0.4) - 10,
		_window_img->getWidth() - 20, 75);
	// 아이템을 보여줄 윈도우를 초기화한다.
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
	int itemH = (int)(23 * _MULTIPLE);	// 23은 무기창.bmp 이미지의 height
	int blankH = 2;						// 위, 아래 여백
	int blankW = 4;						// 아이템RECT와 설명RECT의 사이 여백

	_itemLine_img = IMAGEMANAGER->addImage("ItemWindow",
		"resource/image/weaponshop/무기창.bmp", itemWindowW, itemH);

	POINT centerTemp;
	int current_top = _itemWindow_rect.top;
	for (int i = 0; i < 6; i++)
	{
		current_top += blankH;
		// 아이템 라인 1개의 이미지를 그리기 위한 RECT를 6개 초기화한다.
		_itemLine_rect[i] = RectMake(_itemWindow_rect.left, current_top,
			_itemLine_img->getWidth(), _itemLine_img->getHeight());
		// 아이템 이미지를 출력하기 위한 RECT를 6개 초기화한다.
		// _itemLine_rect의 중점을 잡고 위치를 잡는다.
		centerTemp.x = (LONG)(
			(_itemLine_rect[i].left + _itemLine_rect[i].right) * 0.5);
		centerTemp.y = (LONG)((_itemLine_rect[i].top +
			_itemLine_rect[i].bottom) * 0.5);
		centerTemp.x -= (LONG)(_itemLine_img->getWidth() * 0.5 -
			itemW * 0.5);
		_item_rect[i] = RectMakeCenter(centerTemp.x, centerTemp.y,
			itemW, itemH);
		_item_center[i] = PointMake(centerTemp.x, centerTemp.y);
		// 아이템 설명을 출력하기 위한 RECT를 6개 초기화한다.
		// _item_rect의 right, top을 기준으로 위치를 잡는다.
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
//==			상점에서 팔 아이템 그리는 부분					==
//============================================================
void Store::init_goods()
{
	auto itemKeys = _allItem->get_itemKeys();
	const int size = itemKeys.size();
	// 0 ~ size-1 을 배열에 넣어서 랜덤하게 섞는다.
	int * randomNum = new int[size];
	for (int i = 0; i < size; i++) { randomNum[i] = i; }
	for (int i = 0; i < 100; i++)
	{
		int sour = RND->getInt(size - 1);
		int dest = RND->getInt(size - 1);
		swap(randomNum[sour], randomNum[dest]);
	}
	// 랜덤한 아이템 6개를 초기화한다.
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
	// 상점에서 팔 아이템을 그린다.
	auto iter = _items.begin();
	for (;iter != _items.end(); iter++)
	{
		(*iter)->render(CAMERAMANAGER->getCameraDC(), LOCATION_STORE,
			_item_center[index]);
		index++;
	}
}
//============================================================
//==				상점에서 아이템 사는 부분					==
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
			else { break; }//else: 돈이 충분하지 않다.
		}// 1. 아이템을 클릭 했다면 돈이 충분한지 확인한다. 플레이어에게 주고, 지우고, break;
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
	// 여기서 아이템 초기화
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
//==						업데이트							==
//============================================================
void Store::update()
{
	if (PLAYER->is_LbuttonDown() == true && _bBuying == false)
	{
		buy_item();
	}//if: 구매중이 아니라면 여기서 무기 클릭할 때 마다 상점에서 지우고, 인벤토리에 넣는다.
	else if (PLAYER->is_LbuttonUp() == true && _bBuying == true)
	{
		_bBuying = false;
	}
	// 디버그 모드
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
		// 여기서 아이템 렌더
		draw_goods();
	}
}