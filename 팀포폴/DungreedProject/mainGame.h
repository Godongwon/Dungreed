#pragma once
#include "base/gameNode.h"
#include "Scene/GameScene.h"

class mainGame : public gameNode
{
private:
	GameScene * _game;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
};

