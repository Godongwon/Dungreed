#pragma once
#include "base/gameNode.h"
// �����
#include "Object/Item/weapon/Gladius.h"
#include "Object/Item/weapon/Jukdo.h"
#include "Object/Item/weapon/LongSword.h"
#include "Object/Item/weapon/ShortSword.h"
#include "Object/Item/weapon/Mace.h"
#include "Object/Item/weapon/WarHammer.h"
// �Դ°�
#include "Object/Item/gain/Coin.h"
#include "Object/Item/gain/GoldBar.h"
#include "Object/Item/gain/Fairy.h"
// �̱���
#include "base/singletonBase.h"
class AllItemList : public gameNode, public singletonBase<AllItemList>
{
private:
	typedef vector<string> vItemKey;
	typedef vector<Item *> vItem;
private:
	vItemKey _itemKeys;
	vItem _itemList;
protected:
	void init_weaponKeysAll();
	void delete_weaponKeysAll();
public:
	// strKey: ����� ���� �������� Ű(�̸�)
	Item * make_item(string strKey);
	Item * make_item_toField(string strKey, POINT center);
public:
	// ������ ����Ʈ�� ���� �����ϴ� �Լ�
	void push_itemList(Item * item);
	void delete_itemListAll();
	void update_itemList();
	void draw_itemList();
public:
	vItemKey get_itemKeys() { return _itemKeys; }
public:
	AllItemList();
	~AllItemList();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

#define ITEMS	AllItemList::getSingleton()