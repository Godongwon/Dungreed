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
	void delete_missiles();						//미사일 삭제

	void draw_missiles();						//그리기
	void release_missiles();					//릴리즈
	void update_missiles();
public:
	// 벡터에 미사일 ㄱ
	void push_missile(Missile *);
public:
	MissileControl();
	~MissileControl();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳
};

#define MISSILECONTROL	MissileControl::getSingleton()
