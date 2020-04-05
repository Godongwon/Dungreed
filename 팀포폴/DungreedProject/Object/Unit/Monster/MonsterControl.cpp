#include "stdafx.h"
#include "MonsterControl.h"
#include "Object/Unit/player/Player.h"
void MonsterControl::init_monsters_ground(MONSTER_TYPE type,int locateX)
{
	Monster * monster = nullptr;
	switch (type)
	{
//==	==		==		==		==		==		==		==
//==					MELEE		GROUND				==
//==	==		==		==		==		==		==		==
	case SKELETON_WORRIOR_BIG:
		monster = new Skeleton_warrior;
		break;
	case SKELETON_WORRIOR_ONEHAND:
		monster = new Skeleton_warrior_onehand;
		break;
	case SKELETON_WORRIOR_TWOHAND:
		monster = new Skeleton_warrior_twohand;
		break;
	case SKELETON_DOG:
		monster = new Skeleton_dog;
		break;
	case MINOTAURS:
		monster = new Minotaurs;
		break;	
//==	==		==		==		==		==		==		==
//==					RANGE	GROUND					==
//==	==		==		==		==		==		==		==
	case SKELETON_ARCHER:
		monster = new Skeleton_archer;
		break;
	}
	monster->init();
	monster->init_monster_spawnLocateGround(locateX);
	monster->init_chk_distance_player_rc();
	monster->init_attack_distance_rc_left();
	monster->init_attack_distance_rc_right();
	_monsters.push_back(monster);
	monster = nullptr;
}
void MonsterControl::init_monsters_air(MONSTER_TYPE type, int locateX, int locateY)
{
	Monster * monster = nullptr;
	switch (type)
	{
	//==	==		==		==		==		==		==		==
	//==					MELEE		AIR					==
	//==	==		==		==		==		==		==		==
	case GHOST:
		monster = new Ghost;
		break;
	//==	==		==		==		==		==		==		==
	//==					RANGE	AIR						==
	//==	==		==		==		==		==		==		==	

	case BAT_SMALL_NEUTRAL:
		monster = new Bat_small_neutral;
		break;
	case BANSHEE:
		monster = new Banshee;
		break;
	case BAT_SMALL:
		monster = new Bat_small;
		break;
	case BAT_BIG_PURPLE:
		monster = new Bat_big_purple;
		break;
	case BAT_BIG_RED:
		monster = new Bat_big_red;
		break;
	}
	monster->init();
	monster->init_monster_spawnLocateAir(locateX, locateY);
	monster->init_chk_distance_player_rc();
	monster->init_attack_distance_rc_left();
	monster->init_attack_distance_rc_right();
	_monsters.push_back(monster);
	monster = nullptr;
}
void MonsterControl::init_Boss()
{
	Monster * monster = nullptr;
	monster = new Beliar;
	monster->init();
	monster->init_beliar();
	_monsters.push_back(monster);
	monster = nullptr;
}
void MonsterControl::delete_monsters()
{
	_monstersIter = _monsters.begin();
	for (; _monstersIter != _monsters.end();)
	{
		if ((*_monstersIter)->get_dead_monster() == true)
		{
			_monstersIter = _monsters.erase(_monstersIter);
		}
		else { _monstersIter++; }
	}
}
void MonsterControl::update_monsters()
{
	_monstersIter = _monsters.begin();
	for (; _monstersIter != _monsters.end(); _monstersIter++)
	{
		(*_monstersIter)->update();
	}
}
//============================================================
//==					R E N D E R							==
//============================================================
void MonsterControl::draw_monsters()
{
	_monstersIter = _monsters.begin();
	for (; _monstersIter != _monsters.end(); _monstersIter++)
	{
		(*_monstersIter)->show_rc();
		(*_monstersIter)->render();		
	}
}
void MonsterControl::release_monsters()
{
	_monstersIter = _monsters.begin();
	for (; _monstersIter != _monsters.end();)
	{
		(*_monstersIter)->release();
		_monstersIter = _monsters.erase(_monstersIter);
	}
	swap(_monsters, vMonster());
}
//============================================================
//==						T E S T							==
//============================================================
void MonsterControl::show_monsterCreateList()
{	
	SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(0, 255, 255));
	char str[128];

	if (show_CreateList == false)
	{
		char str[128];
		wsprintf(str, " |Cntl + C | : 소환 목록 펼치기 ");
		TextOut(CAMERAMANAGER->getCameraDC(),0, 120, str, strlen(str));		
	}
	if (show_CreateList == true)
	{
		char str[128];
		wsprintf(str, " |Cntl + C | : 소환 목록 닫기");
		TextOut(CAMERAMANAGER->getCameraDC(), 0, 120, str, strlen(str));		
		wsprintf(str, " |Cntl + 'Q' | : SKELETON_WORRIOR_BIG");
		TextOut(CAMERAMANAGER->getCameraDC(),0, 140, str, strlen(str));		
		wsprintf(str, " |Cntl + 'W' | : SKELETON_WORRIOR_ONEHAND");
		TextOut(CAMERAMANAGER->getCameraDC(), 0, 160, str, strlen(str));		
		wsprintf(str, " |Cntl + 'E' | : SKELETON_WORRIOR_TWOHAND");
		TextOut(CAMERAMANAGER->getCameraDC(), 0, 180, str, strlen(str));		
		wsprintf(str, " |Cntl + 'R' | : SKELETON_DOG");
		TextOut(CAMERAMANAGER->getCameraDC(), 0, 200, str, strlen(str));		
		wsprintf(str, " |Cntl + 'T' | : SKELETON_ARCHER ");
		TextOut(CAMERAMANAGER->getCameraDC(), 0, 220, str, strlen(str));
		wsprintf(str, " |Cntl + 'Y' | : MINOTAURS");
		TextOut(CAMERAMANAGER->getCameraDC(), 0, 240, str, strlen(str));
		wsprintf(str, " |Cntl + 'U' | : GHOST");
		TextOut(CAMERAMANAGER->getCameraDC(), 0, 260, str, strlen(str));
		wsprintf(str, " |Cntl + 'I' | : BANSHEE ");
		TextOut(CAMERAMANAGER->getCameraDC(), 0, 280, str, strlen(str));
		wsprintf(str, " |Cntl + 'O' | : BAT_SMALL ");
		TextOut(CAMERAMANAGER->getCameraDC(), 0, 300, str, strlen(str));		
		wsprintf(str, " |Cntl + 'P' | : BAT_BIG_PURPLE ");
		TextOut(CAMERAMANAGER->getCameraDC(), 0, 320, str, strlen(str));
		wsprintf(str, " |Cntl + 'A' | : BAT_BIG_RED  ");
		TextOut(CAMERAMANAGER->getCameraDC(), 0, 340, str, strlen(str));
		wsprintf(str, " |Cntl + 'S' | : BAT_SMALL_NEUTRAL");
		TextOut(CAMERAMANAGER->getCameraDC(), 0, 360, str, strlen(str));
		for (int i = 0; i < _monsters.size(); i++)
		{
			char str[128];
			wsprintf(str, "%d", _monsters[i]->get_hp());
			TextOut(getMemDC(), _monsters[i]->get_rc().right, _monsters[i]->get_rc().top - 10, str, strlen(str));
		}
	}
	SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(0, 0, 0));
}
void MonsterControl::create_monsters()
{
	if (KEYMANAGER->isStayKeyDown(VK_CONTROL))
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (show_CreateList == true)
			{
				show_CreateList = false;
			}
			else show_CreateList = true;			
		}

		if (KEYMANAGER->isOnceKeyUp('Q'))
		{	
			init_monsters_ground(SKELETON_WORRIOR_BIG, 1000);

		}
		if (KEYMANAGER->isOnceKeyUp('W'))
		{
			init_monsters_ground(SKELETON_WORRIOR_ONEHAND , 1000);
		}
		if (KEYMANAGER->isOnceKeyUp('E'))
		{
			init_monsters_ground(SKELETON_WORRIOR_TWOHAND , 1000);
		}
		if (KEYMANAGER->isOnceKeyUp('R'))
		{
			init_monsters_ground(SKELETON_DOG , 1000);
		}
		if (KEYMANAGER->isOnceKeyUp('T'))
		{
			init_monsters_ground(SKELETON_ARCHER , 1000);
		}
		if (KEYMANAGER->isOnceKeyUp('Y'))
		{
			init_monsters_ground(MINOTAURS , 1000);
		}


		if (KEYMANAGER->isOnceKeyUp('U'))
		{
			init_monsters_air(GHOST , 1000 , 100);
		}
		if (KEYMANAGER->isOnceKeyUp('I'))
		{
			init_monsters_air(BANSHEE , 1000, 100);
		}
		if (KEYMANAGER->isOnceKeyUp('O'))
		{
			init_monsters_air(BAT_SMALL , 1000, 100);
		}
		if (KEYMANAGER->isOnceKeyUp('P'))
		{
			init_monsters_air(BAT_BIG_PURPLE , 1000, 100);
		}
		if (KEYMANAGER->isOnceKeyUp('A'))
		{
			init_monsters_air(BAT_BIG_RED , 1000, 100);
		}
		if (KEYMANAGER->isOnceKeyUp('S'))
		{
			init_monsters_air(BAT_SMALL_NEUTRAL , 1000, 100);
		}

		if (KEYMANAGER->isOnceKeyUp('D'))
		{
			init_Boss();
		}
	}
}
void MonsterControl::kill_monsters()
{
	if (KEYMANAGER->isStayKeyDown(VK_CONTROL))
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			_monstersIter = _monsters.begin();
			for (; _monstersIter != _monsters.end();)
			{
				(*_monstersIter)->set_hp(0);
				_monstersIter++;
			}
		}
	}
}
void MonsterControl::player_Atk()
{
	RECT temp;
	if (PLAYER->get_isAtk())
	{
		for (int i=0;i< _monsters.size();i++)
		{
			for (int j = 0; j < 8; j++)
			{
				temp = PLAYER->get_Player_ATK(j).player_AtkRC;
				if (IntersectRect(&RECT(), &temp, &_monsters[i]->get_rc()))
 				{
					_monsters[i]->set_hp(_monsters[i]->get_hp() - PLAYER->get_playerAtkNum());
					PLAYER->set_isAtk(false);
					break;
				}
			}
		}
	}
}
//============================================================
//==				D E F A U L T   B A S E					==
//============================================================
MonsterControl::MonsterControl()
{
}
MonsterControl::~MonsterControl()
{
}
HRESULT MonsterControl::init()
{	
	return S_OK;
}
void MonsterControl::release()
{
	release_monsters();
}
void MonsterControl::update()
{
	create_monsters();
	kill_monsters();
	player_Atk();
	delete_monsters();
	update_monsters();
}
void MonsterControl::render()
{
	show_monsterCreateList();
	draw_monsters();
}