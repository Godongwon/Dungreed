#include "stdafx.h"
#include "Beliar.h"
void Beliar::actBeliar()
{
	if (_cooldown_attack !=0)
	{
		if (_bEngage == false)
		{
			rndBeliarAct = RND->getFromIntTo(0,4);
		}
		_cooldown_attack -= 1;
	}
	if (_cooldown_attack == 0)
	{
		_bEngage = true;
		TemprndBeliarAct = rndBeliarAct;
		switch (TemprndBeliarAct)
		{
			case 0:	attackLeftArm();
				break;
			case 1:	attackRightArm();
				break;
			case 2:	attackArms();
				break;
			case 3: spawnBeliarSword();
				break;
			case 4: darkballAttack();
				break;
		}
	}
}
//====================================================================
//==							Arms				   				==
//====================================================================
void Beliar::moveLeftArm()
{
	RECT tempPlayer = PLAYER->get_playerRC();	
	int tempPlayerY = (tempPlayer.top + tempPlayer.bottom) / 2;
	int ArmY = (_beliar_leftArm_rc.top + _beliar_leftArm_rc.bottom) / 2;

	if (tempPlayerY < ArmY)
	{
		_beliar_leftArm_rc.top -= (LONG)_speedArmMove;
		_beliar_leftArm_rc.bottom -= (LONG)_speedArmMove;
		_beliar_leftArm_attack_distance_rc.top -= (LONG)_speedArmMove;
		_beliar_leftArm_attack_distance_rc.bottom -= (LONG)_speedArmMove;
	}
	else if (tempPlayerY > ArmY)
	{
		_beliar_leftArm_rc.top += (LONG)_speedArmMove;
		_beliar_leftArm_rc.bottom += (LONG)_speedArmMove;
		_beliar_leftArm_attack_distance_rc.top += (LONG)_speedArmMove;
		_beliar_leftArm_attack_distance_rc.bottom += (LONG)_speedArmMove;
	}
}
void Beliar::moveRightArm()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	int tempPlayerY = (tempPlayer.top + tempPlayer.bottom) / 2;
	int ArmY = (_beliar_rightArm_rc.top + _beliar_rightArm_rc.bottom) / 2;

	if (tempPlayerY < ArmY)
	{
		_beliar_rightArm_rc.top -= (LONG)_speedArmMove;
		_beliar_rightArm_rc.bottom -= (LONG)_speedArmMove;
		_beliar_rightArm_attack_distance_rc.top -= (LONG)_speedArmMove;
		_beliar_rightArm_attack_distance_rc.bottom -= (LONG)_speedArmMove;
	}
	else if (tempPlayerY > ArmY)
	{
		_beliar_rightArm_rc.top += (LONG)_speedArmMove;
		_beliar_rightArm_rc.bottom += (LONG)_speedArmMove;
		_beliar_rightArm_attack_distance_rc.top += (LONG)_speedArmMove;
		_beliar_rightArm_attack_distance_rc.bottom += (LONG)_speedArmMove;
	}
}
void Beliar::attackLeftArm()
{
	RECT temp;
	RECT tempPlayer = PLAYER->get_playerRC();
	int playerhp = PLAYER->get_playerHP();
	int tempPlayerY = (tempPlayer.top + tempPlayer.bottom) / 2;
	int ArmY = (_beliar_leftArm_rc.top + _beliar_leftArm_rc.bottom) / 2;
//ÆÈ ÀÌµ¿
	if (_cooldownLeftArmAttack != 0)
	{
		_cooldownLeftArmAttack -= 1;
		moveLeftArm();
		if (tempPlayerY == ArmY)
		{
			_cooldownLeftArmAttack = 5;
		}
	}
	if (_cooldownLeftArmAttack == 0)
	{
		_cooldownLeftArmCharge -= 1;	
	}
	if (_cooldownLeftArmCharge == 29)
	{
		SOUNDMANAGER->play("LaserFire");
		_img_beliarLeftArm_Laser->setFrameX(0);
	}
//Â÷Â¡
	if (_cooldownLeftArmCharge == 0)
	{
		SOUNDMANAGER->stop("LaserFire");
		if (IntersectRect(&temp, &_beliar_leftArm_attack_distance_rc, &tempPlayer))
		{
			if (_bGiveDamage == false)
			{
				playerhp -= 10;
				PLAYER->set_playerHP(playerhp);
				_bGiveDamage = true;
			}
		}
		_bGiveDamage = false;
		_cooldownLeftArmAttack = _speedLeftArmAttack;
		_cooldownLeftArmCharge = _speedLeftArmReCharge;
		_bLeftArmAttackComplete = true;

		if (_bRightArmAttackComplete == true && _bLeftArmAttackComplete == true)
		{
			_bLeftArmAttackComplete = false;
			_bRightArmAttackComplete = false;
			_cooldown_attack = _speed_attack;
			_bEngage = false;
		}
		if (TemprndBeliarAct == 0)
		{
			_bEngage = false;
			_bLeftArmAttackComplete = false;
			_cooldown_attack = _speed_attack;
		}
	}
}
void Beliar::attackRightArm()
{
	RECT temp;
	RECT tempPlayer = PLAYER->get_playerRC();
	int playerhp = PLAYER->get_playerHP();
	int tempPlayerY = (tempPlayer.top + tempPlayer.bottom) / 2;
	int ArmY = (_beliar_rightArm_rc.top + _beliar_rightArm_rc.bottom) / 2;
	//ÆÈ ÀÌµ¿
	if (_cooldownRightArmAttack !=0)
	{
		_cooldownRightArmAttack -= 1;
		moveRightArm();
		if (tempPlayerY == ArmY)
		{
			_cooldownRightArmAttack = 5;
		}
	}
	if (_cooldownRightArmAttack == 0)
	{		
		_cooldownRightArmCharge -= 1;
	}
	if (_cooldownRightArmCharge == 29)
	{
		SOUNDMANAGER->play("LaserFire");
		_img_beliarRightArm_Laser->setFrameX(14);
	}
	//Â÷Â¡
	if (_cooldownRightArmCharge == 0)
	{
		SOUNDMANAGER->stop("LaserFire");
		if (IntersectRect(&temp, &_beliar_rightArm_attack_distance_rc, &tempPlayer))
		{
			if (_bGiveDamage == false)
			{
				playerhp -= 10;
				PLAYER->set_playerHP(playerhp);
				_bGiveDamage = true;
			}
		}
		_bGiveDamage = false;
		_cooldownRightArmAttack = _speedRightArmAttack;
		_cooldownRightArmCharge = _speedRightArmReCharge;
		_bRightArmAttackComplete = true;

		if (TemprndBeliarAct == 1)
		{
			_bEngage = false;
			_bRightArmAttackComplete = false;
			_cooldown_attack = _speed_attack;
		}
	}
}
void Beliar::attackArms()
{
	if (_bLeftArmAttackComplete == false && _bRightArmAttackComplete == false)
	{
		attackLeftArm();
	}
	if (_bRightArmAttackComplete == false && _bLeftArmAttackComplete == true)
	{
		attackRightArm();
	}
	if (_bRightArmAttackComplete == true && _bLeftArmAttackComplete == true)
	{
		attackLeftArm();
	}
}
//====================================================================
//==					Beliar		Swords				   			==
//====================================================================
void Beliar::spawnBeliarSword()
{
	if (_counter_spawnBeliarSword != 0)
	{
		_counter_spawnBeliarSword -= 1;
	}

	_focus_changeY = -150;
	if (_counter_spawnBeliarSword == 60)
	{
		SOUNDMANAGER->play("BeliarSwordSpawn");
		_focus_changeX = -120;
		init_focusforMissile_plusVar();
		delay_BeliarSword = 100;
		_beliarSword = new BeliarSword;
		_beliarSword->init();
		_beliarSword->init_BeliarSwordInfo(_focus_forMissile, delay_BeliarSword);
		make_missile(_beliarSword);
		_beliarSword = nullptr;
	}
	if (_counter_spawnBeliarSword == 50)
	{
		SOUNDMANAGER->play("BeliarSwordSpawn");
		_focus_changeX = -60;
		init_focusforMissile_plusVar();
		delay_BeliarSword = 120;
		_beliarSword = new BeliarSword;
		_beliarSword->init();
		_beliarSword->init_BeliarSwordInfo(_focus_forMissile, delay_BeliarSword);
		make_missile(_beliarSword);
		_beliarSword = nullptr;
	}
	if (_counter_spawnBeliarSword == 40)
	{
		SOUNDMANAGER->play("BeliarSwordSpawn");
		_focus_changeX = 0;
		init_focusforMissile_plusVar();
		delay_BeliarSword = 140;
		_beliarSword = new BeliarSword;
		_beliarSword->init();
		_beliarSword->init_BeliarSwordInfo(_focus_forMissile, delay_BeliarSword);
		make_missile(_beliarSword);
		_beliarSword = nullptr;
	}
	if (_counter_spawnBeliarSword == 30)
	{
		SOUNDMANAGER->play("BeliarSwordSpawn");
		_focus_changeX = 60;
		init_focusforMissile_plusVar();
		delay_BeliarSword = 160;
		_beliarSword = new BeliarSword;
		_beliarSword->init();
		_beliarSword->init_BeliarSwordInfo(_focus_forMissile, delay_BeliarSword);
		make_missile(_beliarSword);
		_beliarSword = nullptr;
	}
	if (_counter_spawnBeliarSword == 20)
	{
		SOUNDMANAGER->play("BeliarSwordSpawn");
		_focus_changeX = 120;
		init_focusforMissile_plusVar();
		delay_BeliarSword = 180;
		_beliarSword = new BeliarSword;
		_beliarSword->init();
		_beliarSword->init_BeliarSwordInfo(_focus_forMissile, delay_BeliarSword);
		make_missile(_beliarSword);
		_beliarSword = nullptr;
	}

	if (_counter_spawnBeliarSword == 0)
	{
		SOUNDMANAGER->stop("BeliarSwordSpawn");
		_counter_spawnBeliarSword = _speedSpawnBeliarSword;
		_cooldown_attack = _speed_attack;
		_bEngage = false;
	}
}
//====================================================================
//==					Dark		ball				   			==
//====================================================================
void Beliar::darkballAttack()
{
	init_focusforMissile();
	if (_counter_spawnDarkball != 0)
	{
		_counter_spawnDarkball -= 1;
		_delay_SpawnDarkball -= 1;

		if (_delay_SpawnDarkball % 6 == 0)
		{
			_darkball = new Darkball;
			_darkball->init();
			_darkball->init_missileInfo(_focus_forMissile, 0 + _angleForDarkball);
			make_missile(_darkball);
			_darkball = nullptr;

			_darkball = new Darkball;
			_darkball->init();
			_darkball->init_missileInfo(_focus_forMissile, 1.5 + _angleForDarkball);
			make_missile(_darkball);
			_darkball = nullptr;

			_darkball = new Darkball;
			_darkball->init();
			_darkball->init_missileInfo(_focus_forMissile, 3 + _angleForDarkball);
			make_missile(_darkball);
			_darkball = nullptr;

			_darkball = new Darkball;
			_darkball->init();
			_darkball->init_missileInfo(_focus_forMissile, 4.5 + _angleForDarkball);
			make_missile(_darkball);
			_darkball = nullptr;

			_angleForDarkball += 0.15f;
			SOUNDMANAGER->play("DarkballSpawn");
		}
	}
	if (_counter_spawnDarkball == 0)
	{
		SOUNDMANAGER->stop("DarkballSpawn");
		_counter_spawnDarkball = _speedSpawnDarkball;
		_delay_SpawnDarkball = _speedDelayDarkball;
		_cooldown_attack = _speed_attack;
		_bEngage = false;
	}
}
void Beliar::dead_beliar()
{
	_img_beliar->set_breakFrame(0);
	SOUNDMANAGER->stop("LaserFire");
	SOUNDMANAGER->stop("BeliarSwordSpawn");
	SOUNDMANAGER->stop("DarkballSpawn");
	SOUNDMANAGER->stop("Hit_monster");

	init_focusforMissile();
	if (_counterDeadScene != 0)
	{
		
		_counterDeadScene -= 1;
		_rndDeadEffect = RND->getFromIntTo(0, 50);
		_rndDeadEffect_plusMinus = RND->getFromIntTo(0,50);

		_focus_forMissile.x += (_rndDeadEffect * 10) - 280;
		_focus_forMissile.y += (_rndDeadEffect_plusMinus * 10) - 280;

		_beliar_deadEffect = new Beliar_DeadEffect;
		_beliar_deadEffect->init();
		_beliar_deadEffect->init_missileInfo(_focus_forMissile,0);
		make_missile(_beliar_deadEffect);
		_beliar_deadEffect = nullptr;		

		if (_counterDeadScene >= 100 && _counterDeadScene % 15 == 0)
		{
			SOUNDMANAGER->play("BeliarDead");
		}
	}

	if (_counterDeadScene == 0)
	{
		SOUNDMANAGER->stop("BeliarDead");
		_bDead_monster = true;
	}
}
Beliar::Beliar()
{
}
Beliar::~Beliar()
{
}
HRESULT Beliar::init()
{
	//===================
	//=		·ºÆ® Å©±â	=
	//===================
	_size_monster_width = 150;
	_size_monster_height = 200;
	_beliar_Arm_width = 150;
	_beliar_Arm_height = 150;
	_beliar_Arm_attack_distance_width = 900;
	_beliar_Arm_attack_distance_height = 75;
	//===================
	//=		´É·ÂÄ¡		=
	//===================
	_hp = 1000;
	_speed_attack = 200;
	_speedArmMove = 10.0f;
	_speedLeftArmAttack = 30;
	_speedLeftArmReCharge = 30;
	_speedRightArmAttack = 30;
	_speedRightArmReCharge = 30;
	_speedSpawnBeliarSword = 70;
	_speedSpawnDarkball = 300;
	_speedDelayDarkball = 300;
	//===================
	//=		A I			=
	//===================
	_cooldownLeftArmAttack = 30;
	_cooldownLeftArmCharge = _speedLeftArmReCharge;
	 _bLeftArmAttackComplete = false;

	_cooldownRightArmAttack = 30;
	_cooldownRightArmCharge = _speedRightArmReCharge;
	_bRightArmAttackComplete = false;
	_cooldown_attack = 400;

	_counter_spawnBeliarSword = _speedSpawnBeliarSword;
	_counter_spawnDarkball = _speedSpawnDarkball;
	_delay_SpawnDarkball = _speedDelayDarkball;
	_angleForDarkball = 0;
	//===================
	//=		EFFECT		=
	//===================
	_hpTemp = 1000;
	_monsterHpBar_W = 1000;
	_bDead_monster = false;
	_counter_damageEffect = 15;
	_counterDeadScene = 350;
	//===================
	//=		ÀÌ¹ÌÁö		=
	//===================
	_img_beliar = new image;
	_img_beliarOpenMouse = new image;
	_img_beliarLeftArm_Laser = new image;
	_img_beliarRightArm_Laser = new image;
	_img_beliarLeftArm_idle = new image;
	_img_beliarRightArm_idle = new image;
	_img_beliarLaserball = new image;
	_img_beliarBodyball = new image;
	_img_bossLifeBar = new image;
	_img_bossLifeBack = new image;
	_img_damageEffect = new image;
	//Idle
	_img_beliar->init("resource/image/Boss/Beliar_body.bmp",
		1800, 275, 9, 1, true, RGB(255, 0, 255));
	_img_beliar->set_frameSection(1, 0, 8, 8, 1);
	//Attack
	_img_beliarOpenMouse->init("resource/image/Boss/Beliar_darkBall.bmp",
		1200, 325, 6, 1, true, RGB(255, 0, 255));
	_img_beliarOpenMouse->set_frameSection(1, 0, 5, 8, 1);
	//laser
	_img_beliarLeftArm_Laser->init("resource/image/Boss/Beliar_leftArm_laser.bmp",
		4545*4, 56*6, 15, 1, true, RGB(255, 0, 255));
	_img_beliarLeftArm_Laser->set_frameSection(1, 0, 14, 5, 1);
	_img_beliarRightArm_Laser->init("resource/image/Boss/Beliar_rightArm_laser.bmp",
		4545*4, 56*6, 15, 1, true, RGB(255, 0, 255));
	_img_beliarRightArm_Laser->set_frameSection(1, 14, 0, 3, 1);
	//Arms
	_img_beliarLeftArm_idle->init("resource/image/Boss/Beliar_leftArm.bmp",
		720 , 180, 4, 1, true, RGB(255, 0, 255));
	_img_beliarLeftArm_idle->set_frameSection(1, 0, 3, 15, 1);
	_img_beliarRightArm_idle->init("resource/image/Boss/Beliar_rightArm.bmp",
		720 , 180 , 4, 1, true, RGB(255, 0, 255));
	_img_beliarRightArm_idle->set_frameSection(1, 0, 3, 15, 1);
	//_img_beliarLaserball
	_img_beliarLaserball->init("resource/image/Boss/laserBall.bmp",
		100 * 8 , 20 * 8, 5, 1, true, RGB(255, 0, 255));
	_img_beliarLaserball->set_frameSection(1, 0, 4, 3, 1);
	//bodyball
	_img_beliarBodyball->init("resource/image/Boss/bodyBall.bmp",
		190 * 6, 36 * 6, 5, 1, true, RGB(255, 0, 255));
	_img_beliarBodyball->set_frameSection(1, 0, 4, 5, 1);
	//LifeBar
	_img_bossLifeBack->init("resource/image/Boss/BossLifeBack.bmp",
		125 * 2, 16 * 2, 1, 1, true, RGB(255, 0, 255));
	_img_bossLifeBar->init("resource/image/Boss/BossLifeBar.bmp",
		100 * 2, 10 * 2, 1, 1, true, RGB(255, 0, 255));
	//Damage
	_img_damageEffect->init("resource/image/Monster/damageEffect.bmp",
		126 * 2, 31 * 2, 6, 1, true, RGB(255, 0, 255));
	_img_damageEffect->set_frameSection(1, 0, 5, 5, 1);
	//Sound
	SOUNDMANAGER->addSound("DarkballSpawn", "resource/sound/enemy/Darkball.wav", true, true);
	SOUNDMANAGER->addSound("BeliarSwordSpawn", "resource/sound/enemy/BeliarSword.wav", true, true);
	SOUNDMANAGER->addSound("LaserFire", "resource/sound/enemy/Laser.wav", true, true);
	SOUNDMANAGER->addSound("BeliarDead", "resource/sound/enemy/beliarDie.wav", true, true);
	_bDebug = false;
	return S_OK;
}
void Beliar::release()
{
	_img_beliar->release();
	_img_beliarOpenMouse->release();
	_img_beliarLeftArm_idle->release();
	_img_beliarRightArm_idle->release();
	//_img_beliarLeftArm_attack->release();
	//_img_beliarRightArm_attack->release();
	_img_beliarLeftArm_Laser->release();
	_img_beliarRightArm_Laser->release();
	_img_beliarLaserball->release();
	_img_beliarBodyball->release();
	_img_bossLifeBar->release();
	_img_bossLifeBack->release();
	_img_damageEffect->release();

	SAFE_DELETE(_img_beliar);
	SAFE_DELETE(_img_beliarOpenMouse);
	SAFE_DELETE(_img_beliarLeftArm_idle);
	SAFE_DELETE(_img_beliarRightArm_idle);
	SAFE_DELETE(_img_beliarLeftArm_attack);
	SAFE_DELETE(_img_beliarRightArm_attack);
	SAFE_DELETE(_img_beliarLeftArm_Laser);
	SAFE_DELETE(_img_beliarRightArm_Laser);
	SAFE_DELETE(_img_beliarLaserball);
	SAFE_DELETE(_img_beliarBodyball);
	SAFE_DELETE(_img_bossLifeBar);
	SAFE_DELETE(_img_bossLifeBack);
	SAFE_DELETE(_img_damageEffect);
}
void Beliar::update()
{
	if (_counterDeadScene == 350)
	{
		actBeliar();
		damage_effect();
		if (TemprndBeliarAct == 4 && _counter_spawnDarkball == _speedSpawnDarkball)
		{
			_img_beliarOpenMouse->setFrameX(0);
		}
		if (_img_beliarOpenMouse->getFrameX() == 3 && _counter_spawnDarkball > 15)
		{
			_img_beliarOpenMouse->set_breakFrame(3);
		}
		if (_counter_spawnDarkball == 15)
		{
			_img_beliarOpenMouse->set_breakFrame();
		}

		if (_cooldownLeftArmAttack != _speedLeftArmAttack)
		{
			_img_beliarLeftArm_idle->set_breakFrame(0);
		}

		if (_cooldownRightArmAttack != _speedRightArmAttack)
		{
			_img_beliarRightArm_idle->set_breakFrame(2);
		}

		if (_cooldownLeftArmCharge == 1)
		{
			_img_beliarLeftArm_idle->set_breakFrame();
		}

		if (_cooldownRightArmCharge == 1)
		{
			_img_beliarRightArm_idle->set_breakFrame();
		}
	}
	if (_hp <= 0)
	{
		dead_beliar();
	}

	//image Update
	_img_beliar->frameUpdate(true , false);
	_img_beliarOpenMouse->frameUpdate(true , false);
	_img_beliarLeftArm_idle->frameUpdate(true , false);
	_img_beliarRightArm_idle->frameUpdate(true , false);
	_img_beliarLeftArm_Laser->frameUpdate(true , false);
	_img_beliarRightArm_Laser->frameUpdate(true , true);
	_img_beliarLaserball->frameUpdate(true , false);
	_img_beliarBodyball->frameUpdate(true , false);
	_img_damageEffect->frameUpdate(true);

}
void Beliar::render()
{
	_img_beliarBodyball->frameRender(getMemDC(), _size_monster_rc.left - 30, _size_monster_rc.top - 10);
	if (_counter_spawnDarkball == _speedSpawnDarkball)
	{
		_img_beliar->frameRender(getMemDC(), _size_monster_rc.left - 45, _size_monster_rc.top - 50);
	}
	if (_counter_spawnDarkball != _speedSpawnDarkball)
	{
		_img_beliarOpenMouse->frameRender(getMemDC(), _size_monster_rc.left - 45, _size_monster_rc.top - 120);
	}
	_img_beliarLeftArm_idle->frameRender(getMemDC(), _beliar_leftArm_rc.left + 10, _beliar_leftArm_rc.top - 10);
	_img_beliarRightArm_idle->frameRender(getMemDC(), _beliar_rightArm_rc.left - 50, _beliar_rightArm_rc.top - 10);
	
	if (_cooldownLeftArmCharge != _speedLeftArmReCharge)
	{
		_img_beliarLeftArm_Laser->frameRender(getMemDC(), _beliar_leftArm_attack_distance_rc.left, _beliar_leftArm_attack_distance_rc.top - 120);
	}
	if (_cooldownRightArmCharge != _speedLeftArmReCharge)
	{
		_img_beliarRightArm_Laser->frameRender(getMemDC(), _beliar_rightArm_attack_distance_rc.left - 300, _beliar_rightArm_attack_distance_rc.top - 120);
	}

	if (_cooldownLeftArmAttack != _speedLeftArmAttack)
	{
		_img_beliarLaserball->frameRender(getMemDC(), _beliar_leftArm_rc.left + 60, _beliar_leftArm_rc.top+10);
	}
	if (_cooldownRightArmAttack != _speedLeftArmAttack)
	{
		_img_beliarLaserball->frameRender(getMemDC(), _beliar_rightArm_rc.left - 60, _beliar_rightArm_rc.top+10);
	}
	//LifeBar
	_img_bossLifeBack->render(CAMERAMANAGER->getCameraDC(), _size_monster_rc.left - 80, 550,
		(int)(350), (int)(40));
	_img_bossLifeBar->render(CAMERAMANAGER->getCameraDC(),
		_size_monster_rc.left -18,557,
		(int)((_hp/_monsterHpBar_W) * 280), (int)(25));
	//DamageEffect
	if (_haveDamage == true)
	{
		_img_damageEffect->frameRender(getMemDC(), (_size_monster_rc.left + _size_monster_rc.right) / 2, 
			(_size_monster_rc.top + _size_monster_rc.bottom) / 2);
	}
}
