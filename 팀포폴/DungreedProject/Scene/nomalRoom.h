#pragma once
#include "Scene/Scene.h"
#include "Object/Unit/stage.h"
#include "UI/UI.h"
#include"Object/Unit/Monster/MonsterControl.h"
 
class nomalRoom : public Scene
{
private:
	UI* _ui;
	stage* _stage;

	image* _backGroundimg;
	RECT _potal;

	MonsterControl * _monsterControl;
public:
	nomalRoom();
	~nomalRoom();

	virtual  HRESULT init();
	virtual  void release();
	virtual  void update();
	virtual  void render();

};

