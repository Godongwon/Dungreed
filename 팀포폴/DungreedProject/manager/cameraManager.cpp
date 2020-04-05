#include "stdafx.h"
#include "cameraManager.h"


cameraManager::cameraManager(){}

cameraManager::~cameraManager(){}

HRESULT cameraManager::init()
{
	// ī�޶� ����۴�.
	_camera = IMAGEMANAGER->addImage("ī�޶�", WINSIZEX, WINSIZEY);
	// ī�޶��� ������ ����ش�.
	_center = PointMake(WINSIZEX / 2, WINSIZEY/2);
	// ī�޶��� RECT left, top ��ġ��.
	_cameraXY = PointMake(_center.x - WINSIZEX / 2, _center.y-WINSIZEY/2);

	return S_OK;
}

void cameraManager::relaese()
{
	SAFE_DELETE(_camera);
}

void cameraManager::update()
{
	_cameraXY = PointMake(_center.x - WINSIZEX / 2, _center.y - WINSIZEY / 2);
}

void cameraManager::render(image * img)
{
	GdiTransparentBlt(img->getMemDC(), _center.x - WINSIZEX / 2, _center.y - WINSIZEY / 2, WINSIZEX, WINSIZEY, _camera->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, RGB(255, 255, 255));
}

void cameraManager::setCameraCenter(POINT point)
{
	// ī�޶��� ������ �ٽ� ����ش�.
	_center.x = point.x;
	_center.y = point.y;
}
