#include "stdafx.h"
#include "Arrow.h"

Arrow::Arrow()
{
}
Arrow::~Arrow()
{
}
HRESULT Arrow::init()
{
	_size_missile_width = 26;					//미사일 렉트 부피
	_size_missile_height = 10;					//미사일 렉트 높이
	_speed_missile = 5.0f;
	_angle = NULL;
	_counterDelete = 100;
	_bCollide = false;
	_bDelete = false;

	//===================
	//=		이미지		=
	//===================
	_img_left_arrow = new image;
	_img_right_arrow = new image;
	_img_arrow_crash = new image;

	_img_left_arrow->init("resource/image/Missile/arrow_left.bmp",
		13 * 2, 5 * 2, 1, 1, true, RGB(255, 0, 255));

	_img_right_arrow->init("resource/image/Missile/arrow_right.bmp",
		13 * 2, 5 * 2, 1, 1, true, RGB(255, 0, 255));

	_img_arrow_crash->init("resource/image/Missile/arrowCrash.bmp",
		240 * 2, 75 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_arrow_crash->set_frameSection(1, 0, 5, 3, 1);

	return S_OK;
}
void Arrow::release()
{
	_img_left_arrow->release();
	_img_right_arrow->release();
	_img_arrow_crash->release();
	SAFE_DELETE(_img_left_arrow);
	SAFE_DELETE(_img_right_arrow);
	SAFE_DELETE(_img_arrow_crash);
}
void Arrow::update()
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
			_img_arrow_crash->setFrameX(0);
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

	if (_counterDelete == 15)
	{
		_img_arrow_crash->setFrameX(0);
	}

	if (_counterDelete == 0)
	{
		_bDelete = true;
	}

	_img_arrow_crash->frameUpdate(true);
}
void Arrow::render()
{
	if (_counterDelete >= 15)
	{
		_img_left_arrow->frameRender(getMemDC(), _size_missile_rc.left, _size_missile_rc.top);
		_img_right_arrow->frameRender(getMemDC(), _size_missile_rc.left, _size_missile_rc.top);
	}
	if (_counterDelete <= 15)
	{
		_img_arrow_crash->frameRender(getMemDC(), _size_missile_rc.left - 20, _size_missile_rc.top - 90);
	}
}
