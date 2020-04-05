#pragma once
#include"base/singletonBase.h"
class cameraManager : public singletonBase<cameraManager>
{
private:
	// 카메라 백버퍼
	image* _camera;

	POINT _center;
	POINT _cameraXY;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void relaese();
	void update();
	void render(image* img);
	// 카메라 중점을 잡아준다.
	void setCameraCenter(POINT point);
	// 카메라 정보를 가져온다.
	POINT getCameraCenter() { return _center; }
	HDC getCameraDC() { return _camera->getMemDC(); }

};

