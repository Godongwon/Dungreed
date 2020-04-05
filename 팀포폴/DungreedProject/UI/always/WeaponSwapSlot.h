#pragma once
#include "base/gameNode.h"
class WeaponSwapSlot: public gameNode
{
private:
	// 1번, 2번 이미지
	image * _weaponSwapFirst_img;
	image * _weaponSwapSecond_img;
	RECT _init_rect[2];					// 초기 좌표
	RECT _current_rect[2];				// 현재 좌표		
	POINT _centerSwap_pt;				// 1번 이미지와 2번 이미지의 중간 지점
	// 무기 바꾸는 bool 변수
	bool _bSwapping = false;			// 스왑 중인지?
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

