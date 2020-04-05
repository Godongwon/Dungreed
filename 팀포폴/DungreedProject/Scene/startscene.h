#pragma once
#include "Scene/Scene.h"
#include "base/gameNode.h"
class startscene : public Scene
{
protected:
	image * _imgfront;
	image * _imgmiddle;
	image * _imgLogo;

	image * _imgstart;
	image * _imgset;
	image * _imgexit;

	RECT exitrc;
	RECT setrc;				//¼³Á¤Ã¢
	RECT startrc;
	RECT background;
	RECT _LogoRC;

	bool bcheck_button;
	int _loopX;
	int _frontloopX;

	


	int _runframe;
	int _startframe;
public:
	startscene();
	~startscene();

	virtual  HRESULT init();
	virtual  void release();
	virtual  void update();
	virtual  void render();
};

