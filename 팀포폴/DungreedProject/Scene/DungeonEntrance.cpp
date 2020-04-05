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
	_imgdungeonEntrance->init("resource/image/���/testBackGround.bmp",2048,600,true,RGB(255,0,255));
	CAMERAMANAGER->setCameraCenter(PointMake(WINSIZEX / 2, WINSIZEY / 2));
	//SOUNDMANAGER->stop("��������");
	//SOUNDMANAGER->addSound("����", "resource/sound/back/��������.wav", true, true);
	//SOUNDMANAGER->play("����");
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