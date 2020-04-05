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

	//�κ��丮�� �ִ� �������̴�.
	image * _inventoryEmptySlot[15];
	RECT _rcInventory_Empty_Slot[15];
	POINT _emptySlot_center[15];
	vItem _items;
	// ��带 ����� ��Ʈ��.
	RECT _gold_rect;

	// �������� �� �� �� ������.

	// �κ��丮�� ������� ���� �����ϴ� ������.
	bool _bShowInventory = false;
	// ����� ����.
	bool _bDebug = false;
protected:
	void init_gold_rect();	// ��巺Ʈ�� �ʱ�ȭ�Ѵ�.
	void draw_gold_rect();
	void draw_golds();		// ���⼭ ��带 ����Ѵ�.
	void update_items();
	void delete_itemsAll();
	// �������� ������ �Ǵ�.
	void sell_item();
	// �κ��丮�� �������� ����� ��, ����� ����ߴ��� �ε����� �����Ѵ�.
	void draw_items();
	// �ε����� �޾Ƽ� �� ������ ����Ѵ�.
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
 
