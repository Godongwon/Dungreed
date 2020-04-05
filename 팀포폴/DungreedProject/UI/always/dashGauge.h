#pragma once
#include "base/gameNode.h"
#include "Object/Unit/player/Player.h"
class dashGauge : public gameNode
{
private:
	image * _dashGaugeBar;
	RECT _rcDashGaugeBar;
	image * _dashGauge_0;
	RECT _rcDashGauge_0;
	image * _dashGauge_1;
	RECT _rcDashGauge_1;
	image * _dashGauge_2;
	RECT _rcDashGauge_2;
	image * _dashGauge_3;
	RECT _rcDashGauge_3;
public:
	dashGauge();
	~dashGauge();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};