#pragma once
#include "base/gameNode.h"
#include "Object/Item/AllItemList.h"
class Store: public gameNode
{
private:
	const double _MULTIPLE = 3.5;
	typedef vector<Item*> vItem;
private:
	// ������ ��� �������� �ҷ��� �� �ִ� Ŭ������.
	AllItemList * _allItem;
	image* _window_img;
	RECT _window_rect;
	POINT _window_center;
	// �������� ������ ����� �������.
	RECT _selfeeWindow_rect;
	image*  _selfee_img;
	RECT _selfee_rect;
	// ������ �׸��� ����
	image * _itemLine_img;
	RECT _itemWindow_rect;
	RECT _itemLine_rect[6];	// ���� �̹����� ��� RECT��.
	RECT _item_rect[6];		// �������� �׸� RECT��.
	POINT _item_center[6];	// ������ ��Ʈ�� �����.
	RECT _desc_rect[6];		// ������ ������ ������ RECT��.
	// �������� ������ �������̴�.
	vItem _items;
	bool _bBuying = false;
	// ������ ������� ���� �����ϴ� ������.
	bool _bShow_store = false;
	bool _bDebug = false;
protected:
	// ������ �׸��� ���� �Լ���.
	void init_defaultWindow();
	void draw_defaultWindow();
	void init_itemWindow();
	void draw_itemWindow();
	void init_selfee();
	void draw_selfee();
	void init_goods();
	void draw_goods();
	// �������� ���, �ȱ� ���� �Լ���.
	void buy_item();
	bool check_enoughMoney(Item * item);
public:
	bool get_bShow_store() { return _bShow_store; }
	void set_bShow_store(bool bShow) { _bShow_store = bShow; }
public:
	Store();
	~Store();
	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�5
	virtual void render(/*HDC hdc*/);//�׸��°�
};

