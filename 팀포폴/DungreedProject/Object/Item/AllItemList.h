#pragma once
#include "base/gameNode.h"
// 무기류
#include "Object/Item/weapon/Gladius.h"
#include "Object/Item/weapon/Jukdo.h"
#include "Object/Item/weapon/LongSword.h"
#include "Object/Item/weapon/ShortSword.h"
#include "Object/Item/weapon/Mace.h"
#include "Object/Item/weapon/WarHammer.h"
// 먹는거
#include "Object/Item/gain/Coin.h"
#include "Object/Item/gain/GoldBar.h"
#include "Object/Item/gain/Fairy.h"
// 싱글톤
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
	// strKey: 만들고 싶은 아이템의 키(이름)
	Item * make_item(string strKey);
	Item * make_item_toField(string strKey, POINT center);
public:
	// 아이템 리스트를 만들어서 렌더하는 함수
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