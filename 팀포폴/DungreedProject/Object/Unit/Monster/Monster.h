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
	stage* _stage;								//�������� �ҷ�����
	RECT _size_monster_rc;						//������ ��Ʈ
	RECT _distance_chk_player_rc;				//������ �÷��̾� �ν� ���� ��Ʈ
	RECT _distance_attack_monster_rc_left;		//������ ���� ���� ���� ��Ʈ
	RECT _distance_attack_monster_rc_right;		//������ ���� ���� ���� ��Ʈ
	//=========================================================
	//===					 RECT	var						===
	//=========================================================
	int _size_monster_width;					//���� ��Ʈ ����
	int _size_monster_height;					//���� ��Ʈ ����
	int _distance_chk_player_width;				//������ �÷��̾� �ν� ���� ��Ʈ ����
	int _distance_chk_player_height;			//������ �÷��̾� �ν� ���� ��Ʈ ����
	int _distance_attack_monster_left_width;	//������ ���� ���� ���� ����
	int _distance_attack_monster_left_height;	//������ ���� ���� ���� ����
	int _distance_attack_monster_right_width;	//������ ������ ���� ���� ����
	int _distance_attack_monster_right_height;	//������ ������ ���� ���� ����

	int rndSpwan;//�׽�Ʈ�� ������ġ ��ȯ
	bool _bDebug;//�����
	//=========================================================
	//===					STATUS	var						===
	//=========================================================
	int _hp;						//ü��
	int _attack_damage;				//���ݷ�
	//speed
	int _speed_attack;				//���ݼӵ�
	int _speed_swing_sword;			//�ֵθ��� �ӵ�(Į�� ġ�ѵ���ٰ� ������ �ӵ���, Į�� �������� �������� �Դ´�)
	int _speed_recharge;			//���� �ӵ�
	int _speed_dash;				//�뽬 �ӵ�
	float _speed_move;				//�̵��ӵ�
	//cooldown
	int _cooldown_attack;			//���� ���ð�
	int _cooldown_swing_sword;		//���� �ֵθ��������� �ð�
	int _cooldown_recharge;			//���� ���ð�
	int _counter_dash;				//�뽬 �����ð�
	//effect,UI
	double _monsterHpBar_W;			//ü�¹� ũ��
	int _counter_DeadEffect;		//�������Ʈ ī����
	int _counter_damageEffect;		//������ ����Ʈ ī����
	int _hpTemp;					//ü�� �ӽ� ����
	bool _haveDamage;				//���ظ� �Ծ����� �Ǵ�
	//=========================================================
	//===					A I		var						===
	//=========================================================
	bool _bShow_left;				//������ �������ΰ�
	bool _bIs_moving;				//�����̴� ���ΰ�
	bool _bChk_player;				//�νĹ��� �ȿ� �÷��̾ ��� �Դ�
	bool _bChase_player;			//�÷��̾ �Ѵ� ���̴�
	bool _bJump_monster;			//������ �ߴ°�
	bool _bAttackable_monster;		//���ݹ��� �ȿ� �÷��̾ ��� �Դ�
	bool _bSwing_sword;				//���� �ֵθ������ΰ�
	bool _bRest;					//ū �ൿ �Ŀ� �������ΰ�
	bool _bChk_playerLocate_left;	//�÷��̾ ���ʿ� �ִ°�
	bool _bChk_playerLocate_right;	//�÷��̾ �����ʿ� �ִ°�
	bool _bChk_playerLocate_up;		//�÷��̾ ���ʿ� �ִ°�
	bool _bChk_playerLocate_down;	//�÷��̾ �Ʒ��ʿ� �ִ°�
	bool _bDash;					//�뽬�ؾ��ϴ°�	
	bool _bAttackStart;				//������ �����ߴ°�
	bool _bGiveDamage;				//�������� �־��°�
	bool _bDead_monster;			//����ߴ°�
	int _counter_monsterJump;		//���� ���� �Ѱ踦 �����ش�
	int _rnd_idleAct_leftRight;		//�����¿��� �� �ൿ ���� ����
	int _rnd_idleAct_upDown;		//�����¿��� �� �ൿ ���� ����
	int _cooldown_idle_act;			//idle ���� �ൿ ī��Ʈ
	int _cooldown_idle_Stand;		//idle ���� �۶����� ī��Ʈ
	//=========================================================
	//===					MISSILE		var					===
	//=========================================================
	bool _bMonsterFire;				//�߻翩�� Ȯ��
	bool _bChk_player_locate;		//�÷��̾� ��ġ�� Ȯ��
	RECT tempPlayerLocate;			//�÷��̾� ��ġ�� ����
	float getAngle_toPlayer;		//�÷��̾� ������ ���� ����
	POINT _focus_forMissile;		//���Ÿ� ���� �̻��� �߻� ��ġ
	int _focus_changeX;				//�߻���ġ�� �ٲٴ� ����
	int _focus_changeY;				//�߻���ġ�� �ٲٴ� ����
	//=========================================================
	//===			V O I D		B A S I C					===
	//=========================================================
	void idle();					//������
	void idle_airUnit();			//������ (��������)
	void findPlayer();				//�÷��̾ ã�ƶ�!
	void moveLeft();				//�������� �̵�
	void moveRight();				//���������� �̵�
	void moveUp();					//���� �̵�
	void moveDown();				//�Ʒ��� �̵�
	void jump_up();					//���� ����
	void jump_down();				//�Ʒ��� ����
	void dead_monster();			//���� ���
	void dead_effect();				//��� ����Ʈ
	void damage_effect();			//������ ����Ʈ
	//=========================================================
	//===			V O I D		AI	MELEE UNIT				===
	//=========================================================
	void chasePlayer();				//�÷��̾� �߰�
	void chasePlayer_dogs();		//�÷��̾� �߰�(��)
	void chasePlayer_minotaurs();	//�÷��̾� �߰�(�̳�Ÿ�츣��)
	void chasePlayer_airUnits();	//�÷��̾� �߰�(��������)
	void compareAttack_warriors();	//���ݻ�Ÿ� ���� �ִ��� Ȯ��
	void compareAttack_dogs();		//���ݻ�Ÿ� ���� �ִ��� Ȯ��(��)
	void compareAttack_minotaurs();	//���ݻ�Ÿ� ���� �ִ��� Ȯ��(�̳�Ÿ�츣��)
	void compareAttack_ghosts();	//���ݰ������� Ȯ��(��Ʈ)
	void attack_warriors();			//����(��)
	void attack_dogs();				//����(��)
	void attack_minotaurs();		//����(�̳�Ÿ�츣��)
	void attack_ghosts();			//����(�̳�Ÿ�츣��)
	void dash_minotaurs();			//�뽬(�̳�Ÿ�츣��)
	//=========================================================
	//===			V O I D		AI	RANGE UNIT				===
	//=========================================================
	void chasePlayer_RangeUnit();	//���ݻ�Ÿ� ���� �ִ��� Ȯ��
	//=========================================================
	//===			V O I D		MISSILE						===
	//=========================================================
	void init_focusforMissile();			//�̻��� ���� ��ġ��� ( ������ ��ġ)
	void init_focusforMissile_plusVar();		//�̻��� ���� ��ġ + ������ġ ���ϰ� ������
	void angle_toPlayer();					//�÷��̾ ���ϴ� �ޱ�
	void make_missile(Missile * missile);	//�̻��� ���� ( ���� �о��ֱ� )

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
	void show_rc();										//��Ʈ ���̱� ( ��� )	
	void init_monster_spawnLocateGround(int locateX);			//���� ������ġ(����)
	void init_monster_spawnLocateAir(int locateX, int locateY);	//���� ������ġ(����)
	void init_monster_size_rc_ground();					//���� ����(����)
	void init_monster_size_rc_air();					//���� ����(����)
	void init_chk_distance_player_rc();					//������ �÷��̾� �ν� ���� ����
	void init_attack_distance_rc_left();				//������ ���� ���� ���� ����
	void init_attack_distance_rc_right();				//������ ������ ���� ���� ����
	void init_beliar();

	//=========================================================
	//===				GETTER		SETTER					===
	//=========================================================
	void set_hp(int x) { _hp = x; }						//HP �����ϱ�
	int get_hp() { return _hp; }						//HP �޾ƿ���
	void set_rc(RECT rc) { _size_monster_rc = rc; }		//������ ��Ʈ �����ϱ�
	RECT get_rc() { return _size_monster_rc; }			//������ ��Ʈ �޾ƿ���
	void set_fire(bool x) { _bMonsterFire = x; }		//�̻��� �߻翩�� �����ϱ�
	bool get_fire() { return _bMonsterFire; }			//�̻��� �߻翩�� �޾ƿ���
	float get_angle() { return getAngle_toPlayer; }		//�÷��̾ ���� �ޱ۰� �޾ƿ���
	POINT get_focus() { return _focus_forMissile; }		//�̻��� ������ġ �޾ƿ���
	bool get_dead_monster() { return _bDead_monster; }	//���� ������� �޾ƿ���
public:
	Monster();
	~Monster();
	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};


