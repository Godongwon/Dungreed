#include "stdafx.h"
#include "Monster.h"
//====================================================================
//==					R E C T		C R E A T E						==
//====================================================================

void Monster::init_monster_spawnLocateGround(int locateX)
{
	_spawnLocateMonsterX = locateX;
	init_monster_size_rc_ground();
}
void Monster::init_monster_spawnLocateAir(int locateX, int locateY)
{
	_spawnLocateMonsterX = locateX;
	_spawnLocateMonsterY = locateY;
	init_monster_size_rc_air();
}
//사이즈 렉트 생성
void Monster::init_monster_size_rc_ground()
{
	_size_monster_rc = RectMake(_spawnLocateMonsterX, PLAYER->get_ground().top - _size_monster_height, _size_monster_width, _size_monster_height);
}
void Monster::init_monster_size_rc_air()
{
	_size_monster_rc = RectMake(_spawnLocateMonsterX, _spawnLocateMonsterY, _size_monster_width, _size_monster_height);
}
//추격 범위 렉트 생성
void Monster::init_chk_distance_player_rc()
{
	_distance_chk_player_rc = RectMakeCenter((_size_monster_rc.left + _size_monster_rc.right) / 2,(_size_monster_rc.top + _size_monster_rc.bottom ) / 2,
		_distance_chk_player_width, _distance_chk_player_height);
}
//공격 사거리 렉트 왼쪽 생성
void Monster::init_attack_distance_rc_left()
{
	_distance_attack_monster_rc_left = RectMake(_size_monster_rc.left - _distance_attack_monster_left_width + ((_size_monster_rc.right - _size_monster_rc.left) / 2), _size_monster_rc.bottom - _distance_attack_monster_left_height,
		_distance_attack_monster_left_width, _distance_attack_monster_left_height);
}
//공격 사거리 렉트 오른쪽 생성
void Monster::init_attack_distance_rc_right()
{
	_distance_attack_monster_rc_right = RectMake(_size_monster_rc.right - ((_size_monster_rc.right-_size_monster_rc.left)/2), _size_monster_rc.bottom- _distance_attack_monster_left_height,
		_distance_attack_monster_right_width, _distance_attack_monster_right_height);
}


//====================================================================
//==				B A S I C	O P E R A T I O N	   				==
//====================================================================

//왼쪽 이동
void Monster::moveLeft()
{	
	if(_size_monster_rc.left >= PLAYER->get_ground().left)
	{
	_size_monster_rc.left -= (LONG)_speed_move;
	_size_monster_rc.right -= (LONG)_speed_move;
	_distance_chk_player_rc.left -= (LONG)_speed_move;
	_distance_chk_player_rc.right -= (LONG)_speed_move;
	_distance_attack_monster_rc_left.left -= (LONG)_speed_move;
	_distance_attack_monster_rc_left.right -= (LONG)_speed_move;
	_distance_attack_monster_rc_right.left -= (LONG)_speed_move;
	_distance_attack_monster_rc_right.right -= (LONG)_speed_move;
	_bShow_left = true;
	_bIs_moving = true;
	}
}
//오른쪽 이동
void Monster::moveRight()
{
	if (_size_monster_rc.right <= PLAYER->get_ground().right)
	{
		_size_monster_rc.left += (LONG)_speed_move;
		_size_monster_rc.right += (LONG)_speed_move;
		_distance_chk_player_rc.left += (LONG)_speed_move;
		_distance_chk_player_rc.right += (LONG)_speed_move;
		_distance_attack_monster_rc_left.left += (LONG)_speed_move;
		_distance_attack_monster_rc_left.right += (LONG)_speed_move;
		_distance_attack_monster_rc_right.left += (LONG)_speed_move;
		_distance_attack_monster_rc_right.right += (LONG)_speed_move;
		_bShow_left = false;
		_bIs_moving = true;
	}
}
//위로 이동 (공중유닛)
void Monster::moveUp()
{
	if (_size_monster_rc.bottom < PLAYER->get_ground().top - 500)
	{
		_size_monster_rc.top -= (LONG)_speed_move;
		_size_monster_rc.bottom -= (LONG)_speed_move;
		_distance_chk_player_rc.top -= (LONG)_speed_move;
		_distance_chk_player_rc.bottom -= (LONG)_speed_move;
	}
}
//아래로 이동 (공중유닛)
void Monster::moveDown()
{
	if (_size_monster_rc.bottom < PLAYER->get_ground().top)
	{
		_size_monster_rc.top += (LONG)_speed_move;
		_size_monster_rc.bottom += (LONG)_speed_move;
		_distance_chk_player_rc.top += (LONG)_speed_move;
		_distance_chk_player_rc.bottom += (LONG)_speed_move;
	}
}
//위로 점프
void Monster::jump_up()
{
	if (_bJump_monster == true)
	{
		if (_counter_monsterJump <= 30)
		{
			OffsetRect(&_size_monster_rc, 0, (int)(-(_speed_move + 2)));
			OffsetRect(&_distance_chk_player_rc, 0, (int)(-(_speed_move + 2)));
			OffsetRect(&_distance_attack_monster_rc_right, 0, (int)(-(_speed_move + 2)));
			OffsetRect(&_distance_attack_monster_rc_left, 0, (int)(-(_speed_move + 2)));
			_counter_monsterJump++;
		}
		if (_counter_monsterJump >= 30)
		{
			OffsetRect(&_size_monster_rc, 0, (int)(_speed_move + 3));
			OffsetRect(&_distance_chk_player_rc, 0, (int)(_speed_move + 3));
			OffsetRect(&_distance_attack_monster_rc_right, 0, (int)(_speed_move + 3));
			OffsetRect(&_distance_attack_monster_rc_left, 0, (int)(_speed_move + 3));
			_counter_monsterJump++;
		}
		if (_size_monster_rc.bottom >=  PLAYER->get_ground().top + 1)
		{
			_size_monster_rc.bottom =  PLAYER->get_ground().top + 1;
			_distance_chk_player_rc.bottom = ((_size_monster_rc.bottom + _size_monster_rc.top)/2) + (_distance_chk_player_height / 2);
			_distance_attack_monster_rc_right.bottom = _size_monster_rc.bottom;
			_distance_attack_monster_rc_left.bottom = _size_monster_rc.bottom;

			_size_monster_rc.top = _size_monster_rc.bottom - _size_monster_height;
			_distance_chk_player_rc.top = ((_size_monster_rc.bottom + _size_monster_rc.top) / 2) - (_distance_chk_player_height / 2);
			_distance_attack_monster_rc_right.top = _distance_attack_monster_rc_right.bottom - _distance_attack_monster_right_height;
			_distance_attack_monster_rc_left.top = _distance_attack_monster_rc_left.bottom - _distance_attack_monster_left_height;
			_counter_monsterJump = 0;
			_bJump_monster = false;
		}
	}
}
//아래 점프
void Monster::jump_down()
{
	//공사중
}
//몬스터 사망(사망이펙트 카운터가 0이 되었을때 몬스터가 진짜 사망(삭제)한다)
void Monster::dead_monster()
{
	static Item * item = nullptr;
	if (_hp <= 0)
	{
		SOUNDMANAGER->stop("Hit_monster");
		_counter_DeadEffect -= 1;
	}//hp0일때 사망이펙트 카운터를 세기 시작한다
	if (_counter_DeadEffect == 0)
	{
		POINT monsterFocus;
		monsterFocus.x = (_size_monster_rc.left + _size_monster_rc.right) / 2;
		monsterFocus.y = (_size_monster_rc.top + _size_monster_rc.bottom) / 2;
		_bDead_monster = true;
	}//사망이펙트 카운터가 0이 되었을때 사망한다

	if (_counter_DeadEffect == 29)
	{
		SOUNDMANAGER->play("die");
	}
	if (_counter_DeadEffect == 12)
	{
		SOUNDMANAGER->stop("die");
	}
}
//사망 이펙트(프레임을0으로 초기화한다)
void Monster::dead_effect()
{
	if (_counter_DeadEffect == 30)
	{
		_img_deadEffect->setFrameX(0);
	}//사망이펙트 카운터가 30일때 사망이펙트 프레임0으로 초기화
}
//데미지 이펙트(맞았는지 검사하고 데미지이펙트를 렌더하게끔만든다)
void Monster::damage_effect()
{
	if (_hpTemp != _hp)
	{
		SOUNDMANAGER->play("Hit_monster");
		_haveDamage = true;
		_hpTemp = _hp;
	}//hpTemp가 hp와 같지 않을때 맞았다고 판정, hpTemp에 hp값을 다시 넣어준다
	if (_haveDamage == true)
	{
		_counter_damageEffect -= 1;
	}//맞았다는 판정이나면 데미지이펙트 카운트를 센다
	if (_counter_damageEffect == 5)
	{
		SOUNDMANAGER->stop("Hit_monster");
	}
	if (_counter_damageEffect == 0)
	{
		_counter_damageEffect = 15;
		_haveDamage = false;
	}//이펙트 카운트가 0이면 이펙트카운트 재설정 및 맞았다는 판정 재설정
}
//추격 전까지 랜덤한 행동을 한다
void Monster::idle()
{
	if (_bChk_player == false)
	{
		if (_cooldown_idle_act == 0)
		{
			_rnd_idleAct_leftRight = RND->getFromIntTo(0, 2);
			_cooldown_idle_act = 100;
		}//idle카운트가 0일때 랜덤변수 설정, 카운트 재설정 
		if (_cooldown_idle_act != 0)
		{
			_cooldown_idle_act -= 1;
			switch (_rnd_idleAct_leftRight)
			{
			case 0:
				_bIs_moving = false;
				break;
			case 1:
				moveLeft();
				break;
			case 2:
				moveRight();
				break;
			}//0 : 움직임 멈춤, 1 : 왼쪽이동, 2 : 오른쪽이동
		}//idle카운트가 0이 아닐때
	}//플레이어 인식전
}
//랜덤한 행동을 한다 (공중 유닛)
void Monster::idle_airUnit()
{
	if (_cooldown_idle_act == 0)
	{
		_rnd_idleAct_leftRight = RND->getFromIntTo(0, 2);
		_rnd_idleAct_upDown = RND->getFromIntTo(3, 5);
		_cooldown_idle_act = 50;
	}//idle카운트가 0일때 랜덤변수 설정, 카운트 재설정 
	if (_cooldown_idle_act != 0)
	{
		_cooldown_idle_act -= 1;
		switch (_rnd_idleAct_leftRight)
		{
		case 0:

			break;
		case 1:
			moveLeft();
			break;
		case 2:
			moveRight();
			break;
		}//0 : 움직임 멈춤, 1 : 왼쪽이동, 2 : 오른쪽이동
		switch (_rnd_idleAct_upDown)
		{
		case 3:

			break;
		case 4:
			moveUp();
			break;
		case 5:
			moveDown();
			break;
		}//0 : 움직임 멈춤, 1 : 위로 이동, 2 : 아래로 이동
	}//idle카운트가 0이 아닐때
}
//=====================================================================
//== 					A	I		Melee Unit						 ==
//=====================================================================

//플레이어 찾기(인식범위렉트와 플레이어렉트 충돌검사)
void Monster::findPlayer()
{
	RECT temp;
	RECT tempPlayer = PLAYER->get_playerRC();
	if (IntersectRect(&temp, &_distance_chk_player_rc, &tempPlayer))
	{
		_bChk_player = true;
	}//인식범위렉트와 플레이어 렉트 충돌시 (플레이어 확인)
}
//플레이어 추격
void Monster::chasePlayer()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	if (_bChk_player == true && _bSwing_sword == false)
	{
		if (_cooldown_attack != 0)
		{
			_cooldown_attack -= 1;
		}//공격 쿨타임 계속 감소
		if (tempPlayer.right < ((_size_monster_rc.left + _size_monster_rc.right) / 2) +1)
		{
			moveLeft();
		}//플레이어가 몬스터사이즈보다 왼쪽에 있을때 왼쪽으로 이동
		else if (tempPlayer.left > ((_size_monster_rc.left + _size_monster_rc.right) / 2) -1)
		{
			moveRight();
		}//플레이어가 몬스터사이즈보다 오른쪽에 있을때 오른쪽으로 이동
		if (tempPlayer.top < _size_monster_rc.top - 9)
		{
			_bJump_monster = true;
		}//플레이어가 몬스터사이즈보다 위에 있을때 점프 활성화
	}//플레이어 인식했으나 공격하기 전
}
//플레이어 추격 (공중유닛)
void Monster::chasePlayer_airUnits()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	if (_bChk_player == true && _cooldown_attack !=0)
	{
		if (_cooldown_attack != 0)
		{
			_cooldown_attack -= 1;
		}//공격 쿨타임 계속 감소
		if ((tempPlayer.right+ tempPlayer.left) / 2 < ((_size_monster_rc.left + _size_monster_rc.right) / 2) + 1)
		{
			moveLeft();
		}//플레이어가 몬스터사이즈보다 왼쪽에 있을때 왼쪽으로 이동
		else if ((tempPlayer.right + tempPlayer.left) / 2 > ((_size_monster_rc.left + _size_monster_rc.right) / 2) - 1)
		{
			moveRight();
		}//플레이어가 몬스터사이즈보다 오른쪽에 있을때 오른쪽으로 이동
		if ((tempPlayer.top + tempPlayer.bottom) / 2 < ((_size_monster_rc.top + _size_monster_rc.bottom) / 2) + 1)
		{
			moveUp();
		}//플레이어가 몬스터사이즈보다 위에 있을때 위쪽으로 이동
		else if ((tempPlayer.top + tempPlayer.bottom) / 2 > ((_size_monster_rc.top + _size_monster_rc.bottom) / 2) - 1)
		{
			moveDown();
		}//플레이어가 몬스터사이즈보다 아래에 있을때 아래쪽으로 이동
	}//플레이어를 인식했으나 공격하기 전
}
//플레이어 추격 (skelDog)
void Monster::chasePlayer_dogs()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	RECT temp = { 0, };
	if (_bChk_player == true && _bAttackable_monster == false && _bRest == false)
	{
		if (_cooldown_attack != 0)
		{
			_cooldown_attack -= 1;
		}//공격 쿨타임 계속 감소
		if (tempPlayer.right < ((_size_monster_rc.left + _size_monster_rc.right) / 2) + 1)
		{
			moveLeft();
		}//플레이어가 몬스터사이즈보다 왼쪽에 있을때 왼쪽으로 이동
		else if (tempPlayer.left > ((_size_monster_rc.left + _size_monster_rc.right) / 2) - 1)
		{
			moveRight();
		}//플레이어가 몬스터사이즈보다 오른쪽에 있을때 오른쪽으로 이동
	}//플레이어를 인식했으나 공격가능 상태가 아니고 재충전 상태가 아닐때
}
//플레이어 추격 (minotaurs)
void Monster::chasePlayer_minotaurs()
{
	RECT temp;
	RECT tempPlayer = PLAYER->get_playerRC();
	if (_bChk_player == true && _bSwing_sword == false && _bDash == false)
	{
		if (_cooldown_attack != 0)
		{
			_cooldown_attack -= 1;
		}//공격 쿨타임 계속 감소
		if (tempPlayer.right < ((_size_monster_rc.left + _size_monster_rc.right) / 2) + 1)
		{
			_bShow_left = true;
		}//플레이어가 몬스터사이즈보다 왼쪽에 있을때 왼쪽을 바라본다
		else if (tempPlayer.left > ((_size_monster_rc.left + _size_monster_rc.right) / 2) - 1)
		{
			_bShow_left = false;
		}//플레이어가 몬스터사이즈보다 오른쪽에 있을때 오른쪽을 바라본다
	}//플레이어를 인식했으나 공격과 대시상태가 아닐때
	if (_cooldown_attack == 0 && _bSwing_sword == false)
	{
		if (IntersectRect(&temp, &_distance_chk_player_rc, &tempPlayer) == 0)
		{
			_bDash = true;
		}//추격범위를 벗어났을때 대쉬한다
	}//공격 쿨타임이 0이고 공격상태가 아닐때
}
//공격가능 상태 판별(warriors)
void Monster::compareAttack_warriors()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	if (tempPlayer.bottom >= _size_monster_rc.bottom-1 || tempPlayer.bottom <= _size_monster_rc.bottom + 1)
	{
		if (((tempPlayer.right+ tempPlayer.left )/2) >= _size_monster_rc.left-(tempPlayer.right - tempPlayer.left) &&
			((tempPlayer.right + tempPlayer.left) / 2) <= ((_size_monster_rc.right + _size_monster_rc.left) / 2))
		{
			_bAttackable_monster = true;

			if (_cooldown_attack == 0 && _bAttackable_monster == true)
			{
				_bSwing_sword = true;
			}//공격쿨타임이 0이고 공격가능상태 일때 공격 시작
		}//공격 사거리내에 플레이어가 있을경우 공격가능상태 활성화
		if (((tempPlayer.right + tempPlayer.left) / 2) <= _size_monster_rc.right+(tempPlayer.right - tempPlayer.left) &&
			((tempPlayer.right + tempPlayer.left) / 2) >= ((_size_monster_rc.right + _size_monster_rc.left) / 2))
		{
			_bAttackable_monster = true;

			if (_cooldown_attack == 0 && _bAttackable_monster == true)
			{
				_bSwing_sword = true;
			}//공격쿨타임이 0이고 공격가능상태 일때 공격시작
		}//공격 사거리내에 플레이어가 있을경우 공격가능상태 활성화
	}//플레이어와 몬스터의 위아래가 같을때
}
//공격가능 상태 판별(skelDog)
void Monster::compareAttack_dogs()
{		
	RECT tempPlayer = PLAYER->get_playerRC();
	RECT temp;
	if (IntersectRect(&temp, &_distance_chk_player_rc, &tempPlayer))
	{
		if (_cooldown_attack == 0 && _bRest == false)
		{
			_bAttackable_monster = true;
		}//공격쿨타임이 0이고 재충전 상태가 아닐때 공격가능상태 활성화
	}//공격 사거리 내에 플레이어가 있을때
//============================
//==	어디로 뛸지 결정		==
	if (_bAttackable_monster == true && _bChk_playerLocate_right == false)
	{
		if (tempPlayer.right < ((_size_monster_rc.left + _size_monster_rc.right) / 2) + 1)
		{
			_bChk_playerLocate_left = true;
		}//플레이어가 몬스터보다 왼쪽에 있을때 플레이어가 왼쪽에 있다고 판단
	}//공격가능상태이고 오른쪽에 있다고 판단하지 않았을때
	if (_bAttackable_monster == true && _bChk_playerLocate_left == false)
	{
		if (tempPlayer.left > ((_size_monster_rc.left + _size_monster_rc.right) / 2) - 1)
		{
			_bChk_playerLocate_right = true;
		}//플레이어가 몬스터보다 오른쪽에 있을때 플레이어가 오른쪽에 있다고 판단
	}//공격가능상태이고 왼쪽에 있다고 판단하지 않았을때
}
//공격가능 상태 판별(minotaurs)
void Monster::compareAttack_minotaurs()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	if (_cooldown_attack == 0 && _bDash == false)
	{
		_bSwing_sword = true;
	}//공격쿨타임이 0이고 대쉬하지 않을때 공격시작
}
//공격가능 상태 판별(Ghost)
void Monster::compareAttack_ghosts()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	if (_cooldown_attack == 0)
	{
		_bAttackable_monster = true;

		if (_bChk_player_locate == false)
		{
			RECT tempPlayer = PLAYER->get_playerRC();
			tempPlayerLocate = tempPlayer;
			_bChk_player_locate = true;
			getAngle_toPlayer = getAngle((float)((_size_monster_rc.right + _size_monster_rc.left) / 2), (float)((_size_monster_rc.top + _size_monster_rc.bottom) / 2),
				(float)((tempPlayerLocate.right + tempPlayerLocate.left) / 2), (float)((tempPlayerLocate.top + tempPlayerLocate.bottom) / 2));
		}//플레이어 위치를 확인하지 않았을때 플레이어의 위치를 확인하고 앵글값을 임시저장한다
	}//공격쿨타임이 0일때 공격가능 활성화
}
//공격 판정과 행동(warrior)
void Monster::attack_warriors()
{
	if (_bSwing_sword == true)
	{
		_bIs_moving = false;			//움직임을 멈춘다
		if (_cooldown_swing_sword != 0)
		{
			_cooldown_swing_sword -= 1;
		}//칼휘두르기 카운터가 0이될때까지 칼을 휘두른다
		if (_bAttackStart == true && _bGiveDamage == false && _cooldown_swing_sword <= 60)
		{
			if (_bShow_left == true)
			{
				RECT temp;
				RECT tempPlayer = PLAYER->get_playerRC();
				int playerhp = PLAYER->get_playerHP();
				if (IntersectRect(&temp, &_distance_attack_monster_rc_left, &tempPlayer))
				{
					playerhp -= 10;
					PLAYER->set_playerHP(playerhp);
					_bAttackStart = false;
					_bGiveDamage = true;
				}//왼쪽 공격사거리 내에 플레이어가 있었다면 플레이어는 데미지를 입는다
				 //공격을 끝내고 데미지를 주었음을 확인
			}//왼쪽을 바라보고 있을때
			if (_bShow_left == false && _bGiveDamage == false && _cooldown_swing_sword <= 60)
			{
				RECT temp;
				RECT tempPlayer = PLAYER->get_playerRC();
				int playerhp = PLAYER->get_playerHP();
				if (IntersectRect(&temp, &_distance_attack_monster_rc_right, &tempPlayer))
				{
					playerhp -= 10;
					PLAYER->set_playerHP(playerhp);
					_bAttackStart = false;
					_bGiveDamage = true;
				}//오른쪽 공격사거리 내에 플레이어가 있었다면 플레이어는 데미지를 입는다
				 //공격을 끝내고 데미지를 주었음을 확인
			}//오른쪽을 바라보고 있을때		
		}//공격을 시작하였고 데미지를 주기 전, 칼을 휘두르는 카운터가 60이하일때(칼이 중간쯤 왔다고 생각하면된다)
	}//공격시작이 활성화 되었을때
	if (_cooldown_swing_sword == 0 )
	{
		_bSwing_sword = false;
		_cooldown_swing_sword = _speed_swing_sword;
		_cooldown_attack = _speed_attack;
		_bGiveDamage = false;
	}//칼을 휘둘렀다면	휘두르는중과,데미지를 주었는가는 비활성화
	 //공격쿨타임 재설정, 검휘두르기 쿨타임 재설정
}
//공격 판정과 행동(skelDog)		공격가능상태일때 플레이어의 좌우를 판단했던 방향으로 이동및 점프, 충돌시 데미지
void Monster::attack_dogs()
{
	RECT temp;
	RECT tempPlayer = PLAYER->get_playerRC();
	int playerhp = PLAYER->get_playerHP();
	if (_bAttackable_monster == true && _bGiveDamage == false)
	{
		if (IntersectRect(&temp, &_size_monster_rc, &tempPlayer))
		{
			playerhp -= 10;
			PLAYER->set_playerHP(playerhp);
			_bGiveDamage = true;
		}//플레이어랑 부딪히면 플레이어는 데미지를 입는다		데미지를 주었음을 확인
	}//공격가능 상태이고 데미지를 주었음을 확인하기 전
	if (_bAttackable_monster == true)
	{
		if (_counter_monsterJump <= 30)
		{
			OffsetRect(&_size_monster_rc, 0, (int)(-(_speed_move + 2)));
			OffsetRect(&_distance_chk_player_rc, 0, (int)(-(_speed_move + 2)));
			_counter_monsterJump++;
		}
		if (_counter_monsterJump >= 30)
		{
			OffsetRect(&_size_monster_rc, 0, (int)(_speed_move + 3));
			OffsetRect(&_distance_chk_player_rc, 0, (int)(_speed_move + 3));
			_counter_monsterJump++;
		}
		if (_size_monster_rc.bottom >=  PLAYER->get_ground().top + 1)
		{
			_size_monster_rc.bottom =  PLAYER->get_ground().top + 1;
			_distance_chk_player_rc.bottom = ((_size_monster_rc.bottom + _size_monster_rc.top) / 2) + (_distance_chk_player_height / 2);
			_size_monster_rc.top = _size_monster_rc.bottom - _size_monster_height;
			_distance_chk_player_rc.top = ((_size_monster_rc.bottom + _size_monster_rc.top) / 2) - (_distance_chk_player_height / 2);
			_counter_monsterJump = 0;
			_bRest = true;
		}//점프가 끝나면 재중천상태로 돌입
	}//공격 가능상태일때 점프
	if (_bChk_playerLocate_left == true)
	{
		moveLeft();
		moveLeft();
		moveLeft();
	}//플레이어가 왼쪽에 있을거라 판단했을 때
	if (_bChk_playerLocate_right == true)
	{
		moveRight();
		moveRight();
		moveRight();
	}//플레이어가 오른쪽에 있을거라 판단했을 때
	if (_bRest == true)
	{
		_bIs_moving = false;
		_bChk_playerLocate_left = false;
		_bChk_playerLocate_right = false;
		_bAttackable_monster = false;
		_cooldown_attack = _speed_attack;
		_cooldown_recharge -= 1;
	}//재충전 상태일때 움직임을 멈춤, 플레이어 좌우판별 해제, 공격가능상태 해제, 공격쿨타임 초기화
	 //재충전 상태 쿨타임 감소
	if (_cooldown_recharge == 0)
	{
		_cooldown_recharge = _speed_recharge;
		_bRest = false;
		_bGiveDamage = false;
	}//재충전 상태 쿨타임0이 되면 공격쿨타임 재설정, 재충전상태 비활성화, 데미지를 입혔는가 여부도 비활성화
}	 //다시 행동하기 시작할거임
//공격 판정과 행동(minotaurs)
void Monster::attack_minotaurs()
{
	if (_bSwing_sword == true)
	{
		if (_cooldown_swing_sword != 0)
		{
			_cooldown_swing_sword -= 1;
		}//칼휘두르기 카운터가 0이될때까지 칼을 휘두른다
		if (_bAttackStart == true && _bGiveDamage == false && _cooldown_swing_sword <= 60)
		{
			if (_bShow_left == true)
			{
				RECT temp;
				RECT tempPlayer = PLAYER->get_playerRC();
				int playerhp = PLAYER->get_playerHP();
				if (IntersectRect(&temp, &_distance_attack_monster_rc_left, &tempPlayer))
				{
					playerhp -= 10;
					PLAYER->set_playerHP(playerhp);
					_bAttackStart = false;
					_bGiveDamage = true;
				}//왼쪽 공격사거리 내에 플레이어가 있었다면 플레이어는 데미지를 입는다
				 //공격을 끝내고 데미지를 주었음을 확인
			}//왼쪽을 바라보고 있을때
			if (_bShow_left == false && _bGiveDamage == false && _cooldown_swing_sword <= 60)
			{
				RECT temp;
				RECT tempPlayer = PLAYER->get_playerRC();
				int playerhp = PLAYER->get_playerHP();
				if (IntersectRect(&temp, &_distance_attack_monster_rc_right, &tempPlayer))
				{
					playerhp -= 10;
					PLAYER->set_playerHP(playerhp);
					_bAttackStart = false;
					_bGiveDamage = true;
				}//오른쪽 공격사거리 내에 플레이어가 있었다면 플레이어는 데미지를 입는다
				 //공격을 끝내고 데미지를 주었음을 확인
			}//오른쪽을 바라보고 있을때
		}//공격을 시작하였고 데미지를 주기 전, 칼을 휘두르는 카운터가 60이하일때(칼이 중간쯤 왔다고 생각하면된다)
	}//공격시작이 활성화 되었을때
	if (_cooldown_swing_sword == 0)
	{
		_bSwing_sword = false;
		_cooldown_swing_sword = _speed_swing_sword;
		_cooldown_attack = _speed_attack;
		_bGiveDamage = false;
	}//칼을 휘둘렀다면	휘두르는중과,데미지를 주었는가는 비활성화
	 //공격쿨타임 재설정, 검휘두르기 쿨타임 재설정
}
//공격 판정과 행동(ghost)
void Monster::attack_ghosts()
{
	RECT temp;
	RECT tempPlayer = PLAYER->get_playerRC();
	int playerhp = PLAYER->get_playerHP();
	if (_bAttackable_monster == true)
	{
		_counter_dash -= 1;
		if (_bGiveDamage == false)
		{
			if (IntersectRect(&temp, &_size_monster_rc, &tempPlayer))
			{
				playerhp -= 10;
				PLAYER->set_playerHP(playerhp);
				_bGiveDamage = true;
			}//플레이어와 몬스터가 충돌했다면 플레이어는 데미지를 입는다
			 //데미지를 주었음을 확인
		}//데미지를 주었음을 확인하기 전까지
	}//공격가능 상태일때 대쉬 카운터가 줄어든다
	if (_bAttackable_monster == true)
	{
	_size_monster_rc.left += (LONG)(cosf(getAngle_toPlayer)*_speed_move * 2);
	_size_monster_rc.right += (LONG)(cosf(getAngle_toPlayer)*_speed_move*2);
	_size_monster_rc.top += (LONG)(-sinf(getAngle_toPlayer)*_speed_move * 2);
	_size_monster_rc.bottom += (LONG)(-sinf(getAngle_toPlayer)*_speed_move * 2);
	_distance_chk_player_rc.left += (LONG)(cosf(getAngle_toPlayer)*_speed_move * 2);
	_distance_chk_player_rc.right += (LONG)(cosf(getAngle_toPlayer)*_speed_move * 2);
	_distance_chk_player_rc.top += (LONG)(-sinf(getAngle_toPlayer)*_speed_move * 2);
	_distance_chk_player_rc.bottom += (LONG)(-sinf(getAngle_toPlayer)*_speed_move * 2);
	}//공격 가능상태일때 앵글값으로 대쉬함
	if (_counter_dash == 0)
	{
		_bChk_player_locate = false;
		_bAttackable_monster = false;
		_bGiveDamage = false;
		_cooldown_attack = _speed_attack;
		_counter_dash = _speed_dash;
	}//대쉬 카운터가 0이되면		플레이어 위치확인여부 해제, 공격가능상태 해제
	//공격쿨타임 재설정, 대쉬 카운터 재설정
}
//대쉬 (minotaurs)
void Monster::dash_minotaurs()
{
//준비동작
	if (_bDash == true && _cooldown_recharge != 0)
	{
		_cooldown_recharge -= 1;
	}//대쉬 가능상태이고 충전시간이 0이 아닐때 충전시간 점차 감소
//대쉬!!!
	RECT temp;
	RECT tempPlayer = PLAYER->get_playerRC();
	int playerhp = PLAYER->get_playerHP();
	if (_cooldown_recharge == 0 && _bShow_left == true && _counter_dash != 0)
	{ 
		moveLeft();
		_counter_dash -= 1;
		if (IntersectRect(&temp, &_size_monster_rc, &tempPlayer))
		{
			playerhp -= 10;
			PLAYER->set_playerHP(playerhp);
			_counter_dash = 0;
		}//충돌시 플레이어는 데미지를 입고 대쉬 종료
	}//충전이 끝났고,대쉬카운터가 0이 아닐때 왼쪽을 바라보고 있으면 왼쪽으로 이동, 대쉬 카운터 줄어듬
	if (_cooldown_recharge == 0 && _bShow_left == false && _counter_dash != 0)
	{
		moveRight();
		_counter_dash -= 1;
		if (IntersectRect(&temp, &_size_monster_rc, &tempPlayer))
		{
			playerhp -= 10;
			PLAYER->set_playerHP(playerhp);
			_counter_dash = 0;
		}//충돌시 플레이어는 데미지를 입고 대쉬 종료
	}//충전이 끝났고, 대쉬카운터가 0이 아닐때 오른쪽을 바라보고 있으면 오른쪽으로 이동, 대쉬카운터 줄어듬
//대쉬 끝!
	if (_counter_dash == 0 && _bDash == true)
	{
		RECT tempPlayer = PLAYER->get_playerRC();
		if (tempPlayer.right < ((_size_monster_rc.left + _size_monster_rc.right) / 2) + 1)
		{
			_bShow_left = true;
			
		}//플레이어가 몬스터보다 왼쪽에 있으면 왼쪽을 바라봄
		else if (tempPlayer.left > ((_size_monster_rc.left + _size_monster_rc.right) / 2) - 1)
		{
			_bShow_left = false;
		}//플레이어가 몬스터보다 오른쪽에 있으면 오른쪽을 바라봄
	}//대쉬가 끝났을때
	if (_counter_dash == 0)
	{
		_bDash = false;
		_counter_dash = _speed_dash;
		_cooldown_recharge = _speed_recharge;
	}//대쉬가 끝났을떄 , 대쉬종료를 알리고 카운트와 공격쿨타임 재설정
}
//=====================================================================
//== 					A	I		range Unit						 ==
//=====================================================================

//미사일 생성 위치 설정
void Monster::init_focusforMissile()
{
	LONG width, height;
	width = (_size_monster_rc.right + _size_monster_rc.left);
	height = (_size_monster_rc.bottom + _size_monster_rc.top);
	_focus_forMissile.x = (LONG)(width * 0.5);
	_focus_forMissile.y = (LONG)(height * 0.5);
}
//미사일 생성 위치 설정(+ _focus_changeXY)
void Monster::init_focusforMissile_plusVar()
{
	LONG width, height;
	width = (_size_monster_rc.right + _size_monster_rc.left);
	height = (_size_monster_rc.bottom + _size_monster_rc.top);
	_focus_forMissile.x = (LONG)(width * 0.5) + _focus_changeX;
	_focus_forMissile.y = (LONG)(height * 0.5) + _focus_changeY;
}
//플레이를 향하는 앵글값
void Monster::angle_toPlayer()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	_bChk_player_locate = true;
	getAngle_toPlayer = getAngle((float)(_focus_forMissile.x), (float)(_focus_forMissile.y),
		(float)((tempPlayer.right + tempPlayer.left) / 2), (float)((tempPlayer.top + tempPlayer.bottom) / 2));
}
//미사일 만들기 (벡터 밀어주기)
void Monster::make_missile(Missile * missile)
{
	MISSILECONTROL->push_missile(missile);
}
//좌우 판별
void Monster::chasePlayer_RangeUnit()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	if (_bChk_player == true)
	{
		if (_cooldown_attack != 0)
		{
			_cooldown_attack -= 1;
		}//공격쿨타임이 0이 아닐때 공격쿨타임 감소
		if (tempPlayer.right < ((_size_monster_rc.left + _size_monster_rc.right) / 2) + 1)
		{
			_bShow_left = true;
		}//플레이어가 몬스터보다 왼쪽에 있을때 왼쪽을 바라봄
		else if (tempPlayer.left > ((_size_monster_rc.left + _size_monster_rc.right) / 2) - 1)
		{
			_bShow_left = false;
		}//플레이어가 몬스터보다 오른쪽 있을때 오른쪽을 바라봄
	}
}
//=====================================================================
//== 						B	O	S	S							 ==
//=====================================================================
//벨리알 생성
void Monster::init_beliar()
{
	_size_monster_rc = RectMake(425, 170, _size_monster_width, _size_monster_height);
	int beliarX = (_size_monster_rc.left + _size_monster_rc.right ) / 2;
	int beliarY = (_size_monster_rc.top + _size_monster_rc.bottom) / 2;

	_beliar_leftArm_rc = RectMakeCenter(beliarX - 325, beliarY + 100,
		_beliar_Arm_width, _beliar_Arm_height);
	_beliar_rightArm_rc = RectMakeCenter(beliarX + 325, beliarY - 100,
		_beliar_Arm_width, _beliar_Arm_height);
	int beliarLeftArmX = (_beliar_leftArm_rc.left + _beliar_leftArm_rc.right) / 2;
	int beliarLeftArmY = (_beliar_leftArm_rc.top + _beliar_leftArm_rc.bottom) / 2;
	int beliarRightArmX = (_beliar_rightArm_rc.left + _beliar_rightArm_rc.right) / 2;
	int beliarRightArmY = (_beliar_rightArm_rc.top + _beliar_rightArm_rc.bottom) / 2;

	_beliar_leftArm_attack_distance_rc = RectMakeCenter(beliarLeftArmX + 500, beliarLeftArmY,
		_beliar_Arm_attack_distance_width, _beliar_Arm_attack_distance_height);
	_beliar_rightArm_attack_distance_rc = RectMakeCenter(beliarRightArmX -500, beliarRightArmY,
		_beliar_Arm_attack_distance_width, _beliar_Arm_attack_distance_height);
}

//================================================
//##				debug : F1					##
//================================================
void Monster::show_rc()
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		if (_bShow_left == false)//오른쪽 공격범위
		{
			Rectangle(getMemDC(), _distance_attack_monster_rc_right.left, _distance_attack_monster_rc_right.top,
				_distance_attack_monster_rc_right.right, _distance_attack_monster_rc_right.bottom);
		}
		if (_bShow_left == true)//왼쪽 공격범위
		{
			Rectangle(getMemDC(), _distance_attack_monster_rc_left.left, _distance_attack_monster_rc_left.top,
				_distance_attack_monster_rc_left.right, _distance_attack_monster_rc_left.bottom);
		}
		//몬스터 그리기
		Rectangle(getMemDC(), _size_monster_rc.left, _size_monster_rc.top, _size_monster_rc.right, _size_monster_rc.bottom);
		//몬스터 추격 범위 그리기
		FrameRect(getMemDC(), &_distance_chk_player_rc, CreateSolidBrush(RGB(255, 0, 0)));
		//벨리알
		Rectangle(getMemDC(), _beliar_leftArm_rc.left, _beliar_leftArm_rc.top,
			_beliar_leftArm_rc.right, _beliar_leftArm_rc.bottom);
		Rectangle(getMemDC(), _beliar_rightArm_rc.left, _beliar_rightArm_rc.top,
			_beliar_rightArm_rc.right, _beliar_rightArm_rc.bottom);
		FrameRect(getMemDC(), &_beliar_leftArm_attack_distance_rc, CreateSolidBrush(RGB(255, 0, 0)));
		FrameRect(getMemDC(), &_beliar_rightArm_attack_distance_rc, CreateSolidBrush(RGB(255, 0, 0)));
		char str[128];
		wsprintf(str, "| 공격쿨타임 : %d | 칼 휘두르는 중 : %d | 충전중 : %d |", _cooldown_attack, _cooldown_swing_sword, _cooldown_recharge);
		TextOut(getMemDC(), ((_size_monster_rc.left + _size_monster_rc.right) /2 ) - 50, _size_monster_rc.top -150, str, strlen(str));

	}
}
//================================================================
//==				D E F A U L T   B A S E						==
//================================================================
Monster::Monster()
{
}
Monster::~Monster()
{
}
HRESULT Monster::init()
{	
	return S_OK;
}
void Monster::release()
{
}
void Monster::update()
{
}
void Monster::render()
{
}