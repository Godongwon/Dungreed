#pragma once
#include "Object/Item/Item.h"
class Fairy: public Item
{
public:
	Fairy();
	~Fairy();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

