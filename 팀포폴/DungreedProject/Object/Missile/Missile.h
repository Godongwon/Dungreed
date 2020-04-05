#pragma once
#include "base/gameNode.h"

enum MISSILE_TYPE
{
	ARROW,
	NOTE,
	FIREBALL
};
class Missile : public gameNode
{
protected :
	image * _img_left_arrow;					//이미지	불러오기
	image * _img_right_arrow;					//이미지	불러오기
	image * _img_arrow_crash;
	image * _img_note_move;
	image * _img_note_crash;
	image * _img_fireball_small_move;
	image * _img_fireball_small_crash;
	image * _img_fireball_big;

	image * _img_darkball;
	image * _img_darkballCrash;
	image * _img_beliarSword;
	image * _img_beliarDeadEffect;

	RECT _size_missile_rc;
	//=========================================================
	//===					 렉트 변수들						===
	//=========================================================
	int _size_missile_width;					//미사일 렉트 부피
	int _size_missile_height;					//미사일 렉트 높이
	float _speed_missile;

	// 미사일이 발사를 시작하는 위치다
	POINT _focus;
	float _angle;
	int _delay;		//미사일 발사를 언제할지 세는 카운터
	// 미사일을 없앨지 말지 결정하는 변수다
	int _counterDelete;
	bool _bCollide;
	bool _bDelete;
protected:
	void init_missile_size_rc();						//미사일 생성
	
public:
	void show_missile_rc();								//렉트 보이기 ( 토글 )	
//	void init_ground();									//그라운드 값 받아오기
	
	void init_missileInfo(POINT focus, float angle);	//미사일 생성, 정보는 몬스터한테 받아옴
	bool is_deleteMissile() { return _bDelete; }
	void init_BeliarSwordInfo(POINT focus, int delay);

public:
	Missile();
	~Missile();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳
};
