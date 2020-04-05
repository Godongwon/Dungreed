#include "stdafx.h"
#include "Darkball.h"
Darkball::Darkball()
{
}
Darkball::~Darkball()
{
}
HRESULT Darkball::init()
{
	_size_missile_width = 35;					//미사일 렉트 부피
	_size_missile_height = 35;					//미사일 렉트 높이
	_speed_missile = 5.0f;
	_angle = NULL;
	_counterDelete = 150;
	_bCollide = false;
	_bDelete = false;

	_img_darkball = new image;
	_img_darkballCrash = new image;
	_img_darkball->init("resource/image/Missile/Darkball.bmp",
		70, 35, 2, 1, true, RGB(255, 0, 255));
	_img_darkball->set_frameSection(1, 0, 1, 10, 1);
	_img_darkballCrash->init("resource/image/Missile/DarkballCrash.bmp",
		224 * 2, 32 * 2, 7, 1, true, RGB(255, 0, 255));
	_img_darkballCrash->set_frameSection(1, 0, 6, 5, 1);
	

	return S_OK;
}
void Darkball::release()
{
	_img_darkball->release();
	_img_darkballCrash->release();
	SAFE_DELETE(_img_darkball);
	SAFE_DELETE(_img_darkballCrash);
}
void Darkball::update()
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
			_bCollide = true;
		}
	}
	if (_counterDelete != 0)
	{
		_counterDelete -= 1;
		if (_counterDelete >= 15)
		{
			_size_missile_rc.left += (LONG)(cosf(_angle) * _speed_missile * 2);
			_size_missile_rc.right += (LONG)(cosf(_angle)*_speed_missile * 2);
			_size_missile_rc.top += (LONG)(-sinf(_angle)*_speed_missile * 2);
			_size_missile_rc.bottom += (LONG)(-sinf(_angle)*_speed_missile * 2);
		}
	}
	if (_counterDelete % 5 == 0)
	{
		_img_darkball->setFrameX(0);
	}
	if (_counterDelete == 15)
	{
		_img_darkballCrash->setFrameX(0);
	}

	if (_counterDelete == 0)
	{
		_bDelete = true;
	}

	_img_darkball->frameUpdate(true);
	_img_darkballCrash->frameUpdate(true);
}
void Darkball::render()
{
	if (_counterDelete > 15)
	{
		_img_darkball->frameRender(getMemDC(), _size_missile_rc.left, _size_missile_rc.top);
	}
	if (_counterDelete <= 15)
	{
		_img_darkballCrash->frameRender(getMemDC(), _size_missile_rc.left, _size_missile_rc.top);
	}
}
