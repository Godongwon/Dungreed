#pragma once
#include "Object/Item/Item.h"
class Coin: public Item
{
public:
	Coin();
	~Coin();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

