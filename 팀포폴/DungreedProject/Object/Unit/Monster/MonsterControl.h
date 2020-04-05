#pragma once
#include "Object/Unit/Monster/Melee/Skeleton_warrior.h"
#include "Object/Unit/Monster/Melee/Skeleton_warrior_onehand.h"
#include "Object/Unit/Monster/Melee/Skeleton_warrior_twohand.h"
#include "Object/Unit/Monster/Melee/Skeleton_dog.h"
#include "Object/Unit/Monster/Range/Skeleton_archer.h"
#include "Object/Unit/Monster/Melee/Minotaurs.h"
#include "Object/Unit/Monster/Melee/Ghost.h"
#include "Object/Unit/Monster/Range/Banshee.h"
#include "Object/Unit/Monster/Range/Bat_small.h"
#include "Object/Unit/Monster/Range/Bat_big_purple.h"
#include "Object/Unit/Monster/Range/Bat_big_red.h"
#include "Object/Unit/Monster/Melee/Bat_small_neutral.h"
#include "Object/Unit/Monster/Boss/Beliar.h"
class MonsterControl : public gameNode
{
private:
	typedef vector<Monster *> vMonster;
private:
	vMonster _monsters;
	vMonster::iterator _monstersIter;
protected:
	void delete_monsters();						//몬스터 체력 0이면 지워라
	void draw_monsters();						//그리기
	void release_monsters();					//릴리즈
	void update_monsters();						//업데이트


public:
	void init_monsters_ground(MONSTER_TYPE type, int locateX);		//몬스터 생성
	void init_monsters_air(MONSTER_TYPE type, int locateX, int locateY);		//몬스터 생성
	//테스트용┐
	bool show_CreateList = false;
	void show_monsterCreateList();				//생성 목록 보이기
	void create_monsters();						//몬스터 생성
	void kill_monsters();						//몬스터 HP 0 으로 만들기
	void player_Atk();							//플레이어 공격
	void init_Boss();
//테스트용┘
public:
	MonsterControl();
	~MonsterControl();
	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳
};





