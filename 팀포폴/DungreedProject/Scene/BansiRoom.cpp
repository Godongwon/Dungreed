#include "stdafx.h"
#include "BansiRoom.h"
#include"Object/Unit/player/Player.h"
void BansiRoom::beliarAppear()
{
	if (countBeliarAppear != 0)
	{
		countBeliarAppear -= 1;
	}

	if (countBeliarAppear == 180)
	{
		SOUNDMANAGER->play("보스웃음");
	}

	if (countBeliarAppear == 0)
	{
		SOUNDMANAGER->stop("보스웃음");
	}
}
BansiRoom::BansiRoom()
{
}


BansiRoom::~BansiRoom()
{
}

HRESULT BansiRoom::init()
{
	gameNode::init(true);
	 
	_backGroundImg = new image;
	_backGroundImg ->init("resource/image/배경/stage3.bmp",1998/2,1328/2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerBackGround1", "resource/image/플레이어/stage3(플레이어용).bmp", (int)(1998 / 2), 1328 / 2, true, RGB(255, 0, 255));
	_stage = new stage;
	_stage -> init();
	_ui = new UI;
	_ui->init();
	_monsterControl = new MonsterControl;
	_monsterControl->init();
	MISSILECONTROL->init();

	//SOUNDMANAGER->addSound("보스", "resource/sound/back/boss.wav", true, true);
	//SOUNDMANAGER->play("보스");
	SOUNDMANAGER->addSound("보스웃음", "resource/sound/enemy/bossLaughter.wav", true, true);
	_blackOut = new image;
	_bossName = new image;
	_blackOut->init("resource/image/Boss/blackOut.bmp", 1024,600, true, RGB(255, 0, 255));
	_bossName->init("resource/image/Boss/belierName.bmp", 100, 65,true, RGB(255, 0, 255));



	PLAYER->init();
	PLAYER->del_playerBackGround();
	PLAYER->set_playerBackGround(IMAGEMANAGER->findImage("playerBackGround1"));
	PLAYER->stage_Make(BANSI_ROOM);

	//MonsterCreate
	_monsterControl->init_Boss();
	return S_OK;
}

void BansiRoom::release()
{
	IMAGEMANAGER->deleteImage("playerBackGround1");
	SAFE_DELETE(_blackOut);
	SAFE_DELETE(_bossName);
	//_blackOut->release();
	//_bossName->release();

	_backGroundImg->release();
	_monsterControl->release();
	_monsterControl = nullptr;
}

void BansiRoom::update()
{
	beliarAppear();
	PLAYER->update();
	_ui->update();
	_monsterControl->update();
	MISSILECONTROL->update();
} 

void BansiRoom::render()
{
	_backGroundImg->render(getMemDC());

	if (countBeliarAppear < 180 && countBeliarAppear !=0)
	{
		_blackOut->render(CAMERAMANAGER->getCameraDC(), 0, 0, 1024, 600);
		_bossName->render(CAMERAMANAGER->getCameraDC(), 120, 450, 100, 65);
	}
	
	//Rectangle(getMemDC(), _stage->getGroud().left, _stage->getGroud().top, _stage->getGroud().right, _stage->getGroud().bottom);
	PLAYER->render();
	_ui->render();
	_monsterControl->render();
	MISSILECONTROL->render();

	
	
	
}
