#pragma once
#include "Object/Item/Item.h"
class Gladius: public Item
{
public:
	Gladius();
	~Gladius();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

