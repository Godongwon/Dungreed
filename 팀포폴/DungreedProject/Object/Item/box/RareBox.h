#pragma once
#include "Object/Item/Item.h"
class RareBox: public Item
{
public:
	RareBox();
	~RareBox();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};