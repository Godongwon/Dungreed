#include "stdafx.h"
#include "townScene.h"
// UI �ҷ��´�
#include "UI/UI.h"
//============================================================
//==				���� �Ա� �Լ���							==
//============================================================
void townScene::init_DungeonEntrance()
{
	_DungeonstanceImg = new image;
	_DungeonstanceImg->init("resource/image/���/��������.bmp", 3276 * 3, 85 * 3, 28, 1, 1);
	_DungeonstanceImg->set_frameSection(2, 0, 8, 5, 1, 8, 27, 5, 1);
	_DungeonRC = RectMake(1814, 1010, 889, WINSIZEY / 4);
}
void townScene::delete_DungeonEntrance()
{
	_DungeonstanceImg->release();
	_DungeonstanceImg = nullptr;
}
void townScene::update_DungeonEntrance()
{
	RECT temp;
	if (IntersectRect(&temp, &_DungeonRC, &PLAYER->get_playerRC()))
	{
		b_isDungeonstance = true;
		_DungeonstanceRC = RectMakeCenter(PLAYER->getplayer_FocousX(), (_DungeonRC.top - (_DungeonstanceImg->getFrameHeight() / 2)) + 10, _DungeonstanceImg->getFrameWidth(), _DungeonstanceImg->getFrameHeight());
		_DungeonstanceCount++;
		if (_DungeonstanceCount <= 1)
		{
			_DungeonstanceImg->setFrameX(0);
		}

	}
	else
	{
		b_isDungeonstance = false;
	}
	_DungeonstanceImg->frameUpdate(false);
	//====================================���� ������ ������ ����=======================================
	if (_DungeonstanceImg->getFrameX() >= _DungeonstanceImg->getMaxFrameX())
	{
		b_isDoorOpen = false;
	}
}
void townScene::draw_DungeonEntrance()
{
	if (b_isDungeonstance &&_DungeonstanceCount < (5 * 28) - 1)//
	{
		_DungeonstanceImg->frameRender(getMemDC(), _DungeonstanceRC.left, _DungeonstanceRC.top);
	}
	//ColorRect(getMemDC(), _DungeonRC, RGB(0, 0, 0));
}

townScene::townScene()
{
}

townScene::~townScene()
{
}

void townScene::statusNpc()
{
}

void townScene::statusrelease()
{
	for (int i = 0; i < 2; i++)
	{
		_imgstatusShopRedBox[i]   = nullptr;
		_imgstatusShopMintBox[i]  = nullptr;
		_imgstatusShopWhiteBox[i] = nullptr;
		_imgstatusShopGrayBox[i]  = nullptr;
		_imgstatusShopGoldBox[i]  = nullptr;
	}
	IMAGEMANAGER->deleteImage("AbilityPerkIcon0_0");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon0_1");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon0_2");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon1_0");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon1_1");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon1_2");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon2_0");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon2_1");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon2_2");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon3_0");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon3_1");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon3_2");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon4_0");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon4_1");
	IMAGEMANAGER->deleteImage("AbilityPerkIcon4_2");

	IMAGEMANAGER->deleteImage("statusBoxPower");
	IMAGEMANAGER->deleteImage("statusBoxMoney");
	IMAGEMANAGER->deleteImage("statusBoxDash");
	IMAGEMANAGER->deleteImage("statusBoxCritical");
	IMAGEMANAGER->deleteImage("statusBoxAmmor");

	IMAGEMANAGER->deleteImage("TrainingSchool");
	IMAGEMANAGER->deleteImage("statusNpc");
}
void townScene::statusupdate()
{

}
void townScene::statusrender()
{

}
HRESULT townScene::init()
{
	PLAYER->init();
	PLAYER->stage_Make(TOWN_SCENE);
	_townBackGround = new townBackGround;
	_townBackGround->init();
	_stage  = new stage;
	_stage->init();
	INGAME_UI->init();
	_weaponNpc = new weaponNpc;
	_weaponNpc->init();
	_monsterControl = new MonsterControl;
	_monsterControl->init();
	MISSILECONTROL->init();
	IMAGEMANAGER->addImage("���", "resource/image/���/TownTinyVersion.bmp", 4200,1200, true, RGB(255, 0, 255));
	_backGroudimg = IMAGEMANAGER->findImage("���");
	SOUNDMANAGER->addSound("town", "resource/sound/back/town.wav", true, true);
	SOUNDMANAGER->addSound("��������", "resource/sound/effect/���� �����.wav", true, true);
	SOUNDMANAGER->play("town");


	//statusinit();
	//====================================== ���� �Ա� �ʱ�ȭ ================================
	init_DungeonEntrance();
	return S_OK;
}

void townScene::release()
{
	delete_DungeonEntrance();
	_townBackGround->release();
	_stage->release();
	_stage = nullptr;

	_weaponNpc->release();
	_monsterControl->release();
	_monsterControl = nullptr;
	MISSILECONTROL->release();
	
	//statusrelease();
}
void townScene::update()
{
	_townBackGround->update();
	_stage->update();
	INGAME_UI->update();
	_monsterControl->update();
	MISSILECONTROL->update();
	//PLAYER->setBackGround(_backGroud);
	// ���� ������ �÷��̾� �ƹ��͵� ���ϰ� �ϴ� �κ�
	if (b_isDungeonstance == true) 
	{
		SOUNDMANAGER->stop("town");
		if (_DungeonstanceImg->getFrameX() <= 1)
		{
			SOUNDMANAGER->play("��������");
		}
	}
	else{ PLAYER->update(); }
	_weaponNpc->update();
	//statusupdate();
	// �����Ա� ������Ʈ �κ�
	update_DungeonEntrance();
	if (b_isDungeonstance == true && (_DungeonstanceImg->getFrameX() >= _DungeonstanceImg->getMaxFrameX()))
	{
		SOUNDMANAGER->stop("��������");
		SCENEMANAGER->changeScene("nomalRoom");		
	}
}
void townScene::render()
{
	_townBackGround->render();
	_backGroudimg->render(getMemDC());
	//_stage->render();
	_weaponNpc->render();
	// ���� ���� �ϴ� �κ�
	draw_DungeonEntrance();
	// ������ �÷��̾� ������ ���� ����� �κ�, �÷��̾�� �������� ���߿� ����
	if (b_isDungeonstance == true && (_DungeonstanceImg->getFrameX() >= 8)) {}
	else{ PLAYER->render(); }
	_monsterControl->render();	
	MISSILECONTROL->render();
	// UI�� ���� �������� �����Ѵ�.
	INGAME_UI->render();
}

 