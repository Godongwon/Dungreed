#include "stdafx.h"
#include "Fireball_big.h"
Fireball_big::Fireball_big()
{
}
Fireball_big::~Fireball_big()
{
}

HRESULT Fireball_big::init()
{
	_size_missile_width = 40;					//미사일 렉트 부피
	_size_missile_height = 40;					//미사일 렉트 높이
	_speed_missile = 3.0f;
	_angle = NULL;
	_counterDelete = 200;
	_bDelete = false;

	//===================
	//=		이미지		=
	//===================
	//_img_fireball_big = new image;
	return S_OK;
}

void Fireball_big::release()
{
	//_img_fireball_big->release();
	//SAFE_DELETE(_img_fireball_small);
}

void Fireball_big::update()
{
	if (_counterDelete != 0)
	{
		_counterDelete -= 1;
		_size_missile_rc.left += (LONG)(cosf(_angle) * _speed_missile * 2);
		_size_missile_rc.right += (LONG)(cosf(_angle)*_speed_missile * 2);
		_size_missile_rc.top += (LONG)(-sinf(_angle)*_speed_missile * 2);
		_size_missile_rc.bottom += (LONG)(-sinf(_angle)*_speed_missile * 2);
	}
	if (_counterDelete == 0)
	{
		_bDelete = true;
	}
}

void Fireball_big::render()
{
	//_img_fireball_big->frameRender(getMemDC(), _size_missile_rc.left, _size_missile_rc.top);
}
