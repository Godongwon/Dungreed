#include "stdafx.h"
#include "Banshee.h"
void Banshee::compareAttack_Banshees()
{
	if (_cooldown_attack == 0)
	{
		init_focusforMissile();
		//angle_toPlayer();
		_bMonsterFire = true;
		_cooldown_attack = _speed_attack;		
		for (int angle = 0; angle < 13; angle++)
		{
			_note = new Note;
			_note->init();
			_note->init_missileInfo(_focus_forMissile, angle * 0.5);
			make_missile(_note);
			_note = nullptr;
		}
	}
}
Banshee::Banshee()
{
}
Banshee::~Banshee()
{
}
HRESULT Banshee::init()
{
	//===================
	//=		렉트 크기	=
	//===================
	_size_monster_width = 40;
	_size_monster_height = 44;
	_distance_chk_player_width = 800;
	_distance_chk_player_height = 800;
	//===================
	//=		능력치		=
	//===================
	_hp = 45;
	_speed_attack = 190;
	//===================
	//=		A I			=
	//===================
	_bChk_player = NULL;
	_cooldown_attack = 189;
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
	_img_left_idle->init("resource/image/Monster/banshee_idle_left.bmp",
		120 * 2, 22 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_left_idle->set_frameSection(1, 5, 0, 10, 1);
	_img_right_idle->init("resource/image/Monster/banshee_idle_right.bmp",
		120 * 2, 22 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_right_idle->set_frameSection(1, 0, 5, 10, 1);
	//Attack
	_img_left_attack->init("resource/image/Monster/banshee_attack_left.bmp",
		120 * 2, 22 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_left_attack->set_frameSection(1, 5, 0, 5, 1);
	_img_right_attack->init("resource/image/Monster/banshee_attack_right.bmp",
		120 * 2, 22 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_right_attack->set_frameSection(1, 0, 5, 5, 1);
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
	//Sound
	SOUNDMANAGER->addSound("attack_banshee", "resource/sound/enemy/banshee.wav", true, true);
	SOUNDMANAGER->addSound("Hit_monster", "resource/sound/effect/hitMonster.wav", true, true);
	SOUNDMANAGER->addSound("die", "resource/sound/enemy/monsterDie.wav", true, true);
	return S_OK;
}
void Banshee::release()
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
void Banshee::update()
{
	if (_counter_DeadEffect == 30)
	{
		findPlayer();
		chasePlayer_RangeUnit();
		compareAttack_Banshees();
		damage_effect();
		if (_cooldown_attack == 15)
		{
			SOUNDMANAGER->play("attack_banshee");
		}
		if (_cooldown_attack == 160)
		{
			SOUNDMANAGER->stop("attack_banshee");
		}
		if (_hp <= 0)
		{
			SOUNDMANAGER->stop("attack_banshee");
		}
	}
	dead_monster();
	dead_effect();
	//image Update
	_img_left_idle->frameUpdate(true,false);
	_img_right_idle->frameUpdate(true);
	_img_left_attack->frameUpdate(true,false);
	_img_right_attack->frameUpdate(true);
	_img_deadEffect->frameUpdate(true);
	_img_damageEffect->frameUpdate(true);
}
void Banshee::render()
{
	if (_counter_DeadEffect == 30)
	{
		//Idle
		if (_bShow_left == true && _cooldown_attack < 190 && _cooldown_attack > 20)
		{
			_img_left_idle->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		if (_bShow_left == false && _cooldown_attack < 190 && _cooldown_attack > 20)
		{
			_img_right_idle->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		//Attack
		if (_bShow_left == true && _cooldown_attack > 190 && _cooldown_attack < 200)
		{
			_img_left_attack->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		if (_bShow_left == false && _cooldown_attack > 190 && _cooldown_attack < 200)
		{
			_img_right_attack->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		if (_bShow_left == true && _cooldown_attack < 20)
		{
			_img_left_attack->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		if (_bShow_left == false && _cooldown_attack < 20)
		{
			_img_right_attack->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		//LifeBar
		_img_lifeBack->render(getMemDC(), _size_monster_rc.left, _size_monster_rc.top + _size_monster_height + 5,
			(int)(_monsterHpBar_W), (int)(10));
		_img_lifeBar->render(getMemDC(),
			_size_monster_rc.left, _size_monster_rc.top + _size_monster_height + 5,
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
