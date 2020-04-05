#include "stdafx.h"
#include "BeliarSword.h"
BeliarSword::BeliarSword()
{
}
BeliarSword::~BeliarSword()
{
}
HRESULT BeliarSword::init()
{
	_size_missile_width = 60;					//미사일 렉트 부피
	_size_missile_height = 160;					//미사일 렉트 높이
	_speed_missile = 10.0f;
	_beliarSwordAngle = NULL;
	_delay = NULL;
	_counterDelete = 200;
	_bCollide = false;
	_bDelete = false;

	_img_beliarSword = new image;
	_img_beliarSword->init("resource/image/Missile/beliarSword.bmp",
		60, 160, 1, 1, true, RGB(255, 0, 255));
	_img_beliarSword->set_frameSection(1, 0, 1, 10, 1);

	return S_OK;
}
void BeliarSword::release()
{
	_img_beliarSword->release();
	SAFE_DELETE(_img_beliarSword);
}
void BeliarSword::update()
{
	RECT temp;
	RECT tempPlayer = PLAYER->get_playerRC();
	int playerhp = PLAYER->get_playerHP();
	if (_bCollide == false && _delay == 0)
	{
		if (IntersectRect(&temp, &_size_missile_rc, &tempPlayer))
		{
			playerhp -= 10;
			PLAYER->set_playerHP(playerhp);
			//_counterDelete = 15;
			_bCollide = true;
		}
	}
	if (_delay != 0)
	{
		_delay -= 1;
	}
	if (_delay == 1)
	{
		RECT tempPlayer = PLAYER->get_playerRC();
		_beliarSwordAngle = getAngle((float)((_size_missile_rc.left + _size_missile_rc.right ) /2),
			(float)((_size_missile_rc.top + _size_missile_rc.bottom) / 2),
			(float)((tempPlayer.right + tempPlayer.left) / 2), (float)((tempPlayer.top + tempPlayer.bottom) / 2));
	}
	if (_counterDelete != 0 && _delay == 0)
	{
		_counterDelete -= 1;
		if (_counterDelete >= 15)
		{
			_size_missile_rc.left += (LONG)(cosf(_beliarSwordAngle) * _speed_missile * 2);
			_size_missile_rc.right += (LONG)(cosf(_beliarSwordAngle)*_speed_missile * 2);
			_size_missile_rc.top += (LONG)(-sinf(_beliarSwordAngle)*_speed_missile * 2);
			_size_missile_rc.bottom += (LONG)(-sinf(_beliarSwordAngle)*_speed_missile * 2);
		}
	}
	if (_counterDelete == 15)
	{
		//_img_fireball_small_crash->setFrameX(0);
	}
	if (_counterDelete == 0)
	{
		_bDelete = true;
	}
}
void BeliarSword::render()
{
	_img_beliarSword->frameRender(getMemDC(), _size_missile_rc.left, _size_missile_rc.top);
	//Rectangle(getMemDC(), _size_missile_rc.left, _size_missile_rc.top, _size_missile_rc.right, _size_missile_rc.bottom);
}