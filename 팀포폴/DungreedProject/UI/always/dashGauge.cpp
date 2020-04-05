#include "stdafx.h"
#include "dashGauge.h"
dashGauge::dashGauge()
{
}
dashGauge::~dashGauge()
{
}
HRESULT dashGauge::init()
{
	_dashGaugeBar = IMAGEMANAGER->addImage("dashGaugeBar", "resource/image/UI/dashCountBar.bmp", 43 * 3, 8 * 3, true, RGB(255, 0, 255));
	_dashGauge_0 = IMAGEMANAGER->addImage("dashGauge_0", "resource/image/UI/dashCount.bmp", 9*3, 4*3, true, RGB(255, 0, 255));
	_dashGauge_1 = IMAGEMANAGER->addImage("dashGauge_1", "resource/image/UI/dashCount.bmp", 9*3, 4*3, true, RGB(255, 0, 255));
	_dashGauge_2 = IMAGEMANAGER->addImage("dashGauge_2", "resource/image/UI/dashCount.bmp", 9*3, 4*3, true, RGB(255, 0, 255));
	_dashGauge_3 = IMAGEMANAGER->addImage("dashGauge_3", "resource/image/UI/dashCount.bmp", 9*3, 4*3, true, RGB(255, 0, 255));
	// 대시게이지 초기화 위치 잡는 부분
	_rcDashGaugeBar = RectMake(CAMERAMANAGER->getCameraCenter().x - (WINSIZEX/2 - 10), 
							   CAMERAMANAGER->getCameraCenter().y - (WINSIZEY/2 - 16*4) - 5, 43*2, 8*2);
	_rcDashGauge_0 = RectMake(_rcDashGaugeBar.left + 6, _rcDashGaugeBar.top + 6, 9*3, 4*3);
	_rcDashGauge_1 = RectMake(_rcDashGauge_0.right + 3, _rcDashGaugeBar.top + 6, 9*3, 4*3);
	_rcDashGauge_2 = RectMake(_rcDashGauge_1.right + 3, _rcDashGaugeBar.top + 6, 9*3, 4*3);
	_rcDashGauge_3 = RectMake(_rcDashGauge_2.right + 3, _rcDashGaugeBar.top + 6, 9*3, 4*3);

	return S_OK;
}

void dashGauge::release()
{
	IMAGEMANAGER->deleteImage("dashGauage_0");
	_dashGauge_3 = nullptr;
	IMAGEMANAGER->deleteImage("dashGauage_1");
	_dashGauge_2 = nullptr;
	IMAGEMANAGER->deleteImage("dashGauage_2");
	_dashGauge_1 = nullptr;
	IMAGEMANAGER->deleteImage("dashGauage_3");
	_dashGauge_0 = nullptr;
	IMAGEMANAGER->deleteImage("dashGaugeBar");
	_dashGaugeBar = nullptr;
}

void dashGauge::update()
{
}
 
void dashGauge::render()
{
	_dashGaugeBar->render(CAMERAMANAGER->getCameraDC(), _rcDashGaugeBar.left, _rcDashGaugeBar.top);
	switch (PLAYER->get_playDashGage())
	{
	case 4:
		_dashGauge_3->render(CAMERAMANAGER->getCameraDC(), _rcDashGauge_3.left, _rcDashGauge_3.top);
	case 3:
		_dashGauge_2->render(CAMERAMANAGER->getCameraDC(), _rcDashGauge_2.left, _rcDashGauge_2.top);
	case 2:
		_dashGauge_1->render(CAMERAMANAGER->getCameraDC(), _rcDashGauge_1.left, _rcDashGauge_1.top);
	case 1:
		_dashGauge_0->render(CAMERAMANAGER->getCameraDC(), _rcDashGauge_0.left, _rcDashGauge_0.top);
	default:
		break;
	}
	
}
 









 




  