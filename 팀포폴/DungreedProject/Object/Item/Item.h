#pragma once
#include"base/gameNode.h"
enum KIND_ITEM
{
	MAIN_HAND,
	SUB_HAND,
	ACC,
	FOOD,
	GAIN
};
enum RENDER_LOCATION
{
	LOCATION_STORE,
	LOCATION_INVENTORY,
	LOCATION_FIELD
};
class Item : public gameNode
{
protected:
	double _MULTIPLE_STORE = 3.5;
	double _MULTIPLE_INVEN = 1.5;
	double _MULTIPLE_FIELD = 3;
protected:
	KIND_ITEM _kinditem;		//����������
	string _itemName;			//�������̸�
	// �������� �׸� ������.
	RECT _item_rect;			//�������� ����ϱ� ���� ��Ʈ
	image* _item_img_store = nullptr;		//������ ������ �̹���
	image* _item_img_inven = nullptr;		//�κ��丮�� ������ �̹���
	image* _item_img_field = nullptr;		//�ʵ� ����� ������ �̹���
	// �������� ���� ������.
	int _itemAtk;	// �����۰��ݷ�
	int _itemDef;	// �����۹���
	int _itemPrice;	// ����
	int _itemHp;	// ü��
protected:
	// ������ �����Ѵ�.
	void set_multiples(double multiply);
	void release_imgs();
public:
	int get_itemPrice() { return _itemPrice; }
	image get_item_img_field() { return *_item_img_field; }
	KIND_ITEM get_kinditem() { return _kinditem; }
	void set_item_rect(RECT rect) { _item_rect = rect; }
public:
	Item();
	~Item();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(HDC hdc, RENDER_LOCATION location, POINT center);
	void frameRender(HDC hdc, POINT center);
	void frameRender(HDC hdc);
};

