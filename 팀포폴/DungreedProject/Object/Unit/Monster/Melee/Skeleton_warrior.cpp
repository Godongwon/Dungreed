#include "stdafx.h"
#include "Skeleton_warrior.h"
Skeleton_warrior::Skeleton_warrior()
{
}
Skeleton_warrior::~Skeleton_warrior()
{
}
HRESULT Skeleton_warrior::init()
{
	//===================
	//=		렉트 크기	=
	//===================
	_size_monster_width = 44;
	_size_monster_height = 60;
	_distance_chk_player_width = 500;
	_distance_chk_player_height = 200;
	_distance_attack_monster_left_width = 100;
	_distance_attack_monster_left_height = 100;
	_distance_attack_monster_right_width = 100;
	_distance_attack_monster_right_height = 100;
	//===================
	//=		능력치		=
	//===================
	_hp = 50;
	_attack_damage = 10;
	_speed_attack = 100;
	_speed_move = 2.0f;
	_speed_swing_sword = 100;
	//===================
	//=		A I			=
	//===================
	_bChk_player = NULL;
	_bJump_monster = NULL;
	_bGiveDamage = NULL;
	_cooldown_idle_act = 200;
	_cooldown_attack = NULL;
	_cooldown_swing_sword = _speed_swing_sword;
	//===================
	//=		EFFECT		=
	//===================
	_hpTemp = 50;
	_monsterHpBar_W = 50;
	_bDead_monster = false;
	_counter_DeadEffect = 30;
	_counter_damageEffect = 15;
	//===================
	//=		이미지		=
	//===================
	_img_left_idle = new image;
	_img_right_idle = new image;
	_img_left_move = new image;
	_img_right_move = new image;
	_img_left_attack = new image;
	_img_right_attack = new image;
	_img_deadEffect = new image;
	_img_lifeBack = new image;
	_img_lifeBar = new image;
	_img_damageEffect = new image;
	//Idle
	_img_left_idle->init("resource/image/Monster/skeleton_warrior_idle_left.bmp",
		132 * 2, 30 * 2, 4, 1, true, RGB(255, 0, 255));
	_img_left_idle->set_frameSection(1, 0, 3, 5, 1);
	_img_right_idle->init("resource/image/Monster/skeleton_warrior_idle_right.bmp",
		132 * 2, 30 * 2, 4, 1, true, RGB(255, 0, 255));
	_img_right_idle->set_frameSection(1, 6, 3, 5, 1);
	//Move
	_img_left_move->init("resource/image/Monster/skeleton_warrior_move_left.bmp",
		198 * 2, 30 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_left_move->set_frameSection(1, 0, 5, 5, 1);
	_img_right_move->init("resource/image/Monster/skeleton_warrior_move_right.bmp",
		198 * 2, 30 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_right_move->set_frameSection(1, 0, 5, 5, 1);
	//Attack
	_img_left_attack->init("resource/image/Monster/skeleton_warrior_attack_left.bmp",
		852 * 2, 48 * 2, 12, 1, true, RGB(255, 0, 255));
	_img_left_attack->set_frameSection(2, 11, 10, 60, 1, 10, 0, 5, 1);
	_img_right_attack->init("resource/image/Monster/skeleton_warrior_attack_right.bmp",
		852 * 2, 48 * 2, 12, 1, true, RGB(255, 0, 255));
	_img_right_attack->set_frameSection(2, 0, 1, 60, 1, 1, 11, 5, 1);
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
	SOUNDMANAGER->addSound("attack_warrior", "resource/sound/player/swish9.wav", true, true);
	SOUNDMANAGER->addSound("Hit_monster", "resource/sound/effect/hitMonster.wav", true, true);
	SOUNDMANAGER->addSound("die", "resource/sound/enemy/monsterDie.wav", true, true);
	_bDebug = false;
	return S_OK;
}
void Skeleton_warrior::release()
{
	_img_left_idle->release();
	_img_right_idle->release();
	_img_left_move->release();
	_img_right_move->release();
	_img_left_attack->release();
	_img_right_attack->release();
	_img_deadEffect->release();
	_img_damageEffect->release();
	_img_lifeBack->release();
	_img_lifeBar->release();
	SAFE_DELETE(_img_leftIdle_weapon);
	SAFE_DELETE(_img_rightIdle_weapon);
	SAFE_DELETE(_img_left_move);
	SAFE_DELETE(_img_right_move);
	SAFE_DELETE(_img_leftAttack_weapon);
	SAFE_DELETE(_img_rightAttack_weapon);
	SAFE_DELETE(_img_deadEffect);
	SAFE_DELETE(_img_damageEffect);
	SAFE_DELETE(_img_lifeBack);
	SAFE_DELETE(_img_lifeBar);
}
void Skeleton_warrior::update()
{
	if (_counter_DeadEffect == 30)
	{
		//함수
		idle();
		findPlayer();
		chasePlayer();
		jump_up();
		damage_effect();
		compareAttack_warriors();
		attack_warriors();
		if (_img_left_attack->getFrameX() == 9 && _cooldown_swing_sword < _speed_swing_sword - 30)
		{
			_bAttackStart = true;
		}
		if (_img_right_attack->getFrameX() == 2 && _cooldown_swing_sword < _speed_swing_sword - 30)
		{
			_bAttackStart = true;
		}
		if (_img_left_attack->getFrameX() == 0 && _bShow_left == true)
		{
			_cooldown_swing_sword = 0;
		}
		if (_img_right_attack->getFrameX() == 11 && _bShow_left == false)
		{
			_cooldown_swing_sword = 0;
		}
		if (_bSwing_sword == true && _cooldown_swing_sword == _speed_swing_sword)
		{
			_img_left_attack->setFrameX(11);
			_img_right_attack->setFrameX(0);
		}
		if (_bSwing_sword == true && _cooldown_swing_sword < _speed_swing_sword && _cooldown_swing_sword > _speed_swing_sword - 30)
		{
			_img_left_attack->set_breakFrame(10);
			_img_right_attack->set_breakFrame(1);
		}
		if (_bSwing_sword == true && _cooldown_swing_sword < _speed_swing_sword && _cooldown_swing_sword < _speed_swing_sword - 30)
		{
			_img_left_attack->set_breakFrame();
			_img_right_attack->set_breakFrame();
		}
		if (_cooldown_swing_sword == 70)
		{
			SOUNDMANAGER->play("attack_warrior");
		}
		if (_cooldown_swing_sword == 60)
		{
			SOUNDMANAGER->stop("attack_warrior");
		}
		if (_hp <= 0)
		{
			SOUNDMANAGER->stop("attack_warrior");
		}
	}
	dead_monster();
	dead_effect();
	//image Update
	_img_left_idle->frameUpdate(true);
	_img_right_idle->frameUpdate(true);
	_img_left_move->frameUpdate(true);
	_img_right_move->frameUpdate(true);
	_img_left_attack->frameUpdate(false, true);
	_img_right_attack->frameUpdate(false, false);
	_img_deadEffect->frameUpdate(true);
	_img_damageEffect->frameUpdate(true);	
}
void Skeleton_warrior::render()
{
	if (_counter_DeadEffect == 30 )
	{
		//Idle
		if (_bShow_left == true && _bIs_moving == false && _bSwing_sword == false)
		{
			_img_left_idle->frameRender(getMemDC(), _size_monster_rc.left - 7, _size_monster_rc.top);
		}
		if (_bShow_left == false && _bIs_moving == false && _bSwing_sword == false)
		{
			_img_right_idle->frameRender(getMemDC(), _size_monster_rc.left - 16, _size_monster_rc.top);
		}
		//Move
		if (_bShow_left == true && _bIs_moving == true)
		{
			_img_left_move->frameRender(getMemDC(), _size_monster_rc.left - 7, _size_monster_rc.top);
		}
		if (_bShow_left == false && _bIs_moving == true)
		{
			_img_right_move->frameRender(getMemDC(), _size_monster_rc.left - 16, _size_monster_rc.top);
		}
		//Attack
		if (_bShow_left == true && _bSwing_sword == true)
		{
			_img_left_attack->frameRender(getMemDC(), _size_monster_rc.left - 70, _size_monster_rc.top - 36);
		}
		if (_bShow_left == false && _bSwing_sword == true)
		{
			_img_right_attack->frameRender(getMemDC(), _size_monster_rc.left - 20, _size_monster_rc.top - 36);
		}
		//LifeBar
		_img_lifeBack->render(getMemDC(), _size_monster_rc.left, _size_monster_rc.top + _size_monster_height + 5,
			(int)(_monsterHpBar_W), (int)(10));
		_img_lifeBar->render(getMemDC(),
			_size_monster_rc.left , _size_monster_rc.top + _size_monster_height + 5,
			(int)(_hp), (int)(10));
		//DamageEffect
		if (_haveDamage == true)
		{
			_img_damageEffect->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top);
		}
	}
	if (_counter_DeadEffect !=30)
	{
		_img_deadEffect->frameRender(getMemDC(), _size_monster_rc.left - 32, _size_monster_rc.top - 32);
	}
}
