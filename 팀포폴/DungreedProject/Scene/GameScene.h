#pragma once
#include "base/gameNode.h"
#include "Scene/townScene.h"
#include "Scene/startscene.h"
#include "Scene/DungeonEntrance.h"
#include "Scene/nomalRoom.h"
#include "Scene/minoRoom.h"
#include "Scene/BansiRoom.h"

// ������ ���� ���� �������
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

