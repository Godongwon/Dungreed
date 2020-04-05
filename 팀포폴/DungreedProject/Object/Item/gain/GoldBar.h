#pragma once
#include "Object/Item/Item.h"
class GoldBar: public Item
{
public:
	GoldBar();
	~GoldBar();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

