#pragma once
#include "UI/always/Inventory.h"
#include "UI/always/dashGauge.h"
#include "UI/always/HpBar.h"
#include "UI/always/WeaponSwapSlot.h"
#include "UI/Store.h"
// UI: ΩÃ±€≈Ê
#include "base/singletonBase.h"

class UI : public gameNode, public singletonBase<UI>
{
private:
	Inventory * _inventory;
	dashGauge * _dashGauge;
	HpBar * _hpBar;
	WeaponSwapSlot * _weaponSwap;
	Store * _weaponStore;
private:
	bool _bOpen_weaponStore;
protected:
	void toggle_inventory();
	void toggle_weaponSwap();
	void toggle_weaponStore();
	void close_weaponStore();
public:
	void set_bOpen_weaponStore(bool bOpen) { _bOpen_weaponStore = bOpen; }
	bool get_bOpen_weaponStore() { return _bOpen_weaponStore; }
	void change_cursor(int bAim);
public:
	UI();
	~UI();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
 
#define INGAME_UI	UI::getSingleton()