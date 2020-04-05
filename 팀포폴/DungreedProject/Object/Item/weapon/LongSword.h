#pragma once
#include "Object/Item/Item.h"
class LongSword: public Item
{
public:
	LongSword();
	~LongSword();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

