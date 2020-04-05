#pragma once
#include "base/gameNode.h"
#include "Scene/townScene.h"
#include "Scene/startscene.h"
#include "Scene/DungeonEntrance.h"
#include "Scene/nomalRoom.h"
#include "Scene/minoRoom.h"
#include "Scene/BansiRoom.h"

// 맵툴을 쓰기 위한 헤더파일
#include "Maptool/Maptool.h"
class GameScene
{
public:
	GameScene();
	~GameScene();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
};

