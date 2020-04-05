#pragma once
#include "base/gameNode.h"
#include "Object/Item/AllItemList.h"
class Store: public gameNode
{
private:
	const double _MULTIPLE = 3.5;
	typedef vector<Item*> vItem;
private:
	// 게임의 모든 아이템을 불러올 수 있는 클래스다.
	AllItemList * _allItem;
	image* _window_img;
	RECT _window_rect;
	POINT _window_center;
	// 상점주인 사진을 출력할 윈도우다.
	RECT _selfeeWindow_rect;
	image*  _selfee_img;
	RECT _selfee_rect;
	// 아이템 그리는 변수
	image * _itemLine_img;
	RECT _itemWindow_rect;
	RECT _itemLine_rect[6];	// 라인 이미지를 띄울 RECT다.
	RECT _item_rect[6];		// 아이템을 그릴 RECT다.
	POINT _item_center[6];	// 아이템 렉트의 가운데다.
	RECT _desc_rect[6];		// 아이템 설명이 나오는 RECT다.
	// 상점에서 보여줄 아이템이다.
	vItem _items;
	bool _bBuying = false;
	// 상점을 출력할지 말지 결정하는 변수다.
	bool _bShow_store = false;
	bool _bDebug = false;
protected:
	// 상점을 그리기 위한 함수다.
	void init_defaultWindow();
	void draw_defaultWindow();
	void init_itemWindow();
	void draw_itemWindow();
	void init_selfee();
	void draw_selfee();
	void init_goods();
	void draw_goods();
	// 아이템을 사고, 팔기 위한 함수다.
	void buy_item();
	bool check_enoughMoney(Item * item);
public:
	bool get_bShow_store() { return _bShow_store; }
	void set_bShow_store(bool bShow) { _bShow_store = bShow; }
public:
	Store();
	~Store();
	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳5
	virtual void render(/*HDC hdc*/);//그리는곳
};

