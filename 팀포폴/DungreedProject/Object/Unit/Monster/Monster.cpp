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
//������ ��Ʈ ����
void Monster::init_monster_size_rc_ground()
{
	_size_monster_rc = RectMake(_spawnLocateMonsterX, PLAYER->get_ground().top - _size_monster_height, _size_monster_width, _size_monster_height);
}
void Monster::init_monster_size_rc_air()
{
	_size_monster_rc = RectMake(_spawnLocateMonsterX, _spawnLocateMonsterY, _size_monster_width, _size_monster_height);
}
//�߰� ���� ��Ʈ ����
void Monster::init_chk_distance_player_rc()
{
	_distance_chk_player_rc = RectMakeCenter((_size_monster_rc.left + _size_monster_rc.right) / 2,(_size_monster_rc.top + _size_monster_rc.bottom ) / 2,
		_distance_chk_player_width, _distance_chk_player_height);
}
//���� ��Ÿ� ��Ʈ ���� ����
void Monster::init_attack_distance_rc_left()
{
	_distance_attack_monster_rc_left = RectMake(_size_monster_rc.left - _distance_attack_monster_left_width + ((_size_monster_rc.right - _size_monster_rc.left) / 2), _size_monster_rc.bottom - _distance_attack_monster_left_height,
		_distance_attack_monster_left_width, _distance_attack_monster_left_height);
}
//���� ��Ÿ� ��Ʈ ������ ����
void Monster::init_attack_distance_rc_right()
{
	_distance_attack_monster_rc_right = RectMake(_size_monster_rc.right - ((_size_monster_rc.right-_size_monster_rc.left)/2), _size_monster_rc.bottom- _distance_attack_monster_left_height,
		_distance_attack_monster_right_width, _distance_attack_monster_right_height);
}


//====================================================================
//==				B A S I C	O P E R A T I O N	   				==
//====================================================================

//���� �̵�
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
//������ �̵�
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
//���� �̵� (��������)
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
//�Ʒ��� �̵� (��������)
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
//���� ����
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
//�Ʒ� ����
void Monster::jump_down()
{
	//������
}
//���� ���(�������Ʈ ī���Ͱ� 0�� �Ǿ����� ���Ͱ� ��¥ ���(����)�Ѵ�)
void Monster::dead_monster()
{
	static Item * item = nullptr;
	if (_hp <= 0)
	{
		SOUNDMANAGER->stop("Hit_monster");
		_counter_DeadEffect -= 1;
	}//hp0�϶� �������Ʈ ī���͸� ���� �����Ѵ�
	if (_counter_DeadEffect == 0)
	{
		POINT monsterFocus;
		monsterFocus.x = (_size_monster_rc.left + _size_monster_rc.right) / 2;
		monsterFocus.y = (_size_monster_rc.top + _size_monster_rc.bottom) / 2;
		_bDead_monster = true;
	}//�������Ʈ ī���Ͱ� 0�� �Ǿ����� ����Ѵ�

	if (_counter_DeadEffect == 29)
	{
		SOUNDMANAGER->play("die");
	}
	if (_counter_DeadEffect == 12)
	{
		SOUNDMANAGER->stop("die");
	}
}
//��� ����Ʈ(��������0���� �ʱ�ȭ�Ѵ�)
void Monster::dead_effect()
{
	if (_counter_DeadEffect == 30)
	{
		_img_deadEffect->setFrameX(0);
	}//�������Ʈ ī���Ͱ� 30�϶� �������Ʈ ������0���� �ʱ�ȭ
}
//������ ����Ʈ(�¾Ҵ��� �˻��ϰ� ����������Ʈ�� �����ϰԲ������)
void Monster::damage_effect()
{
	if (_hpTemp != _hp)
	{
		SOUNDMANAGER->play("Hit_monster");
		_haveDamage = true;
		_hpTemp = _hp;
	}//hpTemp�� hp�� ���� ������ �¾Ҵٰ� ����, hpTemp�� hp���� �ٽ� �־��ش�
	if (_haveDamage == true)
	{
		_counter_damageEffect -= 1;
	}//�¾Ҵٴ� �����̳��� ����������Ʈ ī��Ʈ�� ����
	if (_counter_damageEffect == 5)
	{
		SOUNDMANAGER->stop("Hit_monster");
	}
	if (_counter_damageEffect == 0)
	{
		_counter_damageEffect = 15;
		_haveDamage = false;
	}//����Ʈ ī��Ʈ�� 0�̸� ����Ʈī��Ʈ �缳�� �� �¾Ҵٴ� ���� �缳��
}
//�߰� ������ ������ �ൿ�� �Ѵ�
void Monster::idle()
{
	if (_bChk_player == false)
	{
		if (_cooldown_idle_act == 0)
		{
			_rnd_idleAct_leftRight = RND->getFromIntTo(0, 2);
			_cooldown_idle_act = 100;
		}//idleī��Ʈ�� 0�϶� �������� ����, ī��Ʈ �缳�� 
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
			}//0 : ������ ����, 1 : �����̵�, 2 : �������̵�
		}//idleī��Ʈ�� 0�� �ƴҶ�
	}//�÷��̾� �ν���
}
//������ �ൿ�� �Ѵ� (���� ����)
void Monster::idle_airUnit()
{
	if (_cooldown_idle_act == 0)
	{
		_rnd_idleAct_leftRight = RND->getFromIntTo(0, 2);
		_rnd_idleAct_upDown = RND->getFromIntTo(3, 5);
		_cooldown_idle_act = 50;
	}//idleī��Ʈ�� 0�϶� �������� ����, ī��Ʈ �缳�� 
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
		}//0 : ������ ����, 1 : �����̵�, 2 : �������̵�
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
		}//0 : ������ ����, 1 : ���� �̵�, 2 : �Ʒ��� �̵�
	}//idleī��Ʈ�� 0�� �ƴҶ�
}
//=====================================================================
//== 					A	I		Melee Unit						 ==
//=====================================================================

//�÷��̾� ã��(�νĹ�����Ʈ�� �÷��̾Ʈ �浹�˻�)
void Monster::findPlayer()
{
	RECT temp;
	RECT tempPlayer = PLAYER->get_playerRC();
	if (IntersectRect(&temp, &_distance_chk_player_rc, &tempPlayer))
	{
		_bChk_player = true;
	}//�νĹ�����Ʈ�� �÷��̾� ��Ʈ �浹�� (�÷��̾� Ȯ��)
}
//�÷��̾� �߰�
void Monster::chasePlayer()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	if (_bChk_player == true && _bSwing_sword == false)
	{
		if (_cooldown_attack != 0)
		{
			_cooldown_attack -= 1;
		}//���� ��Ÿ�� ��� ����
		if (tempPlayer.right < ((_size_monster_rc.left + _size_monster_rc.right) / 2) +1)
		{
			moveLeft();
		}//�÷��̾ ���ͻ������ ���ʿ� ������ �������� �̵�
		else if (tempPlayer.left > ((_size_monster_rc.left + _size_monster_rc.right) / 2) -1)
		{
			moveRight();
		}//�÷��̾ ���ͻ������ �����ʿ� ������ ���������� �̵�
		if (tempPlayer.top < _size_monster_rc.top - 9)
		{
			_bJump_monster = true;
		}//�÷��̾ ���ͻ������ ���� ������ ���� Ȱ��ȭ
	}//�÷��̾� �ν������� �����ϱ� ��
}
//�÷��̾� �߰� (��������)
void Monster::chasePlayer_airUnits()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	if (_bChk_player == true && _cooldown_attack !=0)
	{
		if (_cooldown_attack != 0)
		{
			_cooldown_attack -= 1;
		}//���� ��Ÿ�� ��� ����
		if ((tempPlayer.right+ tempPlayer.left) / 2 < ((_size_monster_rc.left + _size_monster_rc.right) / 2) + 1)
		{
			moveLeft();
		}//�÷��̾ ���ͻ������ ���ʿ� ������ �������� �̵�
		else if ((tempPlayer.right + tempPlayer.left) / 2 > ((_size_monster_rc.left + _size_monster_rc.right) / 2) - 1)
		{
			moveRight();
		}//�÷��̾ ���ͻ������ �����ʿ� ������ ���������� �̵�
		if ((tempPlayer.top + tempPlayer.bottom) / 2 < ((_size_monster_rc.top + _size_monster_rc.bottom) / 2) + 1)
		{
			moveUp();
		}//�÷��̾ ���ͻ������ ���� ������ �������� �̵�
		else if ((tempPlayer.top + tempPlayer.bottom) / 2 > ((_size_monster_rc.top + _size_monster_rc.bottom) / 2) - 1)
		{
			moveDown();
		}//�÷��̾ ���ͻ������ �Ʒ��� ������ �Ʒ������� �̵�
	}//�÷��̾ �ν������� �����ϱ� ��
}
//�÷��̾� �߰� (skelDog)
void Monster::chasePlayer_dogs()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	RECT temp = { 0, };
	if (_bChk_player == true && _bAttackable_monster == false && _bRest == false)
	{
		if (_cooldown_attack != 0)
		{
			_cooldown_attack -= 1;
		}//���� ��Ÿ�� ��� ����
		if (tempPlayer.right < ((_size_monster_rc.left + _size_monster_rc.right) / 2) + 1)
		{
			moveLeft();
		}//�÷��̾ ���ͻ������ ���ʿ� ������ �������� �̵�
		else if (tempPlayer.left > ((_size_monster_rc.left + _size_monster_rc.right) / 2) - 1)
		{
			moveRight();
		}//�÷��̾ ���ͻ������ �����ʿ� ������ ���������� �̵�
	}//�÷��̾ �ν������� ���ݰ��� ���°� �ƴϰ� ������ ���°� �ƴҶ�
}
//�÷��̾� �߰� (minotaurs)
void Monster::chasePlayer_minotaurs()
{
	RECT temp;
	RECT tempPlayer = PLAYER->get_playerRC();
	if (_bChk_player == true && _bSwing_sword == false && _bDash == false)
	{
		if (_cooldown_attack != 0)
		{
			_cooldown_attack -= 1;
		}//���� ��Ÿ�� ��� ����
		if (tempPlayer.right < ((_size_monster_rc.left + _size_monster_rc.right) / 2) + 1)
		{
			_bShow_left = true;
		}//�÷��̾ ���ͻ������ ���ʿ� ������ ������ �ٶ󺻴�
		else if (tempPlayer.left > ((_size_monster_rc.left + _size_monster_rc.right) / 2) - 1)
		{
			_bShow_left = false;
		}//�÷��̾ ���ͻ������ �����ʿ� ������ �������� �ٶ󺻴�
	}//�÷��̾ �ν������� ���ݰ� ��û��°� �ƴҶ�
	if (_cooldown_attack == 0 && _bSwing_sword == false)
	{
		if (IntersectRect(&temp, &_distance_chk_player_rc, &tempPlayer) == 0)
		{
			_bDash = true;
		}//�߰ݹ����� ������� �뽬�Ѵ�
	}//���� ��Ÿ���� 0�̰� ���ݻ��°� �ƴҶ�
}
//���ݰ��� ���� �Ǻ�(warriors)
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
			}//������Ÿ���� 0�̰� ���ݰ��ɻ��� �϶� ���� ����
		}//���� ��Ÿ����� �÷��̾ ������� ���ݰ��ɻ��� Ȱ��ȭ
		if (((tempPlayer.right + tempPlayer.left) / 2) <= _size_monster_rc.right+(tempPlayer.right - tempPlayer.left) &&
			((tempPlayer.right + tempPlayer.left) / 2) >= ((_size_monster_rc.right + _size_monster_rc.left) / 2))
		{
			_bAttackable_monster = true;

			if (_cooldown_attack == 0 && _bAttackable_monster == true)
			{
				_bSwing_sword = true;
			}//������Ÿ���� 0�̰� ���ݰ��ɻ��� �϶� ���ݽ���
		}//���� ��Ÿ����� �÷��̾ ������� ���ݰ��ɻ��� Ȱ��ȭ
	}//�÷��̾�� ������ ���Ʒ��� ������
}
//���ݰ��� ���� �Ǻ�(skelDog)
void Monster::compareAttack_dogs()
{		
	RECT tempPlayer = PLAYER->get_playerRC();
	RECT temp;
	if (IntersectRect(&temp, &_distance_chk_player_rc, &tempPlayer))
	{
		if (_cooldown_attack == 0 && _bRest == false)
		{
			_bAttackable_monster = true;
		}//������Ÿ���� 0�̰� ������ ���°� �ƴҶ� ���ݰ��ɻ��� Ȱ��ȭ
	}//���� ��Ÿ� ���� �÷��̾ ������
//============================
//==	���� ���� ����		==
	if (_bAttackable_monster == true && _bChk_playerLocate_right == false)
	{
		if (tempPlayer.right < ((_size_monster_rc.left + _size_monster_rc.right) / 2) + 1)
		{
			_bChk_playerLocate_left = true;
		}//�÷��̾ ���ͺ��� ���ʿ� ������ �÷��̾ ���ʿ� �ִٰ� �Ǵ�
	}//���ݰ��ɻ����̰� �����ʿ� �ִٰ� �Ǵ����� �ʾ�����
	if (_bAttackable_monster == true && _bChk_playerLocate_left == false)
	{
		if (tempPlayer.left > ((_size_monster_rc.left + _size_monster_rc.right) / 2) - 1)
		{
			_bChk_playerLocate_right = true;
		}//�÷��̾ ���ͺ��� �����ʿ� ������ �÷��̾ �����ʿ� �ִٰ� �Ǵ�
	}//���ݰ��ɻ����̰� ���ʿ� �ִٰ� �Ǵ����� �ʾ�����
}
//���ݰ��� ���� �Ǻ�(minotaurs)
void Monster::compareAttack_minotaurs()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	if (_cooldown_attack == 0 && _bDash == false)
	{
		_bSwing_sword = true;
	}//������Ÿ���� 0�̰� �뽬���� ������ ���ݽ���
}
//���ݰ��� ���� �Ǻ�(Ghost)
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
		}//�÷��̾� ��ġ�� Ȯ������ �ʾ����� �÷��̾��� ��ġ�� Ȯ���ϰ� �ޱ۰��� �ӽ������Ѵ�
	}//������Ÿ���� 0�϶� ���ݰ��� Ȱ��ȭ
}
//���� ������ �ൿ(warrior)
void Monster::attack_warriors()
{
	if (_bSwing_sword == true)
	{
		_bIs_moving = false;			//�������� �����
		if (_cooldown_swing_sword != 0)
		{
			_cooldown_swing_sword -= 1;
		}//Į�ֵθ��� ī���Ͱ� 0�̵ɶ����� Į�� �ֵθ���
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
				}//���� ���ݻ�Ÿ� ���� �÷��̾ �־��ٸ� �÷��̾�� �������� �Դ´�
				 //������ ������ �������� �־����� Ȯ��
			}//������ �ٶ󺸰� ������
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
				}//������ ���ݻ�Ÿ� ���� �÷��̾ �־��ٸ� �÷��̾�� �������� �Դ´�
				 //������ ������ �������� �־����� Ȯ��
			}//�������� �ٶ󺸰� ������		
		}//������ �����Ͽ��� �������� �ֱ� ��, Į�� �ֵθ��� ī���Ͱ� 60�����϶�(Į�� �߰��� �Դٰ� �����ϸ�ȴ�)
	}//���ݽ����� Ȱ��ȭ �Ǿ�����
	if (_cooldown_swing_sword == 0 )
	{
		_bSwing_sword = false;
		_cooldown_swing_sword = _speed_swing_sword;
		_cooldown_attack = _speed_attack;
		_bGiveDamage = false;
	}//Į�� �ֵѷ��ٸ�	�ֵθ����߰�,�������� �־��°��� ��Ȱ��ȭ
	 //������Ÿ�� �缳��, ���ֵθ��� ��Ÿ�� �缳��
}
//���� ������ �ൿ(skelDog)		���ݰ��ɻ����϶� �÷��̾��� �¿츦 �Ǵ��ߴ� �������� �̵��� ����, �浹�� ������
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
		}//�÷��̾�� �ε����� �÷��̾�� �������� �Դ´�		�������� �־����� Ȯ��
	}//���ݰ��� �����̰� �������� �־����� Ȯ���ϱ� ��
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
		}//������ ������ ����õ���·� ����
	}//���� ���ɻ����϶� ����
	if (_bChk_playerLocate_left == true)
	{
		moveLeft();
		moveLeft();
		moveLeft();
	}//�÷��̾ ���ʿ� �����Ŷ� �Ǵ����� ��
	if (_bChk_playerLocate_right == true)
	{
		moveRight();
		moveRight();
		moveRight();
	}//�÷��̾ �����ʿ� �����Ŷ� �Ǵ����� ��
	if (_bRest == true)
	{
		_bIs_moving = false;
		_bChk_playerLocate_left = false;
		_bChk_playerLocate_right = false;
		_bAttackable_monster = false;
		_cooldown_attack = _speed_attack;
		_cooldown_recharge -= 1;
	}//������ �����϶� �������� ����, �÷��̾� �¿��Ǻ� ����, ���ݰ��ɻ��� ����, ������Ÿ�� �ʱ�ȭ
	 //������ ���� ��Ÿ�� ����
	if (_cooldown_recharge == 0)
	{
		_cooldown_recharge = _speed_recharge;
		_bRest = false;
		_bGiveDamage = false;
	}//������ ���� ��Ÿ��0�� �Ǹ� ������Ÿ�� �缳��, ���������� ��Ȱ��ȭ, �������� �����°� ���ε� ��Ȱ��ȭ
}	 //�ٽ� �ൿ�ϱ� �����Ұ���
//���� ������ �ൿ(minotaurs)
void Monster::attack_minotaurs()
{
	if (_bSwing_sword == true)
	{
		if (_cooldown_swing_sword != 0)
		{
			_cooldown_swing_sword -= 1;
		}//Į�ֵθ��� ī���Ͱ� 0�̵ɶ����� Į�� �ֵθ���
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
				}//���� ���ݻ�Ÿ� ���� �÷��̾ �־��ٸ� �÷��̾�� �������� �Դ´�
				 //������ ������ �������� �־����� Ȯ��
			}//������ �ٶ󺸰� ������
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
				}//������ ���ݻ�Ÿ� ���� �÷��̾ �־��ٸ� �÷��̾�� �������� �Դ´�
				 //������ ������ �������� �־����� Ȯ��
			}//�������� �ٶ󺸰� ������
		}//������ �����Ͽ��� �������� �ֱ� ��, Į�� �ֵθ��� ī���Ͱ� 60�����϶�(Į�� �߰��� �Դٰ� �����ϸ�ȴ�)
	}//���ݽ����� Ȱ��ȭ �Ǿ�����
	if (_cooldown_swing_sword == 0)
	{
		_bSwing_sword = false;
		_cooldown_swing_sword = _speed_swing_sword;
		_cooldown_attack = _speed_attack;
		_bGiveDamage = false;
	}//Į�� �ֵѷ��ٸ�	�ֵθ����߰�,�������� �־��°��� ��Ȱ��ȭ
	 //������Ÿ�� �缳��, ���ֵθ��� ��Ÿ�� �缳��
}
//���� ������ �ൿ(ghost)
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
			}//�÷��̾�� ���Ͱ� �浹�ߴٸ� �÷��̾�� �������� �Դ´�
			 //�������� �־����� Ȯ��
		}//�������� �־����� Ȯ���ϱ� ������
	}//���ݰ��� �����϶� �뽬 ī���Ͱ� �پ���
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
	}//���� ���ɻ����϶� �ޱ۰����� �뽬��
	if (_counter_dash == 0)
	{
		_bChk_player_locate = false;
		_bAttackable_monster = false;
		_bGiveDamage = false;
		_cooldown_attack = _speed_attack;
		_counter_dash = _speed_dash;
	}//�뽬 ī���Ͱ� 0�̵Ǹ�		�÷��̾� ��ġȮ�ο��� ����, ���ݰ��ɻ��� ����
	//������Ÿ�� �缳��, �뽬 ī���� �缳��
}
//�뽬 (minotaurs)
void Monster::dash_minotaurs()
{
//�غ���
	if (_bDash == true && _cooldown_recharge != 0)
	{
		_cooldown_recharge -= 1;
	}//�뽬 ���ɻ����̰� �����ð��� 0�� �ƴҶ� �����ð� ���� ����
//�뽬!!!
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
		}//�浹�� �÷��̾�� �������� �԰� �뽬 ����
	}//������ ������,�뽬ī���Ͱ� 0�� �ƴҶ� ������ �ٶ󺸰� ������ �������� �̵�, �뽬 ī���� �پ��
	if (_cooldown_recharge == 0 && _bShow_left == false && _counter_dash != 0)
	{
		moveRight();
		_counter_dash -= 1;
		if (IntersectRect(&temp, &_size_monster_rc, &tempPlayer))
		{
			playerhp -= 10;
			PLAYER->set_playerHP(playerhp);
			_counter_dash = 0;
		}//�浹�� �÷��̾�� �������� �԰� �뽬 ����
	}//������ ������, �뽬ī���Ͱ� 0�� �ƴҶ� �������� �ٶ󺸰� ������ ���������� �̵�, �뽬ī���� �پ��
//�뽬 ��!
	if (_counter_dash == 0 && _bDash == true)
	{
		RECT tempPlayer = PLAYER->get_playerRC();
		if (tempPlayer.right < ((_size_monster_rc.left + _size_monster_rc.right) / 2) + 1)
		{
			_bShow_left = true;
			
		}//�÷��̾ ���ͺ��� ���ʿ� ������ ������ �ٶ�
		else if (tempPlayer.left > ((_size_monster_rc.left + _size_monster_rc.right) / 2) - 1)
		{
			_bShow_left = false;
		}//�÷��̾ ���ͺ��� �����ʿ� ������ �������� �ٶ�
	}//�뽬�� ��������
	if (_counter_dash == 0)
	{
		_bDash = false;
		_counter_dash = _speed_dash;
		_cooldown_recharge = _speed_recharge;
	}//�뽬�� �������� , �뽬���Ḧ �˸��� ī��Ʈ�� ������Ÿ�� �缳��
}
//=====================================================================
//== 					A	I		range Unit						 ==
//=====================================================================

//�̻��� ���� ��ġ ����
void Monster::init_focusforMissile()
{
	LONG width, height;
	width = (_size_monster_rc.right + _size_monster_rc.left);
	height = (_size_monster_rc.bottom + _size_monster_rc.top);
	_focus_forMissile.x = (LONG)(width * 0.5);
	_focus_forMissile.y = (LONG)(height * 0.5);
}
//�̻��� ���� ��ġ ����(+ _focus_changeXY)
void Monster::init_focusforMissile_plusVar()
{
	LONG width, height;
	width = (_size_monster_rc.right + _size_monster_rc.left);
	height = (_size_monster_rc.bottom + _size_monster_rc.top);
	_focus_forMissile.x = (LONG)(width * 0.5) + _focus_changeX;
	_focus_forMissile.y = (LONG)(height * 0.5) + _focus_changeY;
}
//�÷��̸� ���ϴ� �ޱ۰�
void Monster::angle_toPlayer()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	_bChk_player_locate = true;
	getAngle_toPlayer = getAngle((float)(_focus_forMissile.x), (float)(_focus_forMissile.y),
		(float)((tempPlayer.right + tempPlayer.left) / 2), (float)((tempPlayer.top + tempPlayer.bottom) / 2));
}
//�̻��� ����� (���� �о��ֱ�)
void Monster::make_missile(Missile * missile)
{
	MISSILECONTROL->push_missile(missile);
}
//�¿� �Ǻ�
void Monster::chasePlayer_RangeUnit()
{
	RECT tempPlayer = PLAYER->get_playerRC();
	if (_bChk_player == true)
	{
		if (_cooldown_attack != 0)
		{
			_cooldown_attack -= 1;
		}//������Ÿ���� 0�� �ƴҶ� ������Ÿ�� ����
		if (tempPlayer.right < ((_size_monster_rc.left + _size_monster_rc.right) / 2) + 1)
		{
			_bShow_left = true;
		}//�÷��̾ ���ͺ��� ���ʿ� ������ ������ �ٶ�
		else if (tempPlayer.left > ((_size_monster_rc.left + _size_monster_rc.right) / 2) - 1)
		{
			_bShow_left = false;
		}//�÷��̾ ���ͺ��� ������ ������ �������� �ٶ�
	}
}
//=====================================================================
//== 						B	O	S	S							 ==
//=====================================================================
//������ ����
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
		if (_bShow_left == false)//������ ���ݹ���
		{
			Rectangle(getMemDC(), _distance_attack_monster_rc_right.left, _distance_attack_monster_rc_right.top,
				_distance_attack_monster_rc_right.right, _distance_attack_monster_rc_right.bottom);
		}
		if (_bShow_left == true)//���� ���ݹ���
		{
			Rectangle(getMemDC(), _distance_attack_monster_rc_left.left, _distance_attack_monster_rc_left.top,
				_distance_attack_monster_rc_left.right, _distance_attack_monster_rc_left.bottom);
		}
		//���� �׸���
		Rectangle(getMemDC(), _size_monster_rc.left, _size_monster_rc.top, _size_monster_rc.right, _size_monster_rc.bottom);
		//���� �߰� ���� �׸���
		FrameRect(getMemDC(), &_distance_chk_player_rc, CreateSolidBrush(RGB(255, 0, 0)));
		//������
		Rectangle(getMemDC(), _beliar_leftArm_rc.left, _beliar_leftArm_rc.top,
			_beliar_leftArm_rc.right, _beliar_leftArm_rc.bottom);
		Rectangle(getMemDC(), _beliar_rightArm_rc.left, _beliar_rightArm_rc.top,
			_beliar_rightArm_rc.right, _beliar_rightArm_rc.bottom);
		FrameRect(getMemDC(), &_beliar_leftArm_attack_distance_rc, CreateSolidBrush(RGB(255, 0, 0)));
		FrameRect(getMemDC(), &_beliar_rightArm_attack_distance_rc, CreateSolidBrush(RGB(255, 0, 0)));
		char str[128];
		wsprintf(str, "| ������Ÿ�� : %d | Į �ֵθ��� �� : %d | ������ : %d |", _cooldown_attack, _cooldown_swing_sword, _cooldown_recharge);
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