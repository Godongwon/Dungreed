
#pragma once
#include "base/gameNode.h"
#include "base/singletonBase.h"
#include "Object/Unit/stage.h"
// �÷��̾ �κ��丮�� ����ϱ� ���� ���
#include "Object/Item/Item.h"
//#include"Scene/testScene.h"

enum player_WAY
{
	Left=0,
	Right
};
enum player_MOVE
{
	Idle=0,
	Move,
	Jump,
	Die
};
enum player_AtkWAY
{
	RIGHTTOP=0,
	TOP,
	LEFTTOP,
	LEFT,
	LEFTBOTTOM,
	BOTTOM,
	RIGHTBOTTOM,
	RIGHT,
	NONE
};
enum render_AtkWay
{
	render_RIGHTTOP = 0,
	render_TOP,
	render_LEFTTOP,
	render_LEFT,
	render_LEFTBOTTOM,
	render_BOTTOM,
	render_RIGHTBOTTOM,
	render_RIGHT,
	render_Nonr
};
enum player_DashWay
{
	DASH_LEFT=0,
	DASH_RIGHT,
	DASH_UP,
	DASH_DOWN,
	DASH_NONE
};
struct Player_ATK
{
	bool b_isAtkRC;
	RECT player_AtkRC;
	int	 playerAtkHeight;//�����Ÿ�
};
class Player : public gameNode  ,public singletonBase<Player>
{
private:
	typedef vector<Item *> vItems;
private:
	const int _PLAYER_RECT_NUM=2;

	RECT _playerbackGround;

	stage* _stage;
	// ����
	RECT _ground;

	player_WAY _playerWay;
	player_MOVE _playerMove;
	RECT _playerRC;//�÷��̾� ��Ʈ
	image* _playerimg;
	animation* _playerani;

	int _playerMouseX;
	int _playerMouseY;

	//============================================================
	//==				�÷��̾ ���� ������ ������.				==
	//============================================================
	vItems _itemList;			// ���� ���̴�.
	int _golds = 30000;			// ���� ���̴�.

	//�÷��̾� ���ݷ�Ʈ
	player_AtkWAY _playerAtkway;
	Player_ATK _playerAtkRC[8];
	int _playerWeaponHeight;//���� ����=�����Ÿ�
	int _playerAtkMouseX;
	int _playerAtkMouseY;
	int _playerAtkCount;
	

	int _playerSpeed;
	float _playerJumpPower;
	float _playerJumpGravity;
	float _playerframeSpeed;
	int _playerHP;
	const int _playerMaxHP=80;
	int _playerAtk;
	////////�÷��̾� �뽬//////
	int _playDashGage;
	player_DashWay _dashWay;
	int _player_DashCount;
	const int _player_MaxDashCount=4;
	int _player_DashDistanceCount;
	int _player_DashPointX;
	int _player_DashPointY;

	/////////ī�޶�///////////
	int _focousplayerX; //�÷��̾� RC ����
	int _focousplayerY; //�÷��̾� RC ����

	/////////�ȼ� �浹/////////
	image* _backGroundImg;
	int _playerProbeX, _playerProbeY;
	int r;
	int g;
	int b;

	//�ϴ�����
	int _jumpDownCount;
	int _jumpDownplayerProbeY;
	int jumpDown_r;
	int jumpDown_g;
	int jumpDown_b;


	//����Render
	render_AtkWay _renderWay;
	image* _weapon_UpDown;
	image* _weapon_LeftRight;
	RECT _weaponRC[6];
	
	//����Effect
	int _renderCount;
	image* _effect_SwingLeft;
	image* _effect_SwingRight;
	image* _effect_SwingTop;
	image* _effect_SwingBottom;

	RECT _effectRC[4];
	






	//bool ����
	bool b_isLeft;
	bool b_isRight;
	bool b_isJump;
	bool b_isJumpDown;
	bool b_isMAXJump;
	bool b_isDash;
	bool b_isATK;
	bool b_isplayerState;
	bool b_isPixelCollision;
	bool b_isPixelOn;
	bool b_isDie;
	bool b_isAtkrender;
	bool b_isAllATK;
	bool b_LbuttonDown = false;	// VK_LBUTTON DOWN �޾Ҵ���
	bool b_LbuttonUp = false;	// VK_LBUTTON UP �޾Ҵ���
	// ���� ������
	SCENE_KIND _sceneKind;
	//�����
	bool b_Debug;
protected:
	//�÷��̾� ����
	void player_AtkRCMake();
	void player_AtkWay();
	void player_ATKRenge();
	void player_ATK();

	//�÷��̾� ������
	void player_Move();
	void player_Jump();
	void player_JumpDown();
	void player_Focus();
	void player_LeftMove();
	void player_RightMove();
	void player_Idle();
	void player_State();
	void player_Die();
	//�÷��̾� ī�޶�
	void player_Camera();
	//�÷��̾� �뽬
	void player_Dash();
	void player_DashMove();
	void player_DashCharge();
	//�ȼ��浹
	void Player_PixelCollision();
	// �÷��̾ ���� ������ ����� �ڵ�
	void delete_itemListAll();
	//����
	void renderWay();
	void weapon_RCMake();
	void weapon_Render();
	//�÷��̾� ����������
	void _effect_RectMake();
	void _effect_Render();
public:
	// ���� ������Ʈ
	void update_sounds();
public:
	//============================================================
	//==				�÷��̾� ������ ó�� �Լ�					==
	//============================================================
	void input_itemList(Item * item) { _itemList.push_back(item); }
	vector<Item*> get_itemList() { return _itemList; }
	int get_golds() { return _golds; }
	void set_golds(int golds) { _golds = golds; }
public:
	Player();
	~Player();
	// Getter, Setter ����
	//
	RECT get_playerRC() { return _playerRC; }
	//void setBackGround(RECT rc) {	_playerbackGround = rc;	}
	// Player HP
	int get_playerHP() { return _playerHP; }
	int get_playerMaxHP(){ return _playerMaxHP; }
	void del_playerBackGround() { _backGroundImg->release(); _backGroundImg = nullptr; }
	void set_playerBackGround(image* img) { _backGroundImg = img; }
	void stage_Make(SCENE_KIND scencekind);

	RECT get_playerBackGround() { return _playerbackGround; }
	//void set_playerBackGround(image* img) { _backGroundImg = img; }
	void set_playerHP(int x) { _playerHP = x; }
	/////////////////////////////////////////////////
	bool get_isAtk() { return b_isATK; }
	void set_isAtk(bool a) { b_isATK = a; }
	Player_ATK get_Player_ATK(int a) {return _playerAtkRC[a];}
	int get_playerAtkNum() {return _playerAtk;}
	/////////////////////////////////////////////
	int getPlayerMoveLeft() { return b_isLeft; }
	int getPlayerMoveRight() { return b_isRight; }
	int getPlayerSpeed() { return _playerSpeed; }
	int getplayer_FocousX() {	return _focousplayerX;}
	// Ground
	RECT get_ground() { return _ground; }
	//  DashGauge
	int get_playDashGage() { return _playDashGage; }
	//	Click
	bool is_LbuttonDown() { return b_LbuttonDown; }
	bool is_LbuttonUp() { return b_LbuttonUp; }

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);


	


};

#define PLAYER	Player::getSingleton()
