#include "stdafx.h"
#include "GameScene.h"


GameScene::GameScene()
{
}
GameScene::~GameScene()
{
}
HRESULT GameScene::init()
{
	SCENEMANAGER->addScene("startscene", new startscene);
	SCENEMANAGER->addScene("townScene", new townScene);
	SCENEMANAGER->addScene("Maptool", new Maptool);
	SCENEMANAGER->addScene("DungeonEntrance", new DungeonEntrance);
	SCENEMANAGER->addScene("nomalRoom", new nomalRoom);
	SCENEMANAGER->addScene("minoRoom", new minoRoom);
	SCENEMANAGER->addScene("BansiRoom", new BansiRoom);
	SCENEMANAGER->changeScene("startscene");
	return S_OK;
}
void GameScene::release()
{
	SCENEMANAGER->release();
	IMAGEMANAGER->deleteImage("Ä«¸Ş¶ó");
}
void GameScene::update()
{
	SCENEMANAGER->update();
}
void GameScene::render()
{
	SCENEMANAGER->render();
}
