#include "stdafx.h"
#include "Skeleton_dog.h"
Skeleton_dog::Skeleton_dog()
{
}
Skeleton_dog::~Skeleton_dog()
{
}
HRESULT Skeleton_dog::init()
{
	//===================
	//=		렉트 크기	=
	//===================
	_size_monster_width = 40;
	_size_monster_height = 36;
	_distance_chk_player_width = 500;
	_distance_chk_player_height = 200;
	//===================
	//=		능력치		=
	//===================
	_hp = 25;
	_attack_damage = 10;
	_speed_attack = 200;
	_speed_move = 3.0f;
	_speed_recharge = 100;	
	//===================
	//=		A I			=
	//===================
	_bChk_player = NULL;
	_bRest = NULL;
	_bGiveDamage = NULL;
	_cooldown_idle_act = 200;
	_cooldown_attack = _speed_attack;
	_cooldown_recharge = _speed_recharge;
	//===================
	//=		EFFECT		=
	//===================
	_hpTemp = 25;
	_monsterHpBar_W = 25;
	_counter_DeadEffect = 30;
	_counter_damageEffect = 15;
	_bDead_monster = false;
	//===================
	//=		이미지		=
	//===================
	_img_left_idle = new image;
	_img_right_idle = new image;
	_img_left_move = new image;
	_img_right_move = new image;
	_img_deadEffect = new image;
	_img_lifeBack = new image;
	_img_lifeBar = new image;
	_img_damageEffect = new image;
	//Idle
	_img_left_idle->init("resource/image/Monster/skeleton_dog_idle_left.bmp",
		100 * 2, 18 * 2, 5, 1, true, RGB(255, 0, 255));
	_img_left_idle->set_frameSection(1, 4, 0, 5, 1);
	_img_right_idle->init("resource/image/Monster/skeleton_dog_idle_right.bmp",
		100 * 2, 18 * 2, 5, 1, true, RGB(255, 0, 255));
	_img_right_idle->set_frameSection(1, 0, 4, 5, 1);
	//Move
	_img_left_move->init("resource/image/Monster/skeleton_dog_move_left.bmp",
		140 * 2, 18 * 2, 7, 1, true, RGB(255, 0, 255));
	_img_left_move->set_frameSection(1, 6, 0, 3, 1);
	_img_right_move->init("resource/image/Monster/skeleton_dog_move_right.bmp",
		140 * 2, 18 * 2, 7, 1, true, RGB(255, 0, 255));
	_img_right_move->set_frameSection(1, 0, 6, 3, 1);
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
	SOUNDMANAGER->addSound("Hit_monster", "resource/sound/effect/hitMonster.wav", true, true);
	SOUNDMANAGER->addSound("die", "resource/sound/enemy/monsterDie.wav", true, true);
	_bDebug = false;
	return S_OK;
}
void Skeleton_dog::release()
{
	_img_left_idle->release();
	_img_right_idle->release();
	_img_left_move->release();
	_img_right_move->release();
	_img_deadEffect->release();
	_img_damageEffect->release();
	_img_lifeBack->release();
	_img_lifeBar->release();
	SAFE_DELETE(_img_left_idle);
	SAFE_DELETE(_img_right_idle);
	SAFE_DELETE(_img_left_move);
	SAFE_DELETE(_img_right_move);
	SAFE_DELETE(_img_deadEffect);
	SAFE_DELETE(_img_damageEffect);
	SAFE_DELETE(_img_lifeBack);
	SAFE_DELETE(_img_lifeBar);
}
void Skeleton_dog::update()
{	
	if (_counter_DeadEffect == 30)
	{
		idle();
		findPlayer();
		damage_effect();
		chasePlayer_dogs();
		compareAttack_dogs();
		attack_dogs();
	}
	dead_monster();
	dead_effect();
	//image Update
	_img_left_idle->frameUpdate(true);
	_img_right_idle->frameUpdate(true);
	_img_left_move->frameUpdate(true);
	_img_right_move->frameUpdate(true);
	_img_deadEffect->frameUpdate(true);
	_img_damageEffect->frameUpdate(true);
}
void Skeleton_dog::render()
{
	if (_counter_DeadEffect == 30)
	{
		//Idle
		if (_bShow_left == true && _bIs_moving == false)
		{
			_img_left_idle->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		if (_bShow_left == false && _bIs_moving == false)
		{
			_img_right_idle->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		//Move
		if (_bShow_left == true && _bIs_moving == true)
		{
			_img_left_move->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		if (_bShow_left == false && _bIs_moving == true)
		{
			_img_right_move->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
		//LifeBar
		_img_lifeBack->render(getMemDC(), _size_monster_rc.left + _size_monster_width*0.25, _size_monster_rc.top + _size_monster_height + 5,
			(int)(_monsterHpBar_W), (int)(10));
		_img_lifeBar->render(getMemDC(),
			_size_monster_rc.left + _size_monster_width*0.25, _size_monster_rc.top + _size_monster_height + 5,
			(int)(_hp), (int)(10));
		//DamageEffect
		if (_haveDamage == true)
		{
			_img_damageEffect->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
	}
	if (_counter_DeadEffect != 30)
	{
		_img_deadEffect->frameRender(getMemDC(), _size_monster_rc.left - 48, _size_monster_rc.top - 32);
	}

}
