#include "stdafx.h"
#include "nomalRoom.h"
#include "Object/Unit/player/Player.h"

nomalRoom::nomalRoom()
{
}


nomalRoom::~nomalRoom()
{
}

HRESULT nomalRoom::init()
{

	gameNode::init(true);

	IMAGEMANAGER->addImage("nomalRoom", "resource/image/배경/stage1.bmp", 2781 / 2, 1071 / 2, true, RGB(255, 0, 255));
	_backGroundimg = IMAGEMANAGER->findImage("nomalRoom");
	
	SOUNDMANAGER->addSound("던전사운드", "resource/sound/back/던전사운드.wav");
	SOUNDMANAGER->play("던전사운드");

	_stage = new stage;
	_stage->init();
	_ui = new UI;
	_ui->init();
	_potal = RectMake(2600 / 2, 492 / 2, 177 / 2, 390/2);
	_monsterControl = new MonsterControl;
	_monsterControl->init();
	MISSILECONTROL->init();

	PLAYER->init();
	PLAYER->del_playerBackGround();
	PLAYER->set_playerBackGround(IMAGEMANAGER->findImage("nomalRoom"));
	PLAYER->stage_Make(NOMAL_ROOM);



	//MonsterCreate
	_monsterControl->init_monsters_ground(SKELETON_WORRIOR_BIG, 100);
	_monsterControl->init_monsters_ground(SKELETON_WORRIOR_ONEHAND, 800);
	_monsterControl->init_monsters_ground(SKELETON_WORRIOR_TWOHAND, 1200);
	_monsterControl->init_monsters_ground(SKELETON_ARCHER, 1000);
	//_monsterControl->init_monsters_air(BANSHEE, 300, 300);

	return S_OK;
}

void nomalRoom::release()
{
	IMAGEMANAGER->deleteImage("nomalRoom");
	_monsterControl->release();
	_monsterControl = nullptr;
}

void nomalRoom::update()
{
	RECT temp;
	if (IntersectRect(&temp, &PLAYER->get_playerRC(), &_potal))
	{
		SOUNDMANAGER->stop("던전사운드");
		SCENEMANAGER->changeScene("minoRoom");	
	}
	else
	{
		
		PLAYER->update();
		_ui->update();
		_monsterControl->update();
		MISSILECONTROL->update();
	}
}

void nomalRoom::render()
{
	_backGroundimg->render(getMemDC());
	//Rectangle(getMemDC(), _stage->getGroud().left, _stage->getGroud().top, _stage->getGroud().right, _stage->getGroud().bottom);
	//Rectangle(getMemDC(), _potal.left, _potal.top, _potal.right, _potal.bottom);
	PLAYER->render();
	_ui->render();
	_monsterControl->render();
	MISSILECONTROL->render();

}
