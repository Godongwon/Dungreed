#include "stdafx.h"
#include "weaponNpc.h"
#include "Object/Unit/player/Player.h"
#include "UI/UI.h"
void weaponNpc::npcWay()
{
	if (_focousNpcX > PLAYER->getplayer_FocousX())
	{
		_npcWay = NPC_WAY_LEFT;
		_npcImg = IMAGEMANAGER->findImage("weaponNPC_LEFT");
		_npcAni = IMAGEMANAGER->findAnimation("weaponNPC_LEFT");
	}
	else
	{
		_npcWay = NPC_WAY_RIGHT;
		_npcImg = IMAGEMANAGER->findImage("weaponNPC_RIGHT");
		_npcAni = IMAGEMANAGER->findAnimation("weaponNPC_RIGHT");
	}
	_npcAni->start();
}
void weaponNpc::npcTouch_IMG()
{
	if (b_touchWeaponNPC)
	{

		_touchNPCkeyImg->setFrameX(0);
	}
	else
	{
		_touchNPCkeyImg->setFrameX(1);
	}
}
void weaponNpc::npcTouch()
{
	RECT temp;
	if (IntersectRect(&temp, &_npcRC, &PLAYER->get_playerRC()))
	{
		b_touchWeaponNPC = true;
	}
	else
	{
		b_touchWeaponNPC = false;
	}
}
/////////////////////////////////////////////////
weaponNpc::weaponNpc() {}
weaponNpc::~weaponNpc() {}
/////////////////////////////////////////////////
HRESULT weaponNpc::init()
{
	_stage = new stage;
	_stage->init();
	_stage->stage_Make(TOWN_SCENE);
	

	_weaponNPCImgnum = 4;
	//////////////////////////////////////���� ���â///////////////////////////////////////////////////////////////
	IMAGEMANAGER->addImage("������â", "resource/image/weaponshop/��������޹��.bmp", 95 * _weaponNPCImgnum, 25 * _weaponNPCImgnum);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////����������Ҿ�/////////////////////////////////////////////////////////////
	IMAGEMANAGER->addFrame("weaponNPC_LEFT", "resource/image/weaponshop/weaponNPC����.bmp", 196 * _weaponNPCImgnum, 48 * _weaponNPCImgnum, 4, 1, 1);
	IMAGEMANAGER->addFrame("weaponNPC_RIGHT", "resource/image/weaponshop/weaponNPC������.bmp", 196 * _weaponNPCImgnum, 48 * _weaponNPCImgnum, 4, 1, 1);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////��ġ ���� �� �̹���//////////////////////////////////////////////////
	IMAGEMANAGER->addFrameImage("ŰE", "resource/image/weaponshop/Ű����E.bmp", 26 * _weaponNPCImgnum, 14 * _weaponNPCImgnum, 2, 1, true, RGB(255, 0, 255));
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////����â///////////////////////////////////////////////////////
	//IMAGEMANAGER->addImage("����â", "resource/image/weaponshop/����â.bmp", IMAGEMANAGER->findImage("��üâ")->getWidth()-15, 55);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	_npcWay = NPC_WAY_LEFT;
	_npcImg = IMAGEMANAGER->findImage("weaponNPC_LEFT");
	_npcAni = IMAGEMANAGER->findAnimation("weaponNPC_LEFT");
	_npcAni->start();
	_npcRC = RectMake(WINSIZEX + 200, 
		_stage->getGroud().top - (48 * _weaponNPCImgnum), 
		_npcImg->getFrameWidth(), _npcImg->getFrameHeight());

	_weaponShop = IMAGEMANAGER->findImage("������â");
	_weaponShopRC = RectMake(_npcRC.left - (_weaponShop->getHeight() + 20), _stage->getGroud().top - (25 * _weaponNPCImgnum), _weaponShop->getWidth(), _weaponShop->getHeight());

	_touchNPCkeyImg = IMAGEMANAGER->findImage("ŰE");
	_touchNPCkeyRC = RectMakeCenter(_npcRC.right - (_npcRC.right - _npcRC.left) / 2, _npcRC.top - 30, _touchNPCkeyImg->getFrameWidth(), _touchNPCkeyImg->getFrameHeight());

	//================================================================================

	b_openWeaponshop = false;
	b_touchWeaponNPC = false;
	return S_OK;
}

void weaponNpc::release()
{
	SAFE_DELETE(_stage);
	IMAGEMANAGER->deleteImage("������â");
	//IMAGEMANAGER->deleteImage("����â");
	IMAGEMANAGER->deleteImage("�۶��콺");
	IMAGEMANAGER->deleteImage("���");
	IMAGEMANAGER->deleteImage("�׵�");
	IMAGEMANAGER->deleteImage("�ܰ�");
	IMAGEMANAGER->deleteImage("�ܰ�");
	IMAGEMANAGER->deleteImage("ŰE");
	IMAGEMANAGER->deleteImage("weaponNPC_LEFT");
	IMAGEMANAGER->deleteImage("weaponNPC_RIGHT");
}

//================================================================================
//##			                   ����NPC������Ʈ                               ##
//================================================================================
void weaponNpc::update()
{
	_focousNpcX = _npcRC.right - (_npcRC.right - _npcRC.left) / 2;
	npcWay();
	npcTouch();
	npcTouch_IMG();
	_npcAni->frameUpdate((float)(0.1));

	if (b_touchWeaponNPC)
	{
		INGAME_UI->set_bOpen_weaponStore(true);
		b_openWeaponshop = true;
	}
	else
	{
		INGAME_UI->set_bOpen_weaponStore(false);
		b_openWeaponshop = false;
	}
}
void weaponNpc::render()
{
	_weaponShop->render(getMemDC(), _weaponShopRC.left, _weaponShopRC.top);
	_npcImg->aniRender(getMemDC(), _npcRC.left, _npcRC.top, _npcAni);
	_touchNPCkeyImg->frameRender(getMemDC(), _touchNPCkeyRC.left, _touchNPCkeyRC.top, _touchNPCkeyImg->getFrameX(), 0);
}

