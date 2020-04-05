#pragma once
#include "Object/Item/Item.h"
class Mace: public Item
{
public:
	Mace();
	~Mace();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

