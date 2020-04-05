#pragma once
#include"base/singletonBase.h"
class cameraManager : public singletonBase<cameraManager>
{
private:
	// ī�޶� �����
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
	// ī�޶� ������ ����ش�.
	void setCameraCenter(POINT point);
	// ī�޶� ������ �����´�.
	POINT getCameraCenter() { return _center; }
	HDC getCameraDC() { return _camera->getMemDC(); }

};

