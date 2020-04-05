#pragma once
#include "Object/Unit/stage.h"
#include "Scene/Scene.h"
#include "UI/UI.h"
#include"Object/Unit/Monster/MonsterControl.h"
class BansiRoom : public Scene
{
private:
	UI* _ui;
	stage* _stage;
	image* _backGroundImg;
	MonsterControl * _monsterControl;

	int countBeliarAppear = 200;
	image* _blackOut;
	image* _bossName;
	void beliarAppear();
public:
	BansiRoom();
	~BansiRoom();

	virtual  HRESULT init();
	virtual  void release();
	virtual  void update();
	virtual  void render();
};

