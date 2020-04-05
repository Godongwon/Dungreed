#include "stdafx.h"
#include "UI/UI.h"
// ���콺 Ŀ���� �ҷ��´�.
// ���콺 Ŀ��: �̱���
#include "UI/always/MouseCursor.h"
//============================================================
//==				���⼭ �κ��丮�� ����, �ݴ´�.				==
//============================================================
void UI::toggle_inventory()
{
	if (_inventory->get_bShowInventory() == false)
	{
		_inventory->set_bShowInventory(true);
		MOUSECURSOR->change_cursor();
	}//if: �κ��丮�� ����
	else
	{
		_inventory->set_bShowInventory(false);
		MOUSECURSOR->change_cursor();
	}//else: �κ��丮�� �ݴ´�.
}
void UI::toggle_weaponSwap()
{
	if (_weaponSwap->get_bSwapping() == false)
	{
		_weaponSwap->swap_slot();
	}//if: �������� �ƴ϶�� ������ �Ѵ�.
}
void UI::toggle_weaponStore()
{
	if (_weaponStore->get_bShow_store() == false)
	{
		_weaponStore->set_bShow_store(true);
		_inventory->set_bShowInventory(true);
		MOUSECURSOR->change_cursor();
	}//if: ������ �κ��� ����
	else {}//else: else�� ����.
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
	// �������â
	_weaponStore = new Store;
	_weaponStore->init();
	// ���콺 Ŀ��
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
	// ���⼭ ������ ���� ������ �� �̺�Ʈ�� �߻��Ѵ�.
	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		toggle_inventory();
	}//if: vŰ�� ������ �� �κ��丮 ���
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
	// ������ ����� ������ ������.
	close_weaponStore();
	_weaponStore->update();
	MOUSECURSOR->update();
}

void UI::render()
{
	_inventory->render();
	_dashGauge->render();
	_hpBar->render();
	// ���⼭ ���� ����â�� Open ���¸� ����
	_weaponStore->render();
	_weaponSwap->render();
	MOUSECURSOR->render();
}
