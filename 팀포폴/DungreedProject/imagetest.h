#pragma once
#include "base/gameNode.h"
class imagetest: public gameNode
{
private:
	image * _img;
	RECT _img_rc;
	POINT _centerFocus;
	RECT _centerRect;
	POINT _img_center;
	double _imgAngle;
	POINT * _img_parall;
	POINT * _img_parallRotate;
	char str[256];
public:
	imagetest();
	~imagetest();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
};

