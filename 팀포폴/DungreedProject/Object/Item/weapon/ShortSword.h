#pragma once
#include "Object/Item/Item.h"
class ShortSword: public Item
{
public:
	ShortSword();
	~ShortSword();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

