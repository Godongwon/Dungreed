#pragma once
#include "Scene/Scene.h"
#include"Object/Unit/stage.h"
#include "UI/UI.h"
#include"Object/Unit/Monster/MonsterControl.h"
class minoRoom : public Scene
{
private:
	UI* _ui;
	stage* _stage;

	image* _backGroundImg;
	RECT _potal;

	bool intoBoss;
	MonsterControl * _monsterControl;
public:
	minoRoom();
	~minoRoom();


	virtual  HRESULT init();
	virtual  void release();
	virtual  void update();
	virtual  void render();


};

