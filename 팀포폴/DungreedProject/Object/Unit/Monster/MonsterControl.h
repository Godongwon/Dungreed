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
	void delete_monsters();						//���� ü�� 0�̸� ������
	void draw_monsters();						//�׸���
	void release_monsters();					//������
	void update_monsters();						//������Ʈ


public:
	void init_monsters_ground(MONSTER_TYPE type, int locateX);		//���� ����
	void init_monsters_air(MONSTER_TYPE type, int locateX, int locateY);		//���� ����
	//�׽�Ʈ�릤
	bool show_CreateList = false;
	void show_monsterCreateList();				//���� ��� ���̱�
	void create_monsters();						//���� ����
	void kill_monsters();						//���� HP 0 ���� �����
	void player_Atk();							//�÷��̾� ����
	void init_Boss();
//�׽�Ʈ�릥
public:
	MonsterControl();
	~MonsterControl();
	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};





