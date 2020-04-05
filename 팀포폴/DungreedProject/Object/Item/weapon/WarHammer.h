#pragma once
#include "Object/Item/Item.h"
class WarHammer: public Item
{
public:
	WarHammer();
	~WarHammer();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

