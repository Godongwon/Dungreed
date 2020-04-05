#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);
	_game = new GameScene;
	_game->init();
	return S_OK;
}
void mainGame::release()
{
	_game->release();
	gameNode::release();
}
void mainGame::update()
{
	gameNode::update();
	_game->update();
}
void mainGame::render(/*HDC hdc*/)
{
	//��� ��Ʈ��
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=====================================================
	_game->render();
	//TIMEMANAGER->render(CAMERAMANAGER->getCameraDC());
	//=====================================================
	//������� ������ HDC�� �׸���.(��������!!)
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
}







