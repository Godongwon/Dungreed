#pragma once
#include "base/gameNode.h"
class WeaponSwapSlot: public gameNode
{
private:
	// 1��, 2�� �̹���
	image * _weaponSwapFirst_img;
	image * _weaponSwapSecond_img;
	RECT _init_rect[2];					// �ʱ� ��ǥ
	RECT _current_rect[2];				// ���� ��ǥ		
	POINT _centerSwap_pt;				// 1�� �̹����� 2�� �̹����� �߰� ����
	// ���� �ٲٴ� bool ����
	bool _bSwapping = false;			// ���� ������?
protected:
	void move_weaponSwapSlot();
public:
	void swap_slot();
	bool get_bSwapping() { return _bSwapping; }
public:
	WeaponSwapSlot();
	~WeaponSwapSlot();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

