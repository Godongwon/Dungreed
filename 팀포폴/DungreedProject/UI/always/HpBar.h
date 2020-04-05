#pragma once
#include "base/gameNode.h"
#include "Object/Unit/player/Player.h"
class HpBar: public gameNode
{
private:
	const int _MULTIPLE = 3;
private:
	RECT _PlayerBackHpBar;
	RECT _PlayerHpBar;
	image * _imgPlayerBackHpBar;
	image * _imgPlayerHpBar;
	double _PlayerHpBar_W = 0;
	double _PlayerHpBar_H = 0;
	// HP�� �����Ÿ��� �̹���
	image * _img_hpWave;
	RECT _hpWave_rect;
	// �÷��̾�Լ� �������� ������
	int _playerMaxHp;
	int _playerCurrentHp;
	int _playerLevel;
protected:
	void sync_hpFromPlayer();
public:
	HpBar();
	~HpBar();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

