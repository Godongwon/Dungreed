#include "stdafx.h"
#include "Skeleton_archer.h"
void Skeleton_archer::compareAttack_Archers()
{	
	if (_cooldown_attack == 0)
	{
		init_focusforMissile();
		angle_toPlayer();
		_bMonsterFire = true;
		_cooldown_attack = _speed_attack;
		_arrow = new Arrow;
		_arrow->init();
		_arrow->init_missileInfo(_focus_forMissile, getAngle_toPlayer);
		make_missile(_arrow);
		_arrow = nullptr;
	}
}
Skeleton_archer::Skeleton_archer()
{
}
Skeleton_archer::~Skeleton_archer()
{
}
HRESULT Skeleton_archer::init()
{
	//===================
	//=		렉트 크기	=
	//===================
	_size_monster_width = 20;
	_size_monster_height = 34;
	_distance_chk_player_width = 800;
	_distance_chk_player_height = 800;
	//===================
	//=		능력치		=
	//===================
	_hp = 30;
	_speed_attack = 200;
	//===================
	//=		A I			=
	//===================
	_bChk_player = NULL;
	_bMonsterFire = NULL;
	_cooldown_attack = _speed_attack;
	//===================
	//=		EFFECT		=
	//===================
	_hpTemp = 30;
	_monsterHpBar_W = 30;
	_bDead_monster = false;
	_counter_DeadEffect = 30;
	_counter_damageEffect = 15;
	//===================
	//=		이미지		=
	//===================
	_img_left_idle = new image;
	_img_right_idle = new image;
	_img_leftAttack_weapon = new image;
	_img_rightAttack_weapon = new image;
	_img_deadEffect = new image;
	_img_lifeBack = new image;
	_img_lifeBar = new image;
	_img_damageEffect = new image;
	//Idle
	_img_left_idle->init("resource/image/Monster/skeleton_small_idle_left.bmp",
		10 * 2, 17 * 2, 1, 1, true, RGB(255, 0, 255));
	_img_right_idle->init("resource/image/Monster/skeleton_small_idle_right.bmp",
		10 * 2, 17 * 2, 1, 1, true, RGB(255, 0, 255));
	//Attack
	_img_leftAttack_weapon->init("resource/image/Monster/bow_left.bmp",
		102 * 2, 15 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_leftAttack_weapon->set_frameSection(2, 5, 2, 5, 1, 1, 0, 25, 1);
	_img_rightAttack_weapon->init("resource/image/Monster/bow_right.bmp",
		102 * 2, 15 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_rightAttack_weapon->set_frameSection(2, 0, 3, 5, 1, 4, 5, 25, 1);
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
	//Sound
	SOUNDMANAGER->addSound("Hit_monster", "resource/sound/effect/hitMonster.wav", true, true);
	SOUNDMANAGER->addSound("die", "resource/sound/enemy/monsterDie.wav", true, true);
	_bDebug = false;
	return S_OK;
}
void Skeleton_archer::release()
{
	_img_left_idle->release();
	_img_right_idle->release();
	_img_leftAttack_weapon->release();
	_img_rightAttack_weapon->release();
	_img_deadEffect->release();
	_img_damageEffect->release();
	_img_lifeBack->release();
	_img_lifeBar->release();
	SAFE_DELETE(_img_left_idle);
	SAFE_DELETE(_img_right_idle);
	SAFE_DELETE(_img_leftAttack_weapon);
	SAFE_DELETE(_img_rightAttack_weapon);
	SAFE_DELETE(_img_damageEffect);
	SAFE_DELETE(_img_lifeBack);
	SAFE_DELETE(_img_lifeBar);
}
void Skeleton_archer::update()
{
	if (_counter_DeadEffect == 30)
	{
		findPlayer();
		chasePlayer_RangeUnit();
		compareAttack_Archers();
		damage_effect();
		if (_cooldown_attack >= 175)
		{
			_img_leftAttack_weapon->set_breakFrame(5);
			_img_rightAttack_weapon->set_breakFrame(0);
		}
		if (_cooldown_attack <= 165 && _cooldown_attack > 115)
		{
			_img_leftAttack_weapon->set_breakFrame(4);
			_img_rightAttack_weapon->set_breakFrame(1);
		}
		if (_cooldown_attack <= 115 && _cooldown_attack > 65)
		{
			_img_leftAttack_weapon->set_breakFrame(3);
			_img_rightAttack_weapon->set_breakFrame(2);
		}
		if (_cooldown_attack <= 65 && _cooldown_attack > 10)
		{
			_img_leftAttack_weapon->set_breakFrame(2);
			_img_rightAttack_weapon->set_breakFrame(3);
		}
		if (_cooldown_attack <= 10)
		{
			_img_leftAttack_weapon->setFrameX(1);
			_img_rightAttack_weapon->setFrameX(4);
			_img_leftAttack_weapon->set_breakFrame();
			_img_rightAttack_weapon->set_breakFrame();
		}
		if (_cooldown_attack <= 7)
		{
			_img_leftAttack_weapon->setFrameX(0);
			_img_rightAttack_weapon->setFrameX(5);
		}
	}
	dead_monster();
	dead_effect();
	//image Update
	_img_leftAttack_weapon->frameUpdate(false, true);
	_img_rightAttack_weapon->frameUpdate(false);
	_img_deadEffect->frameUpdate(true);
	_img_damageEffect->frameUpdate(true);
}
void Skeleton_archer::render()
{
	if (_counter_DeadEffect == 30)
	{
		//Idle
		//Attack
		if (_bShow_left == true)
		{
			_img_left_idle->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
			_img_leftAttack_weapon->frameRender(getMemDC(), _size_monster_rc.left - 20, _size_monster_rc.top + 5);
		}
		if (_bShow_left == false)
		{
			_img_right_idle->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
			_img_rightAttack_weapon->frameRender(getMemDC(), _size_monster_rc.left + 6, _size_monster_rc.top + 5);
		}
		//LifeBar
		_img_lifeBack->render(getMemDC(), _size_monster_rc.left - 2, _size_monster_rc.top + _size_monster_height + 5,
			(int)(_monsterHpBar_W), (int)(10));
		_img_lifeBar->render(getMemDC(),
			_size_monster_rc.left - 2 , _size_monster_rc.top + _size_monster_height + 5,
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
