#pragma once
#include"Object/Unit/Monster/Monster.h"
#include "Object/Missile/Darkball.h"
#include "Object/Missile/BeliarSword.h"
#include "Object/Missile/Beliar_DeadEffect.h"
class Beliar : public Monster
{
private:
	Darkball * _darkball;
	BeliarSword * _beliarSword;
	Beliar_DeadEffect * _beliar_deadEffect;
	int rndBeliarAct;
	int TemprndBeliarAct;
	float _speedArmMove;
	bool _bEngage;

	int _speedLeftArmAttack;
	int _speedLeftArmReCharge;
	int _cooldownLeftArmAttack;
	int _cooldownLeftArmCharge;
	bool _bLeftArmAttackComplete;

	int _speedRightArmAttack;
	int _speedRightArmReCharge;
	int _cooldownRightArmAttack;
	int _cooldownRightArmCharge;
	bool _bRightArmAttackComplete;

	int delay_BeliarSword;
	int _counter_spawnBeliarSword;
	int _speedSpawnBeliarSword;

	int _counter_spawnDarkball;
	int _speedSpawnDarkball;
	int _delay_SpawnDarkball;
	int _speedDelayDarkball;
	float _angleForDarkball;

	int _counterDeadScene;
	int _rndDeadEffect;
	int _rndDeadEffect_plusMinus;
protected:
	void actBeliar();
	void moveLeftArm();
	void moveRightArm();
	void attackLeftArm();
	void attackRightArm();
	void attackArms();

	void spawnBeliarSword();
	void darkballAttack();
	
	void dead_beliar();
public:
	Beliar();
	~Beliar();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳

};