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
	image * _img_left_arrow;					//�̹���	�ҷ�����
	image * _img_right_arrow;					//�̹���	�ҷ�����
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
	//===					 ��Ʈ ������						===
	//=========================================================
	int _size_missile_width;					//�̻��� ��Ʈ ����
	int _size_missile_height;					//�̻��� ��Ʈ ����
	float _speed_missile;

	// �̻����� �߻縦 �����ϴ� ��ġ��
	POINT _focus;
	float _angle;
	int _delay;		//�̻��� �߻縦 �������� ���� ī����
	// �̻����� ������ ���� �����ϴ� ������
	int _counterDelete;
	bool _bCollide;
	bool _bDelete;
protected:
	void init_missile_size_rc();						//�̻��� ����
	
public:
	void show_missile_rc();								//��Ʈ ���̱� ( ��� )	
//	void init_ground();									//�׶��� �� �޾ƿ���
	
	void init_missileInfo(POINT focus, float angle);	//�̻��� ����, ������ �������� �޾ƿ�
	bool is_deleteMissile() { return _bDelete; }
	void init_BeliarSwordInfo(POINT focus, int delay);

public:
	Missile();
	~Missile();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};
