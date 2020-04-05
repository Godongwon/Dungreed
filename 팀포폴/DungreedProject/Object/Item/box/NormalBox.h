#pragma once
#include "Object/Item/Item.h"
class NormalBox: public Item
{
public:
	NormalBox();
	~NormalBox();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

