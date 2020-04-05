#pragma once
#include "Object/Missile/Missile.h"
#include "base/singletonBase.h"
class MissileControl : public gameNode, public singletonBase<MissileControl>
{
private:
	typedef vector<Missile*> vMissile;
private:
	vMissile _missiles;
	vMissile::iterator _missilesIter;
protected:
	void delete_missiles();						//�̻��� ����

	void draw_missiles();						//�׸���
	void release_missiles();					//������
	void update_missiles();
public:
	// ���Ϳ� �̻��� ��
	void push_missile(Missile *);
public:
	MissileControl();
	~MissileControl();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};

#define MISSILECONTROL	MissileControl::getSingleton()
