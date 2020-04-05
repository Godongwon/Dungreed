#include "stdafx.h"
#include "cameraManager.h"


cameraManager::cameraManager(){}

cameraManager::~cameraManager(){}

HRESULT cameraManager::init()
{
	// 카메라 백버퍼다.
	_camera = IMAGEMANAGER->addImage("카메라", WINSIZEX, WINSIZEY);
	// 카메라의 중점을 잡아준다.
	_center = PointMake(WINSIZEX / 2, WINSIZEY/2);
	// 카메라의 RECT left, top 위치다.
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
	// 카메라의 중점을 다시 잡아준다.
	_center.x = point.x;
	_center.y = point.y;
}
