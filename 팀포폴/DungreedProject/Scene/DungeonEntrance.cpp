#include "stdafx.h"
#include "DungeonEntrance.h"

DungeonEntrance::DungeonEntrance()
{
}

DungeonEntrance::~DungeonEntrance()
{
}

HRESULT DungeonEntrance::init()
{
	_imgdungeonEntrance = new image;
	_imgdungeonEntrance->init("resource/image/배경/testBackGround.bmp",2048,600,true,RGB(255,0,255));
	CAMERAMANAGER->setCameraCenter(PointMake(WINSIZEX / 2, WINSIZEY / 2));
	//SOUNDMANAGER->stop("던전입장");
	//SOUNDMANAGER->addSound("던전", "resource/sound/back/던전사운드.wav", true, true);
	//SOUNDMANAGER->play("던전");
	//PLAYER->init();
	return S_OK;
}

void DungeonEntrance::release()
{
	_imgdungeonEntrance->release();
	_imgdungeonEntrance = nullptr;
}

void DungeonEntrance::update()
{
	//PLAYER->update();
}

void DungeonEntrance::render()
{
	_imgdungeonEntrance->render(getMemDC(),0,0);
	//PLAYER->render();
}