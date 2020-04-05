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
	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};

