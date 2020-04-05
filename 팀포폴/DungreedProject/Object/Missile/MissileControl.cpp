#include "stdafx.h"
#include "MissileControl.h"

void MissileControl::push_missile(Missile * missile)
{
	_missiles.push_back(missile);
}

void MissileControl::delete_missiles()
{
	auto iter = _missiles.begin();
	for (; iter != _missiles.end();)
	{
		if ((*iter)->is_deleteMissile() == true)
		{
			iter = _missiles.erase(iter);
		}
		else { iter++; }
	}
}
void MissileControl::update_missiles()
{
	_missilesIter = _missiles.begin();
	for (; _missilesIter != _missiles.end(); _missilesIter++)
	{
		(*_missilesIter)->update();
	}
}
//============================================================
//==					R E N D E R							==
//============================================================
void MissileControl::draw_missiles()
{
	_missilesIter = _missiles.begin();
	for (; _missilesIter != _missiles.end(); _missilesIter++)
	{
		(*_missilesIter)->render();
		(*_missilesIter)->show_missile_rc();
	}
}
void MissileControl::release_missiles()
{
	_missilesIter = _missiles.begin();
	for (; _missilesIter != _missiles.end();)
	{
		(*_missilesIter)->release();
		_missilesIter = _missiles.erase(_missilesIter);
	}
	swap(_missiles, vMissile());
}
//============================================================
//==						T E S T							==
//============================================================

//============================================================
//==				D E F A U L T   B A S E					==
//============================================================
MissileControl::MissileControl()
{
}
MissileControl::~MissileControl()
{
}
HRESULT MissileControl::init()
{
	return S_OK;
}
void MissileControl::release()
{
	release_missiles();
}
void MissileControl::update()
{
	delete_missiles();
	update_missiles();
}
void MissileControl::render()
{
	draw_missiles();
}

