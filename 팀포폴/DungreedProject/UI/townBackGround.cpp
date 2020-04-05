#include "stdafx.h"
#include "townBackGround.h"
#include"Object/Unit/player/Player.h"
//마을 x크기 :2100
//마을 y크기 :256
townBackGround::townBackGround()
{
}

townBackGround::~townBackGround()
{
}
 
HRESULT townBackGround::init()
{
	//townBackGround = new image;
	//townBackGround = IMAGEMANAGER->addImage("townBackGround", "resource/image/town/townBackGround.bmp",2100, WINSIZEY *2 ,true,RGB(255,0,255));
	_imgback = new image;
	_imgback = IMAGEMANAGER->addImage("_imgback","resource/image/town/Sky_Day02.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_imgmiddle = new image;
	_imgmiddle = IMAGEMANAGER->addImage("_imgmiddle", "resource/image/town/TownBG_Day.bmp", 1300, WINSIZEY , true, RGB(255, 0, 255));
	_imgforward = new image;
	_imgforward = IMAGEMANAGER->addImage("imgforward", "resource/image/town/TownLayer_Day.bmp", 1400,WINSIZEY, true, RGB(255, 0, 255));
	_imgbrokenFloor = new image;
	_imgbrokenFloor = IMAGEMANAGER->addImage("_imgbrokenFloor", "resource/image/town/brokenSecondFloor.bmp", 656, 128, true, RGB(255, 0, 255));
	
	_rcTownBackGround = RectMakeCenter(WINSIZEX, WINSIZEY, 2100, 1200);

	return S_OK;
}

void townBackGround::release()
{
	_imgforward->release();
	_imgforward = nullptr;
	_imgmiddle->release();
	_imgmiddle = nullptr;
	_imgback->release();
	_imgback = nullptr;
//	townBackGround->release();
//	townBackGround = nullptr;
}
void townBackGround::update()
{
}

void townBackGround::render()
{
    
	_imgback->render(getMemDC(), PLAYER->get_playerBackGround().left, PLAYER->get_playerBackGround().top);
	_imgmiddle->render(getMemDC(), PLAYER->get_playerBackGround().left, PLAYER->get_playerBackGround().top);
	_imgforward->render(getMemDC(), PLAYER->get_playerBackGround().left, PLAYER->get_playerBackGround().top);

	//_number->frameRender(getMemDC(), 0, 0);
	
	//Rectangle(getMemDC(), _PlayerBackHpBar.left, _PlayerBackHpBar.top, _PlayerBackHpBar.right, _PlayerBackHpBar.bottom);
	//Rectangle(getMemDC(), _PlayerHpBar.left, _PlayerHpBar.top, _PlayerHpBar.right, _PlayerHpBar.bottom);
	//Rectangle(getMemDC(), _testrc.left,  _testrc.top,  _testrc.right , _testrc.bottom);
}