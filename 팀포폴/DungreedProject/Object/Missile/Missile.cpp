#include "stdafx.h"
#include "Missile.h"


void Missile::init_missile_size_rc()
{
	_size_missile_rc = RectMakeCenter(_focus.x, _focus.y,_size_missile_width, _size_missile_height);
}
void Missile::init_missileInfo(POINT focus, float angle)
{
	_focus = focus;
	_angle = angle;
	init_missile_size_rc();
}

void Missile::init_BeliarSwordInfo(POINT focus, int delay)
{
	_focus = focus;
	_delay = delay;
	init_missile_size_rc();
}

//================================================
//##				debug : F1					##
//================================================
void Missile::show_missile_rc()
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _size_missile_rc.left, _size_missile_rc.top, _size_missile_rc.right, _size_missile_rc.bottom);
	}
}
//============================================================
//==				D E F A U L T   B A S E					==
//============================================================
Missile::Missile()
{
}
Missile::~Missile()
{
}
HRESULT Missile::init()
{
	return S_OK;
}
void Missile::release()
{
}
void Missile::update()
{
}
void Missile::render()
{

}