#pragma once
#include "base/gameNode.h"
#include "Object/Unit/player/Player.h"
#include "Scene/Scene.h"

class DungeonEntrance : public Scene
{
private:
	image * _imgdungeonEntrance;
public:
	DungeonEntrance();
	~DungeonEntrance();

	virtual  HRESULT init();
	virtual  void release();
	virtual  void update();
	virtual  void render();
};

