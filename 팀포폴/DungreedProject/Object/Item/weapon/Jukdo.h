#pragma once
#include "Object/Item/Item.h"
class Jukdo: public Item
{
public:
	Jukdo();
	~Jukdo();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

