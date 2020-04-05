#pragma once
#include "base/gameNode.h"
#include "Object/Item/Item.h"
class Inventory : public gameNode
{
private:
	typedef vector<Item*> vItem;
private:
	image * _inventory;
	RECT _rcInventory;
	
	image* _changeButton;
	RECT _rcChangeButton;

	image * _inventoryWeapon[2];
	RECT _rcinventoryWeapon[2];

	image * _inventoryAmmor[2];
	RECT _rcinventoryAmmor[2];

	image * _inventorySlot[4];
	RECT _rcInventory_Slot[4];

	image * _inventoryExit;
	RECT _rcinventoryExit;

	//인벤토리에 있는 아이템이다.
	image * _inventoryEmptySlot[15];
	RECT _rcInventory_Empty_Slot[15];
	POINT _emptySlot_center[15];
	vItem _items;
	// 골드를 출력할 렉트다.
	RECT _gold_rect;

	// 아이템을 팔 때 쓸 변수다.

	// 인벤토리를 출력할지 말지 결정하는 변수다.
	bool _bShowInventory = false;
	// 디버그 모드다.
	bool _bDebug = false;
protected:
	void init_gold_rect();	// 골드렉트를 초기화한다.
	void draw_gold_rect();
	void draw_golds();		// 여기서 골드를 출력한다.
	void update_items();
	void delete_itemsAll();
	// 아이템을 상점에 판다.
	void sell_item();
	// 인벤토리에 아이템을 출력한 뒤, 몇개까지 출력했는지 인덱스를 리턴한다.
	void draw_items();
	// 인덱스를 받아서 빈 슬롯을 출력한다.
	void draw_emptySlots();
public:
	void set_bShowInventory(bool bShowInventory) { _bShowInventory = bShowInventory; }
	bool get_bShowInventory() { return _bShowInventory; }
public:
	Inventory();
	~Inventory();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
 
