#include "stdafx.h"
#include "UI/UI.h"
// 마우스 커서를 불러온다.
// 마우스 커서: 싱글톤
#include "UI/always/MouseCursor.h"
//============================================================
//==				여기서 인벤토리를 열고, 닫는다.				==
//============================================================
void UI::toggle_inventory()
{
	if (_inventory->get_bShowInventory() == false)
	{
		_inventory->set_bShowInventory(true);
		MOUSECURSOR->change_cursor();
	}//if: 인벤토리를 연다
	else
	{
		_inventory->set_bShowInventory(false);
		MOUSECURSOR->change_cursor();
	}//else: 인벤토리를 닫는다.
}
void UI::toggle_weaponSwap()
{
	if (_weaponSwap->get_bSwapping() == false)
	{
		_weaponSwap->swap_slot();
	}//if: 스왑중이 아니라면 스왑을 한다.
}
void UI::toggle_weaponStore()
{
	if (_weaponStore->get_bShow_store() == false)
	{
		_weaponStore->set_bShow_store(true);
		_inventory->set_bShowInventory(true);
		MOUSECURSOR->change_cursor();
	}//if: 상점과 인벤을 연다
	else {}//else: else는 없다.
}
void UI::close_weaponStore()
{
	if (_bOpen_weaponStore == false)
	{
		_weaponStore->set_bShow_store(false);
	}
}
void UI::change_cursor(int bAim)
{
	MOUSECURSOR->set_cursor(bAim);
}
UI::UI()
{
}
UI::~UI()
{
}
HRESULT UI::init()
{
	_inventory = new Inventory;
	_inventory->init();
	_dashGauge = new dashGauge;
	_dashGauge->init();
	_hpBar = new HpBar();
	_hpBar->init();
	_weaponSwap = new WeaponSwapSlot;
	_weaponSwap->init();
	// 무기상점창
	_weaponStore = new Store;
	_weaponStore->init();
	// 마우스 커서
	MOUSECURSOR->init();
	return S_OK;
}

void UI::release()
{
	MOUSECURSOR->release();
	_weaponStore->release();
	_weaponStore = nullptr;
	_weaponSwap->release();
	_weaponSwap = nullptr;
	_hpBar->release();
	_hpBar = nullptr;
	_inventory->release();
	_inventory = nullptr;
	_dashGauge->release();
	_dashGauge = nullptr;
}

void UI::update()
{
	// 여기서 유저가 뭔가 눌렀을 때 이벤트가 발생한다.
	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		toggle_inventory();
	}//if: v키를 눌렀을 때 인벤토리 토글
	else if (KEYMANAGER->isOnceKeyDown('E') && _bOpen_weaponStore == true)
	{
		toggle_weaponStore();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		toggle_weaponSwap();
	}
	_inventory->update();
	_dashGauge->update();
	_hpBar->update();
	_weaponSwap->update();
	// 상점을 벗어나면 상점이 닫힌다.
	close_weaponStore();
	_weaponStore->update();
	MOUSECURSOR->update();
}

void UI::render()
{
	_inventory->render();
	_dashGauge->render();
	_hpBar->render();
	// 여기서 무기 상점창이 Open 상태면 렌더
	_weaponStore->render();
	_weaponSwap->render();
	MOUSECURSOR->render();
}
