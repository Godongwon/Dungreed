#include "stdafx.h"
#include "Fireball_small.h"
Fireball_small::Fireball_small()
{
}
Fireball_small::~Fireball_small()
{
}

HRESULT Fireball_small::init()
{
	_size_missile_width = 28;					//미사일 렉트 부피
	_size_missile_height = 28;					//미사일 렉트 높이
	_speed_missile = 3.0f;
	_angle = NULL;
	_counterDelete = 200;
	_bCollide = false;
	_bDelete = false;

	//===================
	//=		이미지		=
	//===================
	_img_fireball_small_move = new image;
	_img_fireball_small_crash = new image;

	_img_fireball_small_move->init("resource/image/Missile/RangeBallBullet_move.bmp",
		70 * 2, 14 * 2, 5, 1, true, RGB(255, 0, 255));
	_img_fireball_small_move->set_frameSection(1, 0, 4, 5, 1);

	_img_fireball_small_crash->init("resource/image/Missile/RangeBallBullet_crash.bmp",
		224 * 2, 32 * 2, 7, 1, true, RGB(255, 0, 255));
	_img_fireball_small_crash->set_frameSection(1, 0, 6, 5, 1);

	return S_OK;
}

void Fireball_small::release()
{
	_img_fireball_small_move->release();
	_img_fireball_small_crash->release();
	SAFE_DELETE(_img_fireball_small_move);
	SAFE_DELETE(_img_fireball_small_crash);
}

void Fireball_small::update()
{
	RECT temp;
	RECT tempPlayer = PLAYER->get_playerRC();
	int playerhp = PLAYER->get_playerHP();
	if (_bCollide == false)
	{
		if (IntersectRect(&temp, &_size_missile_rc, &tempPlayer))
		{
			playerhp -= 10;
			PLAYER->set_playerHP(playerhp);
			_counterDelete = 15;
			_img_fireball_small_crash->setFrameX(0);
			_bCollide = true;
		}
	}

	if (_counterDelete != 0)
	{
		_counterDelete -= 1;
		if (_counterDelete >=15)
		{			
			_size_missile_rc.left += (LONG)(cosf(_angle) * _speed_missile * 2);
			_size_missile_rc.right += (LONG)(cosf(_angle)*_speed_missile * 2);
			_size_missile_rc.top += (LONG)(-sinf(_angle)*_speed_missile * 2);
			_size_missile_rc.bottom += (LONG)(-sinf(_angle)*_speed_missile * 2);
			
		}
	}
	if (_counterDelete == 15)
	{
		_img_fireball_small_crash->setFrameX(0);
	}
	if (_counterDelete == 0)
	{
		_bDelete = true;
	}

	_img_fireball_small_move->frameUpdate(true);
	_img_fireball_small_crash->frameUpdate(true);
}

void Fireball_small::render()
{
	if (_counterDelete >= 15)
	{
		_img_fireball_small_move->frameRender(getMemDC(), _size_missile_rc.left, _size_missile_rc.top);
	}
	if (_counterDelete <= 15)
	{
		_img_fireball_small_crash->frameRender(getMemDC(), _size_missile_rc.left - 16, _size_missile_rc.top - 16);
	}
}
