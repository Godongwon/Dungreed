#include "stdafx.h"
#include "Bat_big_red.h"
void Bat_big_red::compareAttack_bats_big_red()
{
	if (_cooldown_attack == 0)
	{		
		makeFireBall_small_bat_big_red();
		_bMonsterFire = true;
		_cooldown_attack = _speed_attack;
	}	
}
void Bat_big_red::makeFireBall_small_bat_big_red()
{
	angle_toPlayer();
	int tempY = 10;
	int tempX = 30;
	_focus_changeX = 0;
	_focus_changeY = -100;
	for (int i = 0; i < 5; i++)
	{
		_focus_changeY = (_focus_changeY + tempY);
		_focus_changeX = _focus_changeX + tempX;
		init_focusforMissile_plusVar();
		_fireball_small = new Fireball_small;
		_fireball_small->init();
		_fireball_small->init_missileInfo(_focus_forMissile, getAngle_toPlayer);
		make_missile(_fireball_small);
		_fireball_small = nullptr;
		tempY += 5;
		tempX -= 5;
	}
	tempY = 30;
	tempX = 10;
	_focus_changeX = 100;
	_focus_changeY = 0;
	for (int i = 0; i < 5; i++)
	{
		_focus_changeY = (_focus_changeY + tempY);
		_focus_changeX = (_focus_changeX - tempX);
		init_focusforMissile_plusVar();
		_fireball_small = new Fireball_small;
		_fireball_small->init();
		_fireball_small->init_missileInfo(_focus_forMissile, getAngle_toPlayer);
		make_missile(_fireball_small);
		_fireball_small = nullptr;
		tempY -= 5;
		tempX += 5;
	}
	tempY = 10;
	tempX = 30;
	_focus_changeX = 0;
	_focus_changeY = 100;
	for (int i = 0; i < 5; i++)
	{
		_focus_changeY = (_focus_changeY - tempY);
		_focus_changeX = (_focus_changeX - tempX);
		init_focusforMissile_plusVar();
		_fireball_small = new Fireball_small;
		_fireball_small->init();
		_fireball_small->init_missileInfo(_focus_forMissile, getAngle_toPlayer);
		make_missile(_fireball_small);
		_fireball_small = nullptr;
		tempY += 5;
		tempX -= 5;
	}
	tempY = 30;
	tempX = 10;
	_focus_changeX = -100;
	_focus_changeY = 0;
	for (int i = 0; i < 5; i++)
	{
		_focus_changeY = (_focus_changeY - tempY);
		_focus_changeX = (_focus_changeX + tempX);
		init_focusforMissile_plusVar();
		_fireball_small = new Fireball_small;
		_fireball_small->init();
		_fireball_small->init_missileInfo(_focus_forMissile, getAngle_toPlayer);
		make_missile(_fireball_small);
		_fireball_small = nullptr;
		tempY -= 5;
		tempX += 5;
	}
	_focus_changeY = 0;
	_focus_changeX = 0;
}
Bat_big_red::Bat_big_red()
{
}
Bat_big_red::~Bat_big_red()
{
}
HRESULT Bat_big_red::init()
{
	//===================
	//=		렉트 크기	=
	//===================
	_size_monster_width = 64;
	_size_monster_height = 64;
	_distance_chk_player_width = 800;
	_distance_chk_player_height = 500;
	//===================
	//=		능력치		=
	//===================
	_hp = 45;
	_speed_attack = 200;
	//===================
	//=		A I			=
	//===================
	_bChk_player_locate = NULL;
	_bChk_player = NULL;
	_cooldown_attack = 190;
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
	_img_left_idle->init("resource/image/Monster/bat_big_red_idle_left.bmp",
		448 * 2, 64 * 2, 7, 1, true, RGB(255, 0, 255));
	_img_left_idle->set_frameSection(1, 6, 0, 5, 1);
	_img_right_idle->init("resource/image/Monster/bat_big_red_idle_right.bmp",
		448 * 2, 64 * 2, 7, 1, true, RGB(255, 0, 255));
	_img_right_idle->set_frameSection(1, 0, 6, 5, 1);
	//Attack
	_img_left_attack->init("resource/image/Monster/bat_big_red_attack_left.bmp",
		640 * 2, 64 * 2, 10, 1, true, RGB(255, 0, 255));
	_img_left_attack->set_frameSection(1, 9, 0, 5, 1);
	_img_right_attack->init("resource/image/Monster/bat_big_red_attack_right.bmp",
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
	//Sound
	SOUNDMANAGER->addSound("attack_Bat_big_red", "resource/sound/enemy/bat3.wav", true, true);
	SOUNDMANAGER->addSound("Hit_monster", "resource/sound/effect/hitMonster.wav", true, true);
	SOUNDMANAGER->addSound("die", "resource/sound/enemy/monsterDie.wav", true, true);
	_bDebug = false;
	return S_OK;
}
void Bat_big_red::release()
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
void Bat_big_red::update()
{
	if (_counter_DeadEffect == 30)
	{
		findPlayer();
		chasePlayer_RangeUnit();
		compareAttack_bats_big_red();
		damage_effect();
		if (_cooldown_attack == 1)
		{
			SOUNDMANAGER->play("attack_Bat_big_red");
		}
		if (_cooldown_attack == 185)
		{
			SOUNDMANAGER->stop("attack_Bat_big_red");
		}
		if (_hp <= 0)
		{
			SOUNDMANAGER->stop("attack_Bat_big_red");
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
void Bat_big_red::render()
{
	if (_counter_DeadEffect == 30)
	{
		//Idle
		if (_bShow_left == true && _cooldown_attack <=190 && _cooldown_attack >10)
		{
			_img_left_idle->frameRender(getMemDC(), _size_monster_rc.left - 32, _size_monster_rc.top - 32);
		}
		if (_bShow_left == false && _cooldown_attack <= 190 && _cooldown_attack > 10)
		{
			_img_right_idle->frameRender(getMemDC(), _size_monster_rc.left - 32, _size_monster_rc.top - 32);
		}
		//Attack
		if (_bShow_left == true && _cooldown_attack <=10 )
		{
			_img_left_attack->frameRender(getMemDC(), _size_monster_rc.left - 32, _size_monster_rc.top - 32);
		}
		if (_bShow_left == false && _cooldown_attack <=10)
		{
			_img_right_attack->frameRender(getMemDC(), _size_monster_rc.left - 32, _size_monster_rc.top - 32);
		}
		if (_bShow_left == true &&  _cooldown_attack > 190)
		{
			_img_left_attack->frameRender(getMemDC(), _size_monster_rc.left - 32, _size_monster_rc.top - 32);
		}
		if (_bShow_left == false && _cooldown_attack > 190)
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
