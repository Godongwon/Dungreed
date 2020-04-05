#include "stdafx.h"
#include "Minotaurs.h"
Minotaurs::Minotaurs()
{
}
Minotaurs::~Minotaurs()
{
}
HRESULT Minotaurs::init()
{
	//===================
	//=		렉트 크기	=
	//===================
	_size_monster_width = 80;
	_size_monster_height = 90;
	_distance_chk_player_width = 500;
	_distance_chk_player_height = 200;
	_distance_attack_monster_left_width = 80;
	_distance_attack_monster_left_height = 100;
	_distance_attack_monster_right_width = 80;
	_distance_attack_monster_right_height = 100;
	//===================
	//=		능력치		=
	//===================
	_hp = 80;
	_attack_damage = 10;
	_speed_attack = 100;
	_speed_move = 8.0f;
	_speed_swing_sword = 100;
	_speed_recharge = 70;
	_speed_dash = 100;
	//===================
	//=		A I			=
	//===================
	_bChk_player = NULL;
	_bRest = NULL;
	_cooldown_swing_sword = _speed_swing_sword;
	_cooldown_attack = _speed_attack;
	_cooldown_recharge = _speed_recharge;
	_counter_dash = _speed_dash;
	//===================
	//=		EFFECT		=
	//===================
	_hpTemp = 80;
	_monsterHpBar_W = 80;
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
	_img_left_dash = new image;
	_img_right_dash = new image;
	_img_left_dash_dust = new image;
	_img_right_dash_dust = new image;
	_img_deadEffect = new image;
	_img_lifeBack = new image;
	_img_lifeBar = new image;
	_img_damageEffect = new image;
	//Idle
	_img_left_idle->init("resource/image/Monster/minotaurs_idle_left.bmp",
		336 * 2, 50 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_left_idle->set_frameSection(1, 0, 6, 5, 1);
	_img_right_idle->init("resource/image/Monster/minotaurs_idle_right.bmp",
		336 * 2, 50 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_right_idle->set_frameSection(1, 6, 0, 5, 1);
	//Attack
	_img_left_attack->init("resource/image/Monster/minotaurs_attack_left.bmp",
		392 * 2, 50 * 2, 7, 1, true, RGB(255, 0, 255));
	_img_left_attack->set_frameSection(2, 6, 4, 30, 1, 3, 0, 20, 1);
	_img_right_attack->init("resource/image/Monster/minotaurs_attack_right.bmp",
		392 * 2, 50 * 2, 7, 1, true, RGB(255, 0, 255));
	_img_right_attack->set_frameSection(2, 0, 2, 30, 1, 3, 6, 20, 1);
	//Dash
	_img_left_dash->init("resource/image/Monster/minotaurs_charge_left.bmp",
		448 * 2, 50 * 2, 8, 1, true, RGB(255, 0, 255));
	_img_left_dash->set_frameSection(3, 0, 2, 10, 1, 3, 3, 10, 1, 4, 7, 10, 1);
	_img_right_dash->init("resource/image/Monster/minotaurs_charge_right.bmp",
		448 * 2, 50 * 2, 8, 1, true, RGB(255, 0, 255));
	_img_right_dash->set_frameSection(3, 7, 5, 10, 1, 4, 4, 10, 1, 3, 0, 10, 1);
	//Dust
	_img_left_dash_dust->init("resource/image/Monster/DashDust_left.bmp",
		80 * 5, 16 * 5, 5, 1, true, RGB(255, 0, 255));
	_img_left_dash_dust->set_frameSection(1, 0, 4, 5, 1);
	_img_right_dash_dust->init("resource/image/Monster/DashDust_right.bmp",
		80 * 5, 16 * 5, 5, 1, true, RGB(255, 0, 255));
	_img_right_dash_dust->set_frameSection(1, 4, 0, 5, 1);
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
	SOUNDMANAGER->addSound("Hit_monster", "resource/sound/effect/hitMonster.wav", true, true);
	SOUNDMANAGER->addSound("die", "resource/sound/enemy/monsterDie.wav", true, true);
	_bDebug = false;
	return S_OK;
}
void Minotaurs::release()
{
	_img_left_idle->release();
	_img_right_idle->release();
	_img_left_attack->release();
	_img_right_attack->release();
	_img_left_dash->release();
	_img_right_dash->release();
	_img_left_dash_dust->release();
	_img_right_dash_dust->release();
	_img_deadEffect->release();
	_img_damageEffect->release();
	_img_lifeBack->release();
	_img_lifeBar->release();
	SAFE_DELETE(_img_left_idle);
	SAFE_DELETE(_img_right_idle);
	SAFE_DELETE(_img_left_attack);
	SAFE_DELETE(_img_right_attack);
	SAFE_DELETE(_img_left_dash);
	SAFE_DELETE(_img_right_dash);
	SAFE_DELETE(_img_left_dash_dust);
	SAFE_DELETE(_img_right_dash_dust);
	SAFE_DELETE(_img_deadEffect);
	SAFE_DELETE(_img_damageEffect);
	SAFE_DELETE(_img_lifeBack);
	SAFE_DELETE(_img_lifeBar);
}
void Minotaurs::update()
{
	if (_counter_DeadEffect == 30)
	{
		findPlayer();
		chasePlayer_minotaurs();
		damage_effect();
		dash_minotaurs();
		compareAttack_minotaurs();
		attack_minotaurs();
		//attack
		if (_img_left_attack->getFrameX() == 3 && _cooldown_swing_sword < _speed_swing_sword - 30)
		{
			_bAttackStart = true;
		}
		if (_img_right_attack->getFrameX() == 3 && _cooldown_swing_sword < _speed_swing_sword - 30)
		{
			_bAttackStart = true;
		}
		if (_img_left_attack->getFrameX() == 0 && _bShow_left == true && _bDash == false)
		{
			_cooldown_swing_sword = 0;
		}
		if (_img_right_attack->getFrameX() == 6 && _bShow_left == false && _bDash == false)
		{
			_cooldown_swing_sword = 0;
		}
		if (_bSwing_sword == true && _cooldown_swing_sword == _speed_swing_sword)
		{
			_img_left_attack->setFrameX(6);
			_img_right_attack->setFrameX(0);
		}
		if (_bSwing_sword == true && _cooldown_swing_sword < _speed_swing_sword && _cooldown_swing_sword > _speed_swing_sword - 30)
		{
			_img_left_attack->set_breakFrame(4);
			_img_right_attack->set_breakFrame(2);
		}
		if (_bSwing_sword == true && _cooldown_swing_sword < _speed_swing_sword && _cooldown_swing_sword < _speed_swing_sword - 30)
		{
			_img_left_attack->set_breakFrame();
			_img_right_attack->set_breakFrame();
		}
		//dash
		if (_cooldown_recharge != _speed_recharge && _cooldown_recharge != 0)
		{
			_img_left_dash->set_breakFrame(2);
			_img_right_dash->set_breakFrame(5);
		}
		if (_bDash == true && _cooldown_recharge == 0 && _counter_dash >= _speed_dash - 80)
		{
			_img_left_dash->set_breakFrame(3);
			_img_right_dash->set_breakFrame(4);
		}
		if (_counter_dash == _speed_dash - 80)
		{
			_img_left_dash->set_breakFrame();
			_img_right_dash->set_breakFrame();
		}
		if (_img_right_dash->getFrameX() == 7)
		{
			_counter_dash = 0;
		}
		if (_img_left_dash->getFrameX() == 0)
		{
			_counter_dash = 0;
		}
	}
	dead_monster();
	dead_effect();
	//image Update
	_img_left_idle->frameUpdate(true);
	_img_right_idle->frameUpdate(true);
	_img_left_attack->frameUpdate(false,true);
	_img_right_attack->frameUpdate(false, false);
	_img_left_dash->frameUpdate(false, false);
	_img_right_dash->frameUpdate(false, true);
	_img_left_dash_dust->frameUpdate(true, true);
	_img_right_dash_dust->frameUpdate(true);
	_img_deadEffect->frameUpdate(true);
	_img_damageEffect->frameUpdate(true);
}
void Minotaurs::render()
{
	if (_counter_DeadEffect == 30)
	{
		//Idle
		if (_bShow_left == true && _cooldown_attack != 0 && _bDash == false)
		{
			_img_left_idle->frameRender(getMemDC(), _size_monster_rc.left - 34, _size_monster_rc.top - 10);
		}
		if (_bShow_left == false && _cooldown_attack != 0 && _bDash == false)
		{
			_img_right_idle->frameRender(getMemDC(), _size_monster_rc.left + 2, _size_monster_rc.top - 10);
		}
		//Attack
		if (_bShow_left == true && _bSwing_sword == true)
		{
			_img_left_attack->frameRender(getMemDC(), _size_monster_rc.left - 34, _size_monster_rc.top - 10);
		}
		if (_bShow_left == false && _bSwing_sword == true)
		{
			_img_right_attack->frameRender(getMemDC(), _size_monster_rc.left + 2, _size_monster_rc.top - 10);
		}
		//Dash
		if (_bShow_left == true && _bDash == true)
		{
			_img_left_dash->frameRender(getMemDC(), _size_monster_rc.left - 34, _size_monster_rc.top - 10);
		}
		if (_bShow_left == false && _bDash == true)
		{
			_img_right_dash->frameRender(getMemDC(), _size_monster_rc.left + 2, _size_monster_rc.top - 10);
		}
		//Dust
		if (_bShow_left == true && _bDash == true && _cooldown_recharge == 0 && _counter_dash >= _speed_dash - 80)
		{
			_img_left_dash_dust->frameRender(getMemDC(), _size_monster_rc.left - 44, _size_monster_rc.bottom - 70);
		}
		if (_bShow_left == false && _bDash == true && _cooldown_recharge == 0 && _counter_dash >= _speed_dash - 80)
		{
			_img_right_dash_dust->frameRender(getMemDC(), _size_monster_rc.left + 32, _size_monster_rc.bottom - 70);
		}
		if (_bShow_left == true && _bDash == true && _cooldown_recharge == 0 && _counter_dash >= _speed_dash - 80)
		{
			_img_left_dash_dust->frameRender(getMemDC(), _size_monster_rc.left + 4, _size_monster_rc.bottom - 70);
		}
		if (_bShow_left == false && _bDash == true && _cooldown_recharge == 0 && _counter_dash >= _speed_dash - 80)
		{
			_img_right_dash_dust->frameRender(getMemDC(), _size_monster_rc.left - 22, _size_monster_rc.bottom - 70);
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
			_img_damageEffect->frameRender(getMemDC(), _size_monster_rc.left + 20, _size_monster_rc.top + 20);
		}
	}
	if (_counter_DeadEffect != 30)
	{
		_img_deadEffect->frameRender(getMemDC(), _size_monster_rc.left - 32, _size_monster_rc.top - 32);
	}
}
