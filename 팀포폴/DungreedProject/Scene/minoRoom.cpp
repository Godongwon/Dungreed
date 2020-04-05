#include "stdafx.h"
#include "minoRoom.h"
#include"Object/Unit/player/Player.h"


minoRoom::minoRoom()
{
}


minoRoom::~minoRoom()
{
}

HRESULT minoRoom::init()
{
	gameNode::init(true);
	_backGroundImg = new image;
	_backGroundImg->init("resource/image/배경/stage2.bmp", 2495 / 2, 2371 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerBackGround", "resource/image/플레이어/stage2(플레이어용).bmp", 2495 / 2, 2371 / 2, true, RGB(255, 0, 255));
	_stage = new stage;
	_stage->init();
	_ui = new UI;
	_ui->init();
	_potal = RectMake(194/2,0,190,165/2);
	_monsterControl = new MonsterControl;
	_monsterControl->init();
	MISSILECONTROL->init();
	SOUNDMANAGER->stop("던전사운드");
	


	PLAYER->init();
	PLAYER->del_playerBackGround();
	PLAYER->set_playerBackGround(IMAGEMANAGER->findImage("playerBackGround"));
	PLAYER->stage_Make(MiNO_ROOM);

	_monsterControl->init_monsters_ground(SKELETON_DOG, 800);
	_monsterControl->init_monsters_ground(MINOTAURS, 100);
	_monsterControl->init_monsters_air(BANSHEE, 400, 600);
	_monsterControl->init_monsters_air(BAT_BIG_PURPLE, 1100, 150);
	_monsterControl->init_monsters_air(BAT_BIG_RED, 100, 150);
	_monsterControl->init_monsters_air(GHOST, 1100, 500);
	_monsterControl->init_monsters_air(GHOST, 1150, 500);



	return S_OK;
}

void minoRoom::release()
{
	IMAGEMANAGER->deleteImage("playerBackGround");
	_backGroundImg->release();
	_monsterControl->release();
	_monsterControl = nullptr;
}


void minoRoom::update()
{
	RECT temp;
	if (IntersectRect(&temp, &PLAYER->get_playerRC(), &_potal))
	{
		SCENEMANAGER->changeScene("BansiRoom");
	}
	else
	{
		PLAYER->update();
		_ui->update();
		_monsterControl->update();
		MISSILECONTROL->update();
	}
}

void minoRoom::render()
{
	_backGroundImg -> render(getMemDC());
	Rectangle(getMemDC(), _stage->getGroud().left, _stage->getGroud().top, _stage->getGroud().right, _stage->getGroud().bottom);
	//Rectangle(getMemDC(), _potal.left, _potal.top, _potal.right, _potal.bottom);
	PLAYER->render();
	_ui->render();
	_monsterControl->render();
	MISSILECONTROL->render();
}
