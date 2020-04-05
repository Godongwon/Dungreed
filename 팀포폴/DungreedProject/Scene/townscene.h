#pragma once
//#include"base/gameNode.h"
#include "Scene/Scene.h"
#include"Object/Unit/stage.h"
#include"Object/Unit/Monster/MonsterControl.h"
#include"Object/Missile/MissileControl.h"
#include "Object/Unit/NPC/weaponNpc.h"
#include "UI/townBackGround.h"

class townScene : public Scene
{
private :
	stage * _stage;
	MonsterControl * _monsterControl;
	MissileControl * _missileControl;
	townBackGround* _townBackGround;
	weaponNpc* _weaponNpc;
	RECT _backGroud;
	
	image* _backGroudimg;
//===========================던전 입구용 변수들 ==============================
private:
	image* _DungeonstanceImg;
	RECT _DungeonRC;
	RECT _DungeonstanceRC;
	bool b_isDungeonstance;
	bool b_isDoorOpen = true;
	int _DungeonstanceCount = 0;
private:
	image * _statusNpc;
	RECT _rcStatusNpc;
	image * _statusBuilding;
	
	image * _statusCase[5];
	RECT _rcstatusCase[5];

	image * _imgstatusShopRedBox[3];
	image * _imgstatusShopMintBox[3];
	image * _imgstatusShopWhiteBox[3];
	image * _imgstatusShopGoldBox[3];
	image * _imgstatusShopGrayBox[3];

	RECT _statusShopRedBox;
	RECT _statusShopMintBox;
	RECT _statusShopWhiteBox;
	RECT _statusShopGoldBox;
	RECT _statusShopGrayBox;
protected:
	void init_DungeonEntrance();
	void delete_DungeonEntrance();
	void update_DungeonEntrance();
	void draw_DungeonEntrance();
public:
	townScene();
	~townScene();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳5
	virtual void render(/*HDC hdc*/);//그리는곳

	void statusNpc();
	//void statusinit();
	void statusrelease();
	void statusupdate();
	void statusrender();

	RECT getbackGroud() {return _backGroud;}

};

