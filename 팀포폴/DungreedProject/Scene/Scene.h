#pragma once
#include "base/gameNode.h"
#include "Object/Item/AllItemList.h"
class Scene: public gameNode
{
private:
	typedef vector<Item*> vItem;
public:
	void make_item(string strKey, POINT center);
public:
	Scene();
	~Scene();
	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳
};

