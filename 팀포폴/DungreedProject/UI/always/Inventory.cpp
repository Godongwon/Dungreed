#include "stdafx.h"
#include "UI/always/Inventory.h"
#include "Object/Unit/player/Player.h"
#include "UI/UI.h"
void Inventory::init_gold_rect()
{
	POINT center;
	center.x = (LONG)((_rcInventory.left + _rcInventory.right) * 0.515);
	center.y = (LONG)((_rcInventory.bottom + _rcInventory.top) * 0.894);
	
	_gold_rect = RectMakeCenter(center.x, center.y, 20, 
		(int)(_inventoryEmptySlot[0]->getFrameHeight() * 0.7));
}
void Inventory::draw_gold_rect()
{
	ColorRect(CAMERAMANAGER->getCameraDC(), _gold_rect, RGB(254, 254, 254));
}
void Inventory::draw_golds()
{
	char str[128];
	wsprintf(str, "%d", PLAYER->get_golds());
	FontTextOut(CAMERAMANAGER->getCameraDC(),
		_gold_rect.left, _gold_rect.top, str, 
		25, "맑은 고딕", RGB(254, 254, 254));
}
//============================================================
//==				인벤토리가 아이템을 받는 부분				==
//============================================================
void Inventory::update_items()
{
	_items = PLAYER->get_itemList();
}
void Inventory::delete_itemsAll()
{
	auto iter = _items.begin();
	for (;iter != _items.end();)
	{
		iter = _items.erase(iter);
	}
	swap(_items, vItem());
}

void Inventory::sell_item()
{
	auto iter = _items.begin();
	int index = 0;
	for (;iter != _items.end();)
	{
		if (PtInRect(&_rcInventory_Empty_Slot[index], m_ptMouse))
		{
			iter = _items.erase(iter);
		}
		else { iter++; }
		index++;
	}
}

void Inventory::draw_items()
{
	auto iter = _items.begin();
	int size = _items.size();
	int index = 0;
	for (;iter != _items.end(); iter++)
	{
		(*iter)->render(CAMERAMANAGER->getCameraDC(), LOCATION_INVENTORY,
			_emptySlot_center[index]);
		index++;
	}
}
void Inventory::draw_emptySlots()
{
	for (int i = 0; i < 15; i++)
	{
		_inventoryEmptySlot[i]->frameRender(CAMERAMANAGER->getCameraDC(), 
			_rcInventory_Empty_Slot[i].left, _rcInventory_Empty_Slot[i].top);
	}
}

Inventory::Inventory()
{
}
Inventory::~Inventory()
{
}

HRESULT Inventory::init()
{
	// 인벤토리 몸통
	_inventory = new image;
	// 인벤토리 출력위치
	_inventory = IMAGEMANAGER->addImage("Inventory",
		"resource/image/UI/inventory/Inventory.bmp",
		0, 0, 123 * 2, 188 * 2, true, RGB(255, 0, 255));
	_rcInventory = RectMakeCenter(
		CAMERAMANAGER->getCameraCenter().x + (WINSIZEX / 2 - _inventory->getWidth() / 2),
		CAMERAMANAGER->getCameraCenter().y - 100,
		_inventory->getWidth(), _inventory->getHeight());

	int focous_rcInventoryY = _rcInventory.bottom -
		(_inventory->getHeight()) / 2;

	IMAGEMANAGER->addFrameImage("Accessory_slot",
		"resource/image/UI/inventory/Accessory_slot.bmp", WINSIZEX - 50, WINSIZEY - 200,
		(int)(38 * 2), (int)(19 * 2), 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Inventory_empty_slot",
		"resource/image/UI/inventory/Inventory_empty_slot.bmp",
		(int)(38 * 2), (int)(19 * 2), 2, 1);

	_changeButton = new image;
	_changeButton = IMAGEMANAGER->addImage("changeButton",
		"resource/image/UI/inventory/changeButton.bmp", WINSIZEX - 150, WINSIZEY - 200,
		8 * 3, 9 * 3, true, RGB(255, 0, 255));
	_rcChangeButton = RectMake(_rcInventory.left + 110, _rcInventory.top + 50
		, _changeButton->getWidth(), _changeButton->getHeight());


	//================================ 악세사리 슬롯 =====================================
	for (int i = 0; i < 4; i++)
	{
		_inventorySlot[i] = new image;
		_inventorySlot[i] = IMAGEMANAGER->findImage("Accessory_slot");
		if (i == 0)
		{
			_rcInventory_Slot[i] = RectMake(_rcInventory.left + 25, focous_rcInventoryY - 55, _inventorySlot[i]->getFrameWidth(), _inventorySlot[i]->getFrameHeight());
		}
		else
		{
			_rcInventory_Slot[i] = RectMake((_rcInventory_Slot[i - 1].left + (_inventorySlot[i]->getFrameWidth()) + 18), _rcInventory_Slot[i - 1].top, _inventorySlot[i]->getFrameWidth(), _inventorySlot[i]->getFrameHeight());
		}
	}

	//========================== 인벤토리 여분 아이템 슬롯 =======================================
	for (int i = 0; i < 15; i++)
	{
		_inventoryEmptySlot[i] = new image;
		_inventoryEmptySlot[i] = IMAGEMANAGER->findImage("Inventory_empty_slot");
		if (i == 0)
		{
			_rcInventory_Empty_Slot[i] = RectMake(_rcInventory.left + 21, focous_rcInventoryY - 3, _inventoryEmptySlot[i]->getFrameWidth(), _inventoryEmptySlot[i]->getFrameHeight());
		}
		else
		{
			if (!(i % 5 == 0))
			{
				_rcInventory_Empty_Slot[i] = RectMake(_rcInventory_Empty_Slot[i - 1].right + 5, _rcInventory_Empty_Slot[i - 1].top, _inventoryEmptySlot[i]->getFrameWidth(), _inventoryEmptySlot[i]->getFrameHeight());
			}
			else
			{
				_rcInventory_Empty_Slot[i] = RectMake(_rcInventory_Empty_Slot[i - 5].left, _rcInventory_Empty_Slot[i - 5].bottom + 5, _inventoryEmptySlot[i]->getFrameWidth(), _inventoryEmptySlot[i]->getFrameHeight());
			}
		}
		// 여기서 센터를 잡아준다.
		_emptySlot_center[i].x = 
			(LONG)((_rcInventory_Empty_Slot[i].left + 
				_rcInventory_Empty_Slot[i].right) * 0.5);
		_emptySlot_center[i].y =
			(LONG)((_rcInventory_Empty_Slot[i].top +
				_rcInventory_Empty_Slot[i].bottom) * 0.5);
	}
	// 인벤토리 EXIT 버튼
	_inventoryExit = IMAGEMANAGER->addFrameImage("InventoryExitButton",
		"resource/image/UI/inventory/InventoryExitButton.bmp", (int)(44 * 1.3), (int)(19 * 1.3),
		2, 1, true, RGB(255, 0, 255));
	_rcinventoryExit = RectMake(
		_rcInventory.left + 5,
		_rcInventory.top + 5,
		_inventoryExit->getFrameWidth(),
		_inventoryExit->getFrameHeight());
	for (int i = 0; i < 2; i++)
	{
		_inventoryWeapon[i] = new image;
		_inventoryAmmor[i] = new image;
		_inventoryWeapon[0] = IMAGEMANAGER->addFrameImage("weaponSlotIcon", "resource/image/UI/inventory/weaponSlotIcon.bmp", (int)(120 / 1.5), (int)(61 / 1.5), 2, 1, true, RGB(255, 0, 255));
		_inventoryAmmor[0] = IMAGEMANAGER->addFrameImage("ammorSlotIcon", "resource/image/UI/inventory/ammorSlotIcon.bmp", (int)(122 / 1.5), (int)(61 / 1.5), 2, 1, true, RGB(255, 0, 255));
		_inventoryWeapon[1] = IMAGEMANAGER->addFrameImage("weaponSlotIcon_2", "resource/image/UI/inventory/weaponSlotIcon.bmp", (int)(120 / 1.5), (int)(61 / 1.5), 2, 1, true, RGB(255, 0, 255));
		_inventoryAmmor[1] = IMAGEMANAGER->addFrameImage("ammorSlotIcon_2", "resource/image/UI/inventory/ammorSlotIcon.bmp", (int)(122 / 1.5), (int)(61 / 1.5), 2, 1, true, RGB(255, 0, 255));
		_rcinventoryWeapon[0] = RectMake(_rcInventory.left + 20, _rcChangeButton.bottom - 5, 120, 61);
		_rcinventoryAmmor[0] = RectMake(_rcInventory.left + 65, _rcChangeButton.bottom - 5, 120, 61);
		_rcinventoryWeapon[1] = RectMake(_rcInventory.left + 140, _rcChangeButton.bottom - 5, 120, 61);
		_rcinventoryAmmor[1] = RectMake(_rcInventory.left + 185, _rcChangeButton.bottom - 5, 120, 61);
	}//loop: 무기, 방패 슬롯 초기화
	// 골드를 출력할 위치 잡아준다.
	init_gold_rect();
	return S_OK;
}
void Inventory::release()
{
	IMAGEMANAGER->deleteImage("Inventory_empty_slot");
	for (int i = 0; i < 15; i++)
	{
		_inventoryEmptySlot[i] = nullptr;
	}
	IMAGEMANAGER->deleteImage("InventoryExitButton");
	_inventoryExit = nullptr;
	IMAGEMANAGER->deleteImage("Accessory_slot");
	_inventorySlot[0] = nullptr;
	_inventorySlot[1] = nullptr;
	_inventorySlot[2] = nullptr;
	_inventorySlot[3] = nullptr;
	IMAGEMANAGER->deleteImage("ammorSlotIcon");
	IMAGEMANAGER->deleteImage("ammorSlotIcon_2");
	_inventoryAmmor[0] = nullptr;
	_inventoryAmmor[1] = nullptr;
	IMAGEMANAGER->deleteImage("weaponSlotIcon");
	IMAGEMANAGER->deleteImage("weaponSlotIcon_2");
	_inventoryWeapon[0] = nullptr;
	_inventoryWeapon[1] = nullptr;
	IMAGEMANAGER->deleteImage("changeButton");
	_changeButton = nullptr;
	IMAGEMANAGER->deleteImage("Inventory");
	_inventory = nullptr;
	delete_itemsAll();
}
void Inventory::update()
{
	update_items();
	// 여기서 인벤토리의 아이템을 뺀다.
	if (INGAME_UI->get_bOpen_weaponStore() && PLAYER->is_LbuttonDown())
	{
		// 인벤토리가 가지고 있는거 갯수
		sell_item();
	}
	// 디버그 모드다.
	if (KEYMANAGER->isToggleKey('1') == true) { _bDebug = true; }
	else if (KEYMANAGER->isToggleKey('1') == false) { _bDebug = false; }
}
void Inventory::render()
{
	//========================================= 인벤토리 창=====================================================
	if (_bShowInventory == true)
	{
		IMAGEMANAGER->render("Inventory", CAMERAMANAGER->getCameraDC(), _rcInventory.left, _rcInventory.top);
		//Rectangle(getMemDC(), _rcInventory.left, _rcInventory.top, _rcInventory.right, _rcInventory.bottom);

		for (int i = 0; i < 4; i++)
		{
			IMAGEMANAGER->frameRender("Accessory_slot", CAMERAMANAGER->getCameraDC(), _rcInventory_Slot[i].left, _rcInventory_Slot[i].top, _inventorySlot[i]->getFrameX(), _inventorySlot[i]->getFrameY());
			//Rectangle(getMemDC(), _rcInventory_Slot[i].left, _rcInventory_Slot[i].top, _rcInventory_Slot[i].right, _rcInventory_Slot[i].bottom);
		}
		// 15 개의 아이템 슬롯을 출력하는 부분이다.
		// 슬롯을 먼저, 아이템을 나중에 출력한다.
		draw_emptySlots();
		draw_items();
		// 체인지 버튼, 무기, 방패 슬롯이다.
		IMAGEMANAGER->render("changeButton", CAMERAMANAGER->getCameraDC(), _rcChangeButton.left, _rcChangeButton.top);
		IMAGEMANAGER->frameRender("weaponSlotIcon", CAMERAMANAGER->getCameraDC(), _rcinventoryWeapon[0].left, _rcinventoryWeapon[0].top, _inventoryWeapon[0]->getFrameX(), _inventoryWeapon[0]->getFrameY());
		IMAGEMANAGER->frameRender("weaponSlotIcon_2", CAMERAMANAGER->getCameraDC(), _rcinventoryWeapon[1].left, _rcinventoryWeapon[1].top, _inventoryWeapon[1]->getFrameX(), _inventoryWeapon[1]->getFrameY());
		//ammorSlotIcon
		IMAGEMANAGER->frameRender("ammorSlotIcon", CAMERAMANAGER->getCameraDC(), _rcinventoryAmmor[0].left, _rcinventoryAmmor[0].top, _inventoryAmmor[0]->getFrameX(), _inventoryAmmor[0]->getFrameY());
		IMAGEMANAGER->frameRender("ammorSlotIcon_2", CAMERAMANAGER->getCameraDC(), _rcinventoryAmmor[1].left, _rcinventoryAmmor[1].top, _inventoryAmmor[1]->getFrameX(), _inventoryAmmor[1]->getFrameY());
		IMAGEMANAGER->frameRender("InventoryExitButton", CAMERAMANAGER->getCameraDC(), _rcinventoryExit.left, _rcinventoryExit.top, _inventoryExit->getFrameX(), _inventoryExit->getFrameY());
		// 골드를 출력한다.
		draw_golds();
	}
	if (_bDebug == true)
	{
		draw_gold_rect();
	}
}
