#pragma once
#include "base/gameNode.h"
#include "Object/Unit/player/Player.h"
#include "Object/Unit/stage.h"
#include "Object/Missile/Missile.h"
#include "Object/Missile/MissileControl.h"
enum MONSTER_TYPE
{
	TYPE_EMPTY,
	//Melee Ground
	SKELETON_WORRIOR_BIG,
	SKELETON_WORRIOR_TWOHAND,
	SKELETON_WORRIOR_ONEHAND,
	SKELETON_DOG,
	MINOTAURS,
	//Melee Air	
	BAT_SMALL_NEUTRAL,
	GHOST,
	//Range Ground
	SKELETON_ARCHER,
	//Range	Air	
	BANSHEE,
	BAT_SMALL,
	BAT_BIG_PURPLE,
	BAT_BIG_RED,
	//BOSS
	BELIAL

};
class Monster : public gameNode
{
protected:
	image * _img_left_idle;						
	image * _img_right_idle;					
	image * _img_left_move;						
	image * _img_right_move;					
	image * _img_left_attack;					
	image * _img_right_attack;					
	image * _img_left_dash;						
	image * _img_right_dash;			
	image * _img_left_dash_dust;
	image * _img_right_dash_dust;
	image * _img_leftAttack_weapon;				
	image * _img_rightAttack_weapon;			
	image * _img_leftIdle_weapon;				
	image * _img_rightIdle_weapon;
	image * _img_deadEffect;
	image * _img_damageEffect;
	image * _img_lifeBar;
	image * _img_lifeBack;

	image * _img_beliar;
	image * _img_beliarOpenMouse;
	image * _img_beliarLeftArm_idle;
	image * _img_beliarRightArm_idle;
	image * _img_beliarLeftArm_attack;
	image * _img_beliarRightArm_attack;
	image * _img_beliarLeftArm_Laser;
	image * _img_beliarRightArm_Laser;
	image * _img_beliarLaserball;
	image * _img_beliarBodyball;

	image * _img_bossLifeBar;
	image * _img_bossLifeBack;
	stage* _stage;								//스테이지 불러오기
	RECT _size_monster_rc;						//몬스터의 렉트
	RECT _distance_chk_player_rc;				//몬스터의 플레이어 인식 범위 렉트
	RECT _distance_attack_monster_rc_left;		//몬스터의 왼쪽 공격 범위 렉트
	RECT _distance_attack_monster_rc_right;		//몬스터의 왼쪽 공격 범위 렉트
	//=========================================================
	//===					 RECT	var						===
	//=========================================================
	int _size_monster_width;					//몬스터 렉트 부피
	int _size_monster_height;					//몬스터 렉트 높이
	int _distance_chk_player_width;				//몬스터의 플레이어 인식 범위 렉트 부피
	int _distance_chk_player_height;			//몬스터의 플레이어 인식 범위 렉트 높이
	int _distance_attack_monster_left_width;	//몬스터의 왼쪽 공격 범위 부피
	int _distance_attack_monster_left_height;	//몬스터의 왼쪽 공격 범위 높이
	int _distance_attack_monster_right_width;	//몬스터의 오른쪽 공격 범위 부피
	int _distance_attack_monster_right_height;	//몬스터의 오른쪽 공격 범위 높이

	int rndSpwan;//테스트용 랜덤위치 소환
	bool _bDebug;//디버그
	//=========================================================
	//===					STATUS	var						===
	//=========================================================
	int _hp;						//체력
	int _attack_damage;				//공격력
	//speed
	int _speed_attack;				//공격속도
	int _speed_swing_sword;			//휘두르는 속도(칼을 치켜들었다가 내리는 속도다, 칼이 내려오면 데미지를 입는다)
	int _speed_recharge;			//차지 속도
	int _speed_dash;				//대쉬 속도
	float _speed_move;				//이동속도
	//cooldown
	int _cooldown_attack;			//공격 대기시간
	int _cooldown_swing_sword;		//검을 휘두를때까지의 시간
	int _cooldown_recharge;			//차지 대기시간
	int _counter_dash;				//대쉬 유지시간
	//effect,UI
	double _monsterHpBar_W;			//체력바 크기
	int _counter_DeadEffect;		//사망이펙트 카운터
	int _counter_damageEffect;		//데미지 이펙트 카운터
	int _hpTemp;					//체력 임시 변수
	bool _haveDamage;				//피해를 입었는지 판단
	//=========================================================
	//===					A I		var						===
	//=========================================================
	bool _bShow_left;				//왼쪽을 보는중인가
	bool _bIs_moving;				//움직이는 중인가
	bool _bChk_player;				//인식범위 안에 플레이어가 들어 왔다
	bool _bChase_player;			//플레이어를 쫓는 중이다
	bool _bJump_monster;			//점프를 했는가
	bool _bAttackable_monster;		//공격범위 안에 플레이어가 들어 왔다
	bool _bSwing_sword;				//검을 휘두르는중인가
	bool _bRest;					//큰 행동 후에 쉬는중인가
	bool _bChk_playerLocate_left;	//플레이어가 왼쪽에 있는가
	bool _bChk_playerLocate_right;	//플레이어가 오른쪽에 있는가
	bool _bChk_playerLocate_up;		//플레이어가 위쪽에 있는가
	bool _bChk_playerLocate_down;	//플레이어가 아래쪽에 있는가
	bool _bDash;					//대쉬해야하는가	
	bool _bAttackStart;				//공격을 시작했는가
	bool _bGiveDamage;				//데미지를 주었는가
	bool _bDead_monster;			//사망했는가
	int _counter_monsterJump;		//점프 도달 한계를 세어준다
	int _rnd_idleAct_leftRight;		//대기상태에서 할 행동 랜덤 변수
	int _rnd_idleAct_upDown;		//대기상태에서 할 행동 랜덤 변수
	int _cooldown_idle_act;			//idle 상태 행동 카운트
	int _cooldown_idle_Stand;		//idle 상태 멍때리기 카운트
	//=========================================================
	//===					MISSILE		var					===
	//=========================================================
	bool _bMonsterFire;				//발사여부 확인
	bool _bChk_player_locate;		//플레이어 위치를 확인
	RECT tempPlayerLocate;			//플레이어 위치를 저장
	float getAngle_toPlayer;		//플레이어 까지의 각도 저장
	POINT _focus_forMissile;		//원거리 몹의 미사일 발사 위치
	int _focus_changeX;				//발사위치를 바꾸는 변수
	int _focus_changeY;				//발사위치를 바꾸는 변수
	//=========================================================
	//===			V O I D		B A S I C					===
	//=========================================================
	void idle();					//대기상태
	void idle_airUnit();			//대기상태 (공중유닛)
	void findPlayer();				//플레이어를 찾아라!
	void moveLeft();				//왼쪽으로 이동
	void moveRight();				//오른쪽으로 이동
	void moveUp();					//위로 이동
	void moveDown();				//아래로 이동
	void jump_up();					//위로 점프
	void jump_down();				//아래로 점프
	void dead_monster();			//몬스터 사망
	void dead_effect();				//사망 이펙트
	void damage_effect();			//데미지 이펙트
	//=========================================================
	//===			V O I D		AI	MELEE UNIT				===
	//=========================================================
	void chasePlayer();				//플레이어 추격
	void chasePlayer_dogs();		//플레이어 추격(개)
	void chasePlayer_minotaurs();	//플레이어 추격(미노타우르스)
	void chasePlayer_airUnits();	//플레이어 추격(공중유닛)
	void compareAttack_warriors();	//공격사거리 내에 있는지 확인
	void compareAttack_dogs();		//공격사거리 내에 있는지 확인(개)
	void compareAttack_minotaurs();	//공격사거리 내에 있는지 확인(미노타우르스)
	void compareAttack_ghosts();	//공격가능한지 확인(고스트)
	void attack_warriors();			//공격(개)
	void attack_dogs();				//공격(개)
	void attack_minotaurs();		//공격(미노타우르스)
	void attack_ghosts();			//공격(미노타우르스)
	void dash_minotaurs();			//대쉬(미노타우르스)
	//=========================================================
	//===			V O I D		AI	RANGE UNIT				===
	//=========================================================
	void chasePlayer_RangeUnit();	//공격사거리 내에 있는지 확인
	//=========================================================
	//===			V O I D		MISSILE						===
	//=========================================================
	void init_focusforMissile();			//미사일 생성 위치잡기 ( 몬스터의 위치)
	void init_focusforMissile_plusVar();		//미사일 생성 위치 + 생성위치 변하고 싶은곳
	void angle_toPlayer();					//플레이어를 향하는 앵글
	void make_missile(Missile * missile);	//미사일 생성 ( 벡터 밀어주기 )

	//=========================================================
	//===				B	O	S	S						===
	//=========================================================
	RECT _beliar_leftArm_rc;
	RECT _beliar_rightArm_rc;
	RECT _beliar_leftArm_attack_distance_rc;
	RECT _beliar_rightArm_attack_distance_rc;

	int _beliar_Arm_width;
	int _beliar_Arm_height;
	int _beliar_Arm_attack_distance_width;
	int _beliar_Arm_attack_distance_height;
//=====================================================================================================
//=============							P	U	B	L	I	C								===========
//=====================================================================================================
public:
	//=========================================================
	//===					RECT	INIT					===
	//=========================================================
	int _spawnLocateMonsterX;
	int _spawnLocateMonsterY;
	void show_rc();										//렉트 보이기 ( 토글 )	
	void init_monster_spawnLocateGround(int locateX);			//몬스터 생성위치(지상)
	void init_monster_spawnLocateAir(int locateX, int locateY);	//몬스터 생성위치(공중)
	void init_monster_size_rc_ground();					//몬스터 생성(지상)
	void init_monster_size_rc_air();					//몬스터 생성(공중)
	void init_chk_distance_player_rc();					//몬스터의 플레이어 인식 범위 생성
	void init_attack_distance_rc_left();				//몬스터의 왼쪽 공격 범위 생성
	void init_attack_distance_rc_right();				//몬스터의 오른쪽 공격 범위 생성
	void init_beliar();

	//=========================================================
	//===				GETTER		SETTER					===
	//=========================================================
	void set_hp(int x) { _hp = x; }						//HP 설정하기
	int get_hp() { return _hp; }						//HP 받아오기
	void set_rc(RECT rc) { _size_monster_rc = rc; }		//사이즈 렉트 설정하기
	RECT get_rc() { return _size_monster_rc; }			//사이즈 렉트 받아오기
	void set_fire(bool x) { _bMonsterFire = x; }		//미사일 발사여부 설정하기
	bool get_fire() { return _bMonsterFire; }			//미사일 발사여부 받아오기
	float get_angle() { return getAngle_toPlayer; }		//플레이어를 향한 앵글값 받아오기
	POINT get_focus() { return _focus_forMissile; }		//미사일 생성위치 받아오기
	bool get_dead_monster() { return _bDead_monster; }	//몬스터 사망여부 받아오기
public:
	Monster();
	~Monster();
	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳
};


