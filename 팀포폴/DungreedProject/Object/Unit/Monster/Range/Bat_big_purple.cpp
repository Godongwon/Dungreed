#include "stdafx.h"
#include "Bat_big_purple.h"
void Bat_big_purple::compareAttack_bats_big_purple()
{
	if (_cooldown_attack == 0)
	{
		init_focusforMissile();
		angle_toPlayer();
		makeCount -= 1;
		if (makeCount == 29)
		{
			makeFireBall_small_bat_big_purple();
		}
		if (makeCount == 19)
		{
			makeFireBall_small_bat_big_purple();
		}
		if (makeCount == 9)
		{
			makeFireBall_small_bat_big_purple();
		}
		if (makeCount == 0)
		{
			makeCount = 30;
			_cooldown_attack = _speed_attack;
		}
		_bMonsterFire = true;
	}
}
void Bat_big_purple::makeFireBall_small_bat_big_purple()
{
	_fireball_small = new Fireball_small;
	_fireball_small->init();
	_fireball_small->init_missileInfo(_focus_forMissile, getAngle_toPlayer);
	make_missile(_fireball_small);
	_fireball_small = nullptr;
	getAngle_toPlayer += 0.5;
	_fireball_small = new Fireball_small;
	_fireball_small->init();
	_fireball_small->init_missileInfo(_focus_forMissile, getAngle_toPlayer);
	make_missile(_fireball_small);
	_fireball_small = nullptr;
	getAngle_toPlayer -= 1.0;
	_fireball_small = new Fireball_small;
	_fireball_small->init();
	_fireball_small->init_missileInfo(_focus_forMissile, getAngle_toPlayer);
	make_missile(_fireball_small);
	_fireball_small = nullptr;
}
Bat_big_purple::Bat_big_purple()
{
}
Bat_big_purple::~Bat_big_purple()
{
}
HRESULT Bat_big_purple::init()
{
	//===================
	//=		렉트 크기	=
	//===================
	_size_monster_width = 64;
	_size_monster_height = 64;
	_distance_chk_player_width = 800;
	_distance_chk_player_height = 800;
	//===================
	//=		능력치		=
	//===================
	_hp = 45;
	_speed_attack = 200;
	makeCount = 30;
	//===================
	//=		A I			=
	//===================
	_bChk_player = NULL;
	_bChk_player_locate = NULL;
	_cooldown_attack = _speed_attack;
	//===================
	//=		EFFECT		=
	//===================
	_hpTemp = 45;
	_monsterHpBar_W = 45;
	_bDead_monster = false;
	_counter_DeadEffect = 30;
	_counter_damageEffect = 15;
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
	_img_left_idle->init("resource/image/Monster/bat_big_purple_idle_left.bmp",
		448 * 2, 64 * 2, 7, 1, true, RGB(255, 0, 255));
	_img_left_idle->set_frameSection(1, 6, 0, 5, 1);
	_img_right_idle->init("resource/image/Monster/bat_big_purple_idle_right.bmp",
		448 * 2, 64 * 2, 7, 1, true, RGB(255, 0, 255));
	_img_right_idle->set_frameSection(1, 0, 6, 5, 1);
	//Attack
	_img_left_attack->init("resource/image/Monster/bat_big_purple_attack_left.bmp",
		640 * 2, 64 * 2, 10, 1, true, RGB(255, 0, 255));
	_img_left_attack->set_frameSection(1, 9, 0, 5, 1);
	_img_right_attack->init("resource/image/Monster/bat_big_purple_attack_right.bmp",
		640 * 2, 64 * 2, 10, 1, true, RGB(255, 0, 255));
	_img_right_attack->set_frameSection(1, 0, 9, 5, 1);
	//Dead
	_img_deadEffect->init("resource/image/Monster/monster_dead.bmp",
		704 * 3, 64 * 3, 11, 1, true, RGB(255, 0, 255));
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
	//Sound
	SOUNDMANAGER->addSound("attack_Bat_big_purple", "resource/sound/enemy/bat2.wav", true, true);
	SOUNDMANAGER->addSound("Hit_monster", "resource/sound/effect/hitMonster.wav", true, true);
	SOUNDMANAGER->addSound("die", "resource/sound/enemy/monsterDie.wav", true, true);
	return S_OK;
}
void Bat_big_purple::release()
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
void Bat_big_purple::update()
{
	if (_counter_DeadEffect == 30)
	{
		findPlayer();
		chasePlayer_RangeUnit();
		compareAttack_bats_big_purple();
		damage_effect();
		if (_cooldown_attack == 1)
		{
			SOUNDMANAGER->play("attack_Bat_big_purple");
		}
		if (_cooldown_attack == 200)
		{
			SOUNDMANAGER->stop("attack_Bat_big_purple");
		}
		if (_hp <= 0)
		{
			SOUNDMANAGER->stop("attack_Bat_big_purple");
		}

	}
	dead_monster();
	dead_effect();
	//image Update
	_img_left_idle->frameUpdate(true, false);
	_img_right_idle->frameUpdate(true);
	_img_left_attack->frameUpdate(true, false);
	_img_right_attack->frameUpdate(true);
	_img_deadEffect->frameUpdate(true);
	_img_damageEffect->frameUpdate(true);
}
void Bat_big_purple::render()
{
	if (_counter_DeadEffect == 30)
	{
		//Idle
		if (_bShow_left == true && _cooldown_attack != 0)
		{
			_img_left_idle->frameRender(getMemDC(), _size_monster_rc.left - 32, _size_monster_rc.top - 32);
		}
		if (_bShow_left == false && _cooldown_attack != 0)
		{
			_img_right_idle->frameRender(getMemDC(), _size_monster_rc.left - 32, _size_monster_rc.top - 32);
		}
		//Attack
		if (_bShow_left == true && _cooldown_attack == 0)
		{
			_img_left_attack->frameRender(getMemDC(), _size_monster_rc.left - 32, _size_monster_rc.top - 32);
		}
		if (_bShow_left == false && _cooldown_attack == 0)
		{
			_img_right_attack->frameRender(getMemDC(), _size_monster_rc.left - 32, _size_monster_rc.top - 32);
		}
		//LifeBar
		_img_lifeBack->render(getMemDC(), _size_monster_rc.left + 10, _size_monster_rc.top + _size_monster_height + 5,
			(int)(_monsterHpBar_W), (int)(10));
		_img_lifeBar->render(getMemDC(),
			_size_monster_rc.left + 10, _size_monster_rc.top + _size_monster_height + 5,
			(int)(_hp), (int)(10));
		//DamageEffect
		if (_haveDamage == true)
		{
			_img_damageEffect->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
	}
	if (_counter_DeadEffect != 30)
	{
		_img_deadEffect->frameRender(getMemDC(), _size_monster_rc.left - 64, _size_monster_rc.top - 64);
	}
}
