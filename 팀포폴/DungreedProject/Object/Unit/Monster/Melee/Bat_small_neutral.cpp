#include "stdafx.h"
#include "Bat_small_neutral.h"
Bat_small_neutral::Bat_small_neutral()
{
}
Bat_small_neutral::~Bat_small_neutral()
{
}
HRESULT Bat_small_neutral::init()
{
	//===================
	//=		렉트 크기	=
	//===================
	_size_monster_width = 32;
	_size_monster_height = 32;
	//===================
	//=		능력치		=
	//===================
	_hp = 20;
	_speed_move = 2.0f;
	//===================
	//=		A I			=
	//===================

	//===================
	//=		EFFECT		=
	//===================
	_hpTemp = 20;
	_monsterHpBar_W = 20;
	_bDead_monster = false;
	_counter_DeadEffect = 30;
	_counter_damageEffect = 15;
	//===================
	//=		이미지		=
	//===================
	_img_left_idle = new image;
	_img_right_idle = new image;
	_img_deadEffect = new image;
	_img_lifeBack = new image;
	_img_lifeBar = new image;
	_img_damageEffect = new image;
	//Idle
	_img_left_idle->init("resource/image/Monster/bat_noAtk_idle_left.bmp",
		192 * 2, 32 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_left_idle->set_frameSection(1, 5, 0, 5, 1);
	_img_right_idle->init("resource/image/Monster/bat_noAtk_idle_right.bmp",
		192 * 2, 32 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_right_idle->set_frameSection(1, 0, 5, 5, 1);
	//Dead
	_img_deadEffect->init("resource/image/Monster/monster_dead.bmp",
		704 * 2, 64 * 2, 11, 1, true, RGB(255, 0, 255));
	_img_deadEffect->set_frameSection(1, 0, 10, 5, 1);
	//LifeBack
	_img_lifeBack->init("resource/image/Monster/monsterLifeBack.bmp",
		20 * 2, 5 * 2, 1, 1, true, RGB(255, 0, 255));
	_img_lifeBar->init("resource/image/Monster/monsterLifeBar.bmp",
		20 * 2, 5 * 2, 1, 1, true, RGB(255, 0, 255));
	//Damage
	_img_damageEffect->init("resource/image/Monster/damageEffect.bmp",
		126 * 2, 31 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_damageEffect->set_frameSection(1, 0, 5, 5, 1);
	_bDebug = false;
	return S_OK;
}
void Bat_small_neutral::release()
{
	_img_left_idle->release();
	_img_right_idle->release();
	_img_deadEffect->release();
	_img_damageEffect->release();
	_img_lifeBack->release();
	_img_lifeBar->release();
	SAFE_DELETE(_img_left_idle);
	SAFE_DELETE(_img_right_idle);
	SAFE_DELETE(_img_deadEffect);
	SAFE_DELETE(_img_damageEffect);
	SAFE_DELETE(_img_lifeBack);
	SAFE_DELETE(_img_lifeBar);
}
void Bat_small_neutral::update()
{
	if (_counter_DeadEffect == 30)
	{
		idle_airUnit();
		damage_effect();
	}
	dead_monster();
	dead_effect();
	//image Update
	_img_left_idle->frameUpdate(true, false);
	_img_right_idle->frameUpdate(true);
	_img_deadEffect->frameUpdate(true);
	_img_damageEffect->frameUpdate(true);
}
void Bat_small_neutral::render()
{
	if (_counter_DeadEffect == 30)
	{
		//Move
		if (_bShow_left == true && _cooldown_recharge == _speed_recharge)
		{
			_img_left_idle->frameRender(getMemDC(), _size_monster_rc.left - 16, _size_monster_rc.top - 16);
		}
		if (_bShow_left == false && _cooldown_recharge == _speed_recharge)
		{
			_img_right_idle->frameRender(getMemDC(), _size_monster_rc.left - 16, _size_monster_rc.top - 16);
		}
		//LifeBar
		_img_lifeBack->render(getMemDC(), _size_monster_rc.left + 5, _size_monster_rc.top + _size_monster_height + 5,
			(int)(_monsterHpBar_W), (int)(10));
		_img_lifeBar->render(getMemDC(),
			_size_monster_rc.left + 5, _size_monster_rc.top + _size_monster_height + 5,
			(int)(_hp), (int)(10));
		//DamageEffect
		if (_haveDamage == true)
		{
			_img_damageEffect->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
	}
	if (_counter_DeadEffect != 30)
	{
		_img_deadEffect->frameRender(getMemDC(), _size_monster_rc.left - 52, _size_monster_rc.top - 37);
	}
}
