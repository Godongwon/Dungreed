#include "stdafx.h"
#include "WeaponSwapSlot.h"


void WeaponSwapSlot::move_weaponSwapSlot()
{

	// 왼쪽 아래 있던게 오른쪽 위로
	_current_rect[0].left++;
	_current_rect[0].right++;
	_current_rect[0].top--;
	_current_rect[0].bottom--;
	// 오른쪽 위에 있던게 왼쪽 아래로
	_current_rect[1].left--;
	_current_rect[1].right--;
	_current_rect[1].top++;
	_current_rect[1].bottom++;
	if (_current_rect[0].left >= _centerSwap_pt.x ||
		_current_rect[1].left <= _centerSwap_pt.x)
	{
		_bSwapping = false;
	}
	if (_current_rect[0].top <= _centerSwap_pt.y ||
		_current_rect[1].top >= _centerSwap_pt.y)
	{
		_bSwapping = false;
	}
	if (_bSwapping == false) 
	{ 
		swap(_weaponSwapFirst_img, _weaponSwapSecond_img);
		_current_rect[0] = _init_rect[0];
		_current_rect[1] = _init_rect[1];
	}
}

void WeaponSwapSlot::swap_slot()
{
	_bSwapping = true;
}

WeaponSwapSlot::WeaponSwapSlot()
{
}
WeaponSwapSlot::~WeaponSwapSlot()
{
}
HRESULT WeaponSwapSlot::init()
{
	_weaponSwapFirst_img = IMAGEMANAGER->addImage("SwapSlot_Front", "resource/image/UI/SwapSlot_1.bmp", 29 * 4, 21 * 4, true, RGB(255, 0, 255));
	_weaponSwapSecond_img = IMAGEMANAGER->addImage("SwapSlot_Back", "resource/image/UI/SwapSlot_2.bmp", 29 * 4, 21 * 4, true, RGB(255, 0, 255));
	// 무기스왑 슬롯의 초기 위치
	_init_rect[0] = RectMake(
		(int)(CAMERAMANAGER->getCameraCenter().x + WINSIZEX * 0.3 + 70),
		(int)(CAMERAMANAGER->getCameraCenter().y + WINSIZEY * 0.3 + 20),
		29 * 3, 21 * 3);
	_init_rect[1] = RectMake(
		_init_rect[0].left + 15, _init_rect[0].top - 15,
		29 * 3, 21 * 3);
	// 현재 무기 슬롯의 위치를 초기화
	_current_rect[0] = _init_rect[0];
	_current_rect[1] = _init_rect[1];
	// 두 슬롯 left 의 중간지점을 초기화한다.
	_centerSwap_pt.x = (LONG)((_init_rect[0].left +
		_init_rect[1].left) * 0.5);
	_centerSwap_pt.y = (LONG)((_init_rect[0].top +
		_init_rect[1].top) * 0.5);
	return E_NOTIMPL;
}

void WeaponSwapSlot::release()
{
	IMAGEMANAGER->deleteImage("SwapSlot_Front");
	IMAGEMANAGER->deleteImage("SwapSlot_Back");
	_weaponSwapFirst_img = nullptr;
	_weaponSwapSecond_img = nullptr;
}

void WeaponSwapSlot::update()
{
	if (_bSwapping == true)
	{
		move_weaponSwapSlot();
	}
}

void WeaponSwapSlot::render()
{
	// 무기 스왑 슬롯이다.
	_weaponSwapSecond_img->render(CAMERAMANAGER->getCameraDC(), _current_rect[1].left, _current_rect[1].top);
	_weaponSwapFirst_img->render(CAMERAMANAGER->getCameraDC(), _current_rect[0].left, _current_rect[0].top);
}
