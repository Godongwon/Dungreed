#include "stdafx.h"
#include "Skeleton_warrior_onehand.h"
Skeleton_warrior_onehand::Skeleton_warrior_onehand()
{
}
Skeleton_warrior_onehand::~Skeleton_warrior_onehand()
{
}
HRESULT Skeleton_warrior_onehand::init()
{
	//===================
	//=		렉트 크기	=
	//===================
	_size_monster_width = 20;
	_size_monster_height = 34;
	_distance_chk_player_width = 500;
	_distance_chk_player_height = 200;
	_distance_attack_monster_left_width = 50;
	_distance_attack_monster_left_height = 50;
	_distance_attack_monster_right_width = 50;
	_distance_attack_monster_right_height = 50;
	//===================
	//=		능력치		=
	//===================
	_hp = 35;
	_attack_damage = 10;
	_speed_attack = 100;
	_speed_move = 2.0f;
	_speed_swing_sword = 100;
	//===================
	//=		A I			=
	//===================
	_bChk_player = NULL;
	_bJump_monster = NULL;
	_cooldown_idle_act = 200;
	_cooldown_attack = NULL;
	_cooldown_swing_sword = _speed_swing_sword;
	//===================
	//=		EFFECT		=
	//===================
	_hpTemp = 35;
	_monsterHpBar_W = 35;
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
	_img_leftIdle_weapon = new image;
	_img_rightIdle_weapon = new image;
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
	//Move
	_img_left_move->init("resource/image/Monster/skeleton_small_move_left.bmp",
		70 * 2, 17 * 2, 7, 1, true, RGB(255, 0, 255));
	_img_left_move->set_frameSection(1, 0, 6, 5, 1);
	_img_right_move->init("resource/image/Monster/skeleton_small_move_right.bmp",
		70 * 2, 17 * 2, 7, 1, true, RGB(255, 0, 255));
	_img_right_move->set_frameSection(1, 0, 6, 5, 1);
	//Weapon idle
	_img_leftIdle_weapon->init("resource/image/Monster/sword_onehand_idle_left.bmp",
		32 * 2, 32 * 2, 1, 1, true, RGB(255, 0, 255));
	_img_rightIdle_weapon->init("resource/image/Monster/sword_onehand_idle_right.bmp",
		32 * 2, 32 * 2, 1, 1, true, RGB(255, 0, 255));
	//Weapon attack
	_img_leftAttack_weapon->init("resource/image/Monster/sword_onehand_attack_left.bmp",
		384 * 2, 42 * 2, 12, 1, true, RGB(255, 0, 255));
	_img_leftAttack_weapon->set_frameSection(2, 11, 6, 10, 1, 6, 0, 10, 1);
	_img_rightAttack_weapon->init("resource/image/Monster/sword_onehand_attack_right.bmp",
		384 * 2, 42 * 2, 12, 1, true, RGB(255, 0, 255));
	_img_rightAttack_weapon->set_frameSection(2, 0, 6, 10, 1, 6, 11, 10, 1);
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
	SOUNDMANAGER->addSound("attack_onehand", "resource/sound/player/swish6.wav", true, true);
	SOUNDMANAGER->addSound("Hit_monster", "resource/sound/effect/hitMonster.wav", true, true);
	SOUNDMANAGER->addSound("die", "resource/sound/enemy/monsterDie.wav", true, true);
	_bDebug = false;
	return S_OK;
}
void Skeleton_warrior_onehand::release()
{
	_img_leftIdle_weapon->release();
	_img_rightIdle_weapon->release();
	_img_leftAttack_weapon->release();
	_img_rightAttack_weapon->release();
	_img_left_idle->release();
	_img_right_idle->release();
	_img_left_move->release();
	_img_right_move->release();
	_img_deadEffect->release();
	SAFE_DELETE(_img_leftIdle_weapon);
	SAFE_DELETE(_img_rightIdle_weapon);
	SAFE_DELETE(_img_leftAttack_weapon);
	SAFE_DELETE(_img_rightAttack_weapon);
	SAFE_DELETE(_img_left_idle);
	SAFE_DELETE(_img_right_idle);
	SAFE_DELETE(_img_left_move);
	SAFE_DELETE(_img_right_move);
	SAFE_DELETE(_img_deadEffect);
	SAFE_DELETE(_img_damageEffect);
	SAFE_DELETE(_img_lifeBack);
	SAFE_DELETE(_img_lifeBar);
}
void Skeleton_warrior_onehand::update()
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
		if (_img_leftAttack_weapon->getFrameX() == 4 && _cooldown_swing_sword < _speed_swing_sword - 30)
		{
			_bAttackStart = true;
		}
		if (_img_rightAttack_weapon->getFrameX() == 7 && _cooldown_swing_sword < _speed_swing_sword - 30)
		{
			_bAttackStart = true;
		}
		if (_img_leftAttack_weapon->getFrameX() == 0 && _bShow_left == true)
		{
			_cooldown_swing_sword = 0;
		}
		if (_img_rightAttack_weapon->getFrameX() == 11 && _bShow_left == false)
		{
			_cooldown_swing_sword = 0;
		}
		if (_bSwing_sword == true && _cooldown_swing_sword == _speed_swing_sword)
		{
			_img_leftAttack_weapon->setFrameX(11);
			_img_rightAttack_weapon->setFrameX(0);
		}
		if (_bSwing_sword == true && _cooldown_swing_sword < _speed_swing_sword && _cooldown_swing_sword > _speed_swing_sword - 30)
		{
			_img_leftAttack_weapon->set_breakFrame(5);
			_img_rightAttack_weapon->set_breakFrame(6);
		}
		if (_bSwing_sword == true && _cooldown_swing_sword < _speed_swing_sword && _cooldown_swing_sword < _speed_swing_sword - 30)
		{
			_img_leftAttack_weapon->set_breakFrame();
			_img_rightAttack_weapon->set_breakFrame();
		}
		if (_cooldown_swing_sword == 70)
		{
			SOUNDMANAGER->play("attack_onehand");
		}
		if (_cooldown_swing_sword == 61)
		{
			SOUNDMANAGER->stop("attack_onehand");
		}
		if (_hp <= 0)
		{
			SOUNDMANAGER->stop("attack_onehand");
		}
	}
	dead_monster();
	dead_effect();
	//image Update
	_img_left_move->frameUpdate(true);
	_img_right_move->frameUpdate(true);
	_img_leftAttack_weapon->frameUpdate(false,true);
	_img_rightAttack_weapon->frameUpdate(false,false);
	_img_deadEffect->frameUpdate(true);
	_img_damageEffect->frameUpdate(true);
}
void Skeleton_warrior_onehand::render()
{
	if (_counter_DeadEffect == 30)
	{
		//Weapon idle
		if (_bShow_left == true && _bSwing_sword == false)
		{
			_img_leftIdle_weapon->frameRender(getMemDC(), _size_monster_rc.left - 45, _size_monster_rc.top - 20);
		}
		if (_bShow_left == false && _bSwing_sword == false)
		{
			_img_rightIdle_weapon->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top - 20);
		}
		//Weapon attack
		if (_bShow_left == true && _bSwing_sword == true)
		{
			_img_leftAttack_weapon->frameRender(getMemDC(), _size_monster_rc.left - 45, _size_monster_rc.top - 30);
		}
		if (_bShow_left == false && _bSwing_sword == true)
		{
			_img_rightAttack_weapon->frameRender(getMemDC(), _size_monster_rc.left, _size_monster_rc.top - 30);
		}
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
		_img_lifeBack->render(getMemDC(), _size_monster_rc.left - 8, _size_monster_rc.top + 40, 0, 0,
			(int)(_monsterHpBar_W), (int)(10));
		_img_lifeBar->render(getMemDC(),
			_size_monster_rc.left - 8, _size_monster_rc.top + 40, 0, 0,
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
