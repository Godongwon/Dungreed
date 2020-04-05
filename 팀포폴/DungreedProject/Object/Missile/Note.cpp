#include "stdafx.h"
#include "Note.h"

Note::Note()
{
}

Note::~Note()
{
}

HRESULT Note::init()
{
	_size_missile_width = 26;					//미사일 렉트 부피
	_size_missile_height = 48;					//미사일 렉트 높이
	_speed_missile = 5.0f;
	_angle = NULL;
	_counterDelete = 200;
	_bCollide = false;
	_bDelete = false;

	//===================
	//=		이미지		=
	//===================
	_img_note_move = new image;
	_img_note_crash = new image;

	_img_note_move->init("resource/image/Missile/Note_move.bmp",
		13 * 4, 16 * 3, 4, 1, true, RGB(255, 0, 255));
	_img_note_move->set_frameSection(1, 0, 3, 5, 1);

	_img_note_crash->init("resource/image/Missile/Note_crash.bmp",
		20 * 4, 26 * 3, 6, 1, true, RGB(255, 0, 255));
	_img_note_crash->set_frameSection(1, 0, 3, 10, 1);

	return S_OK;
}

void Note::release()
{
	_img_note_move->release();
	_img_note_crash->release();
	SAFE_DELETE(_img_note_move);
	SAFE_DELETE(_img_note_crash);
}

void Note::update()
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
			_img_note_crash->setFrameX(0);
			_bCollide = true;
		}
	}

	if (_counterDelete != 0)
	{
		_counterDelete -= 1;
		if (_counterDelete >= 15)
		{
			_size_missile_rc.left += (LONG)(cosf(_angle) * _speed_missile);
			_size_missile_rc.right += (LONG)(cosf(_angle)*_speed_missile);
			_size_missile_rc.top += (LONG)(-sinf(_angle)*_speed_missile);
			_size_missile_rc.bottom += (LONG)(-sinf(_angle)*_speed_missile);
		}
	}

	if (_counterDelete == 15)
	{
		_img_note_crash->setFrameX(0);
	}
	if (_counterDelete == 0)
	{
		_bDelete = true;
	}

	_img_note_move->frameUpdate(true);
	_img_note_crash->frameUpdate(true);
}

void Note::render()
{
	if (_counterDelete >= 15)
	{
		_img_note_move->frameRender(getMemDC(), _size_missile_rc.left, _size_missile_rc.top);
	}
	if (_counterDelete <= 15)
	{
		_img_note_crash->frameRender(getMemDC(), _size_missile_rc.left, _size_missile_rc.top -5 );
	}
}
