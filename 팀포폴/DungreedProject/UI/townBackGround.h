#pragma once
#include "base/gameNode.h"
class townBackGround : public gameNode
{
private:
	image * _imgback;
	image * _imgmiddle;
	image * _imgforward;
	image * _imgsecondFloor[3];
	image * _imgtemple;
	image * _imgbrokenFloor;
	image * _townBackGround;

	RECT _rcTownBackGround;
	RECT _testrc;
	RECT _rcSecondFloor[3];
public:
	townBackGround();
	~townBackGround();


	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
 
 