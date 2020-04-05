#include "stdafx.h"
#include "Ghost.h"
Ghost::Ghost()
{
}
Ghost::~Ghost()
{
}
HRESULT Ghost::init()
{
	//===================
	//=		렉트 크기	=
	//===================
	_size_monster_width = 40;
	_size_monster_height = 40;
	_distance_chk_player_width = 1000;
	_distance_chk_player_height = 1000;
	//===================
	//=		능력치		=
	//===================
	_hp = 10;
	_attack_damage = 10;
	_speed_attack = 150;
	_speed_move = 2.0f;
	_speed_recharge = 100;
	_speed_dash = 60;
	//===================
	//=		A I			=
	//===================
	_bDead_monster = false;
	_counter_DeadEffect = 30;
	_bChk_player = NULL;
	_bAttackable_monster = NULL;
	_bChk_player_locate = NULL;
	_cooldown_attack = _speed_attack;
	_counter_dash = _speed_dash;
	//===================
	//=		EFFECT		=
	//===================
	_hpTemp = 10;
	_monsterHpBar_W = 10;
	_counter_DeadEffect = 30;
	_counter_damageEffect = 15;
	_bDead_monster = false;
	//===================
	//=		이미지		=
	//===================
	_img_left_idle = new image;
	_img_right_idle = new image;
	_img_left_attack = new image;
	_img_right_attack = new image;
	_img_deadEffect = new image;
	_img_lifeBack = new image;
	_img_lifeBar = new image;
	_img_damageEffect = new image;
	//Idle
	_img_left_idle->init("resource/image/Monster/ghost_idle_left.bmp",
		60 * 2, 20 * 2, 3, 1, true, RGB(255, 0, 255));
	_img_left_idle->set_frameSection(1, 2, 0, 10, 1);
	_img_right_idle->init("resource/image/Monster/ghost_idle_right.bmp",
		60 * 2, 20 * 2, 3, 1, true, RGB(255, 0, 255));
	_img_right_idle->set_frameSection(1, 0, 2, 10, 1);
	//Attack
	_img_left_attack->init("resource/image/Monster/ghost_attack_left.bmp",
		120 * 2, 20 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_left_attack->set_frameSection(1, 5, 0, 10, 1);
	_img_right_attack->init("resource/image/Monster/ghost_attack_right.bmp",
		120 * 2, 20 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_right_attack->set_frameSection(1, 0, 5, 10, 1);
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
void Ghost::release()
{
	_img_left_idle->release();
	_img_right_idle->release();
	_img_left_attack->release();
	_img_right_attack->release();
	_img_deadEffect->release();
	_img_damageEffect->release();
	_img_lifeBack->release();
	_img_lifeBar->release();
	SAFE_DELETE(_img_left_idle);
	SAFE_DELETE(_img_right_idle);
	SAFE_DELETE(_img_left_attack);
	SAFE_DELETE(_img_right_attack);
	SAFE_DELETE(_img_deadEffect);
	SAFE_DELETE(_img_damageEffect);
	SAFE_DELETE(_img_lifeBack);
	SAFE_DELETE(_img_lifeBar);
}
void Ghost::update()
{
	if (_counter_DeadEffect == 30)
	{
		findPlayer();
		chasePlayer_airUnits();
		damage_effect();
		compareAttack_ghosts();
		attack_ghosts();
	}
	dead_monster();
	dead_effect();
	//image Update
	_img_left_idle->frameUpdate(true);
	_img_right_idle->frameUpdate(true);
	_img_left_attack->frameUpdate(true);
	_img_right_attack->frameUpdate(true);
	_img_deadEffect->frameUpdate(true);
	_img_damageEffect->frameUpdate(true);
}
void Ghost::render()
{
	if (_counter_DeadEffect == 30)
	{
		//idle
		if (_bShow_left == true && _bAttackable_monster == false)
		{
			_img_left_idle->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		if (_bShow_left == false && _bAttackable_monster == false)
		{
			_img_right_idle->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		//Attack
		if (_bShow_left == true && _bAttackable_monster == true)
		{
			_img_left_attack->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		if (_bShow_left == false && _bAttackable_monster == true)
		{
			_img_right_attack->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		//LifeBar
		_img_lifeBack->render(getMemDC(), _size_monster_rc.left + 10, _size_monster_rc.top + 40, 0, 0,
			(int)(_monsterHpBar_W), (int)(10));
		_img_lifeBar->render(getMemDC(),
			_size_monster_rc.left + 10, _size_monster_rc.top + 40, 0, 0,
			(int)(_hp), (int)(10));
		//DamageEffect
		if (_haveDamage == true)
		{
			_img_damageEffect->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
	}
	if (_counter_DeadEffect != 30)
	{
		_img_deadEffect->frameRender(getMemDC(), _size_monster_rc.left - 32, _size_monster_rc.top - 32);
	}
}
