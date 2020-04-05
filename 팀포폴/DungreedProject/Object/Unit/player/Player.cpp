#include "stdafx.h"
#include "Player.h"


void Player::player_Camera()
{
	if (_focousplayerX < WINSIZEX / 2) { CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, _focousplayerY-150)); }
	else if (_focousplayerX > _backGroundImg->getWidth() - (WINSIZEX / 2)) { CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, _focousplayerY-150)); }
	else{CAMERAMANAGER->setCameraCenter(PointMake(_focousplayerX, _focousplayerY-150));}
}
void Player::player_Dash()
{
	if ((_player_DashPointX > _playerRC.left-50&&_player_DashPointX < _playerRC.right+50) && _player_DashPointY < _playerRC.top)
	{
		_dashWay = DASH_UP;
		
	}
	else if (_player_DashPointX < _focousplayerX)
	{
		_dashWay = DASH_LEFT;
	}
	else if (_player_DashPointX > _focousplayerX)
	{
		_dashWay = DASH_RIGHT;
	}

	else
	{
		if (_playDashGage < _player_MaxDashCount)
		{
			_playDashGage++;
		}
		else
		{
			_playDashGage = _player_MaxDashCount;
		}
	}
	
	/*else
	{
		_dashWay = DASH_NONE;
	}*/

}
void Player::player_DashMove()
{
	if (_dashWay == DASH_LEFT || _dashWay == DASH_RIGHT)
	{
		_playerMove = Move;
	}
	else if (_dashWay == DASH_UP)
	{
		_playerMove = Jump;
	}
	if (_player_DashDistanceCount < 30)
	{
		switch (_dashWay)
		{
		case DASH_LEFT:
			_playerRC.left -= 10;
			_playerRC.right -= 10;

			break;
		case DASH_RIGHT:
			_playerRC.left += 10;
			_playerRC.right += 10;
			break;
			case DASH_UP:
				_playerRC.top -= 20;
				_playerRC.bottom -= 20;
				break;
			//case DASH_DOWN:
			//	break;
			//case DASH_NONE:
			//	break;
			//
		}
	}
	else
	{
		b_isDash = false;
		_player_DashDistanceCount =0;
	}

	if (!b_isDash)
	{
		_dashWay = DASH_NONE;
	}
	
}
void Player::player_DashCharge()
{
	if (!b_isDash)
	{
		_player_DashCount++;
		if (_player_DashCount > 100)
		{
			if (_playDashGage < 3)
			{
				_playDashGage++;
			}
			else
			{
				_playDashGage = _player_MaxDashCount;
			}
			_player_DashCount = 0;
		}
	}
}
void Player::Player_PixelCollision()
{

	int _playerY = (21 * _PLAYER_RECT_NUM) / 2;
	
	
	_playerProbeY = _focousplayerY + _playerY;
	
		
		for (int i = _focousplayerY;i < _playerProbeY+10; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				COLORREF color = GetPixel(_backGroundImg->getMemDC(), _focousplayerX, i);

				r = GetRValue(color);
				g = GetGValue(color);
				b = GetBValue(color);
				if (!(r == 255 && g == 0 && b == 255))
				{
					_focousplayerY = i - _playerY;
					b_isPixelOn = false;

					break;
				}
				else
				{
					b_isPixelOn = true;
				}
			}
		}
		if (b_isPixelOn)
		{
			//마젠타가 아니면 렉트의 bottom하고 top을 다시 잡는다.
			_playerRC.bottom = _focousplayerY + ((21 * _PLAYER_RECT_NUM) / 2);
			_playerRC.top = _playerRC.bottom - (21 * _PLAYER_RECT_NUM);
		}
	
}
void Player::delete_itemListAll()
{
	auto iter = _itemList.begin();
	for (;iter != _itemList.end();)
	{
		iter = _itemList.erase(iter);
	}
	swap(_itemList, vItems());
}
void Player::weapon_RCMake()
{
	//위쪽
	//LEFTtop
	_weaponRC[0] = RectMakeCenter(_focousplayerX-10, (_playerRC.top - (_weapon_UpDown->getFrameHeight() / 2)) + 10, _weapon_UpDown->getFrameWidth(), _weapon_UpDown->getFrameHeight());
	//RIGHTtop
	_weaponRC[1] = RectMakeCenter(_focousplayerX+10, (_playerRC.top - (_weapon_UpDown->getFrameHeight() / 2)) + 10, _weapon_UpDown->getFrameWidth(), _weapon_UpDown->getFrameHeight());
	//오른쪽
	_weaponRC[2] = RectMakeCenter((_playerRC.right + (_weapon_LeftRight->getFrameWidth() / 2) - 10), _focousplayerY, _weapon_LeftRight->getFrameWidth(), _weapon_LeftRight->getFrameHeight());
	//아래
	//LEFTbottom
	_weaponRC[3] = RectMakeCenter(_focousplayerX-10, (_playerRC.bottom + (_weapon_UpDown->getFrameHeight() / 2) - 10), _weapon_UpDown->getFrameWidth(), _weapon_UpDown->getFrameHeight());
	//RIGHTbottom
	_weaponRC[4] = RectMakeCenter(_focousplayerX+10, (_playerRC.bottom + (_weapon_UpDown->getFrameHeight() / 2) - 10), _weapon_UpDown->getFrameWidth(), _weapon_UpDown->getFrameHeight());
	//왼쪽
	_weaponRC[5] = RectMakeCenter((_playerRC.left - (_weapon_LeftRight->getFrameWidth() / 2) + 10), _focousplayerY, _weapon_LeftRight->getFrameWidth(), _weapon_LeftRight->getFrameHeight());
}
void Player::weapon_Render()
{

		switch (_renderWay)
		{
		case render_RIGHTTOP:
			if (_renderCount < 20)
			{
				_weapon_UpDown->frameRender(getMemDC(), _weaponRC[1].left, _weaponRC[1].top, 0, 0);
			}
			else
			{
				_weapon_UpDown->frameRender(getMemDC(), _weaponRC[4].left, _weaponRC[4].top, 1, 0);
			}
			break;
		case render_TOP:
			if (_renderCount < 20)
			{
				_weapon_LeftRight->frameRender(getMemDC(), _weaponRC[2].left, _weaponRC[2].top, 1, 0);
			}
			else
			{
				_weapon_LeftRight->frameRender(getMemDC(), _weaponRC[5].left, _weaponRC[5].top, 0, 0);
			}
			break;
		case render_LEFTTOP:
			if (_renderCount < 20)
			{
				_weapon_UpDown->frameRender(getMemDC(), _weaponRC[0].left, _weaponRC[0].top, 0, 0);
			}
			else
			{
				_weapon_UpDown->frameRender(getMemDC(), _weaponRC[3].left, _weaponRC[3].top, 1, 0);//LEFT
			}
			break;
		case render_LEFT:
			if (_renderCount < 20)
			{
				_weapon_UpDown->frameRender(getMemDC(), _weaponRC[0].left, _weaponRC[0].top, 0, 0);
			}
			else
			{
				_weapon_UpDown->frameRender(getMemDC(), _weaponRC[3].left, _weaponRC[3].top, 1, 0);//LEFT
			}
			break;
		case render_LEFTBOTTOM:
			if (_renderCount < 20)
			{
				_weapon_UpDown->frameRender(getMemDC(), _weaponRC[3].left, _weaponRC[3].top, 1, 0);
			}
			else
			{
				_weapon_UpDown->frameRender(getMemDC(), _weaponRC[0].left, _weaponRC[0].top, 0, 0);
			}
			break;
		case render_BOTTOM:
			if (_renderCount < 20)
			{
				_weapon_LeftRight->frameRender(getMemDC(), _weaponRC[2].left, _weaponRC[2].top, 1, 0);
			}
			else
			{
				_weapon_LeftRight->frameRender(getMemDC(), _weaponRC[5].left, _weaponRC[5].top, 0, 0);
			}
			break;
		case render_RIGHTBOTTOM:
			if (_renderCount < 20)
			{
				_weapon_UpDown->frameRender(getMemDC(), _weaponRC[4].left, _weaponRC[4].top, 1, 0);
			}
			else
			{
				_weapon_UpDown->frameRender(getMemDC(), _weaponRC[1].left, _weaponRC[1].top, 0, 0);
			}
			break;
		case render_RIGHT:
			if (_renderCount < 20)
			{
				_weapon_UpDown->frameRender(getMemDC(), _weaponRC[1].left, _weaponRC[1].top, 0, 0);
			}
			else
			{
				_weapon_UpDown->frameRender(getMemDC(), _weaponRC[4].left, _weaponRC[4].top, 1, 0);
			}
			break;
		}
	
}
void Player::renderWay()
{
	if (_playerAtkMouseX > _playerRC.right&&_playerAtkMouseY < _playerRC.top)//RIGHTtop
	{
		_renderWay = render_RIGHTTOP;
	}
	else if (_playerAtkMouseX < _playerRC.right&&_playerAtkMouseX >= _playerRC.left&&_playerAtkMouseY < _playerRC.top)//top
	{
		_renderWay = render_TOP;
	}
	else if (_playerAtkMouseX < _playerRC.left&&_playerAtkMouseY < _playerRC.top)//lefttop
	{
		_renderWay = render_LEFTTOP;
	}
	else if (_playerAtkMouseX < _playerRC.left&&_playerAtkMouseY > _playerRC.top&&_playerAtkMouseY <= _playerRC.bottom)//left
	{
		_renderWay = render_LEFT;
	}
	else if (_playerAtkMouseX < _playerRC.left&&_playerAtkMouseY > _playerRC.bottom)//leftbottom
	{
		_renderWay = render_LEFTBOTTOM;
	}
	else if (_playerAtkMouseX > _playerRC.left&&_playerAtkMouseX < _playerRC.right&&_playerAtkMouseY > _playerRC.bottom)//bottom
	{
		_renderWay = render_BOTTOM;
	}
	else if (_playerAtkMouseX > _playerRC.right&&_playerAtkMouseY > _playerRC.bottom)//rightbottom
	{
		_renderWay = render_RIGHTBOTTOM;
	}
	else if (_playerAtkMouseX > _playerRC.right&&_playerAtkMouseY > _playerRC.top&&_playerAtkMouseY < _playerRC.bottom)//right
	{
		_renderWay = render_RIGHT;
	}
}
void Player::_effect_RectMake()
{
	//leftSwing
	_effectRC[0] = RectMake(_playerAtkRC[0].player_AtkRC.left, _playerAtkRC[0].player_AtkRC.top,
		getDistance(_playerAtkRC[0].player_AtkRC.left, _playerAtkRC[0].player_AtkRC.top, _playerAtkRC[0].player_AtkRC.right, _playerAtkRC[0].player_AtkRC.top),
		getDistance(_playerAtkRC[0].player_AtkRC.left, _playerAtkRC[0].player_AtkRC.top, _playerAtkRC[5].player_AtkRC.left, _playerAtkRC[5].player_AtkRC.bottom));
	//rightSwing
	_effectRC[1] = RectMake(_playerAtkRC[1].player_AtkRC.left, _playerAtkRC[1].player_AtkRC.top,
		getDistance(_playerAtkRC[1].player_AtkRC.left, _playerAtkRC[1].player_AtkRC.top, _playerAtkRC[1].player_AtkRC.right, _playerAtkRC[1].player_AtkRC.top),
		getDistance(_playerAtkRC[1].player_AtkRC.left, _playerAtkRC[1].player_AtkRC.top, _playerAtkRC[4].player_AtkRC.left, _playerAtkRC[4].player_AtkRC.bottom));
	//topSwing
	_effectRC[2]= RectMake(_playerAtkRC[0].player_AtkRC.left, _playerAtkRC[0].player_AtkRC.top,
		getDistance(_playerAtkRC[0].player_AtkRC.left, _playerAtkRC[0].player_AtkRC.top, _playerAtkRC[1].player_AtkRC.right, _playerAtkRC[1].player_AtkRC.top),
		getDistance(_playerAtkRC[0].player_AtkRC.left, _playerAtkRC[0].player_AtkRC.top, _playerAtkRC[0].player_AtkRC.left, _playerAtkRC[7].player_AtkRC.bottom));
	//bottomSwing
	_effectRC[3] = RectMake(_playerAtkRC[6].player_AtkRC.left, _playerAtkRC[6].player_AtkRC.top,
		getDistance(_playerAtkRC[6].player_AtkRC.left, _playerAtkRC[6].player_AtkRC.top, _playerAtkRC[3].player_AtkRC.right, _playerAtkRC[3].player_AtkRC.top),
		getDistance(_playerAtkRC[6].player_AtkRC.left, _playerAtkRC[6].player_AtkRC.top, _playerAtkRC[5].player_AtkRC.left, _playerAtkRC[5].player_AtkRC.bottom));
}
void Player::_effect_Render()
{
	int _playerY = (21 * _PLAYER_RECT_NUM) / 2;

	switch (_renderWay)
	{
	case render_RIGHTTOP:
		if (_renderCount >= 21)
		{
			_effect_SwingLeft->render(getMemDC(), _effectRC[1].left, _effectRC[1].top);
		}
		break;
	case render_TOP:
		if (_renderCount >= 21)
		{
			_effect_SwingTop->render(getMemDC(), _effectRC[2].left, _effectRC[2].top);
		}
		break;
	case render_LEFTTOP:
		if (_renderCount >= 21)
		{
			_effect_SwingRight->render(getMemDC(), _effectRC[0].left, _effectRC[0].top);
		}
		break;
	case render_LEFT:
		if (_renderCount >= 21)
		{
			_effect_SwingRight->render(getMemDC(), _effectRC[0].left, _effectRC[0].top);
		}
		break;
	case render_LEFTBOTTOM:
		if (_renderCount >= 21)
		{
			_effect_SwingRight->render(getMemDC(), _effectRC[0].left, _effectRC[0].top);
		}
		break;
	case render_BOTTOM:
		if (_renderCount >= 21)
		{
			_effect_SwingBottom->render(getMemDC(), _effectRC[3].left, _effectRC[3].top);
		}
		break;
	case render_RIGHTBOTTOM:
		if (_renderCount >= 21)
		{
			_effect_SwingLeft->render(getMemDC(), _effectRC[1].left, _effectRC[1].top);
		}
		break;
	case render_RIGHT:
		if (_renderCount >= 21)
		{
			_effect_SwingLeft->render(getMemDC(), _effectRC[1].left, _effectRC[1].top);
		}
	break;
	}
}
void Player::update_sounds()
{
}
void Player::player_AtkRCMake()
{
	_playerAtkRC[0].player_AtkRC = RectMake(_playerRC.left- _playerWeaponHeight,
											_playerRC.top-_playerWeaponHeight,
											getDistance (_playerRC.left - _playerWeaponHeight, _playerRC.top - _playerWeaponHeight, _focousplayerX, _playerRC.top - _playerWeaponHeight), 
											_playerWeaponHeight);
	_playerAtkRC[1].player_AtkRC = RectMake(_focousplayerX,
											_playerRC.top-_playerWeaponHeight,
											getDistance(_focousplayerX, _playerRC.top - _playerWeaponHeight,_playerRC.right+ _playerWeaponHeight, _playerRC.top - _playerWeaponHeight),
											_playerWeaponHeight);
	_playerAtkRC[2].player_AtkRC = RectMake(_playerRC.right,
											_playerRC.top,
											getDistance(_playerRC.right, _playerRC.top, _playerRC.right+ _playerWeaponHeight, _playerRC.top),
											getDistance(_playerRC.right, _playerRC.top, _playerRC.right, _focousplayerY));
	_playerAtkRC[3].player_AtkRC = RectMake(_playerRC.right,
											_focousplayerY,
											getDistance(_playerRC.right, _playerRC.bottom, _playerRC.right + _playerWeaponHeight, _playerRC.bottom),
											getDistance(_playerRC.right, _focousplayerY, _playerRC.right, _playerRC.bottom));
	_playerAtkRC[4].player_AtkRC = RectMake(_focousplayerX,
											_playerRC.bottom ,
											getDistance(_focousplayerX, _playerRC.bottom, _playerRC.right + _playerWeaponHeight , _playerRC.bottom),
											_playerWeaponHeight);
	_playerAtkRC[5].player_AtkRC = RectMake(_playerRC.left- _playerWeaponHeight,
											_playerRC.bottom,
											getDistance(_playerRC.left - _playerWeaponHeight, _playerRC.bottom, _focousplayerX, _playerRC.bottom),
											_playerWeaponHeight);

	_playerAtkRC[6].player_AtkRC = RectMake(_playerRC.left- _playerWeaponHeight,
											_focousplayerY,
											getDistance(_playerRC.left, _focousplayerY, _playerRC.left- _playerWeaponHeight, _focousplayerY),
											getDistance(_playerRC.left, _focousplayerY, _playerRC.left, _playerRC.bottom));
	_playerAtkRC[7].player_AtkRC = RectMake(_playerRC.left- _playerWeaponHeight,
											_playerRC.top,
											getDistance(_playerRC.left- _playerWeaponHeight,_playerRC.top,_playerRC.left,_playerRC.top),
											getDistance(_playerRC.left, _focousplayerY, _playerRC.left, _playerRC.top));



	for (int i = 0; i < 8; i++)
	{
		_playerAtkRC[i].b_isAtkRC = false;
		_playerAtkRC[i].playerAtkHeight= _playerWeaponHeight;
	}
}
void Player::player_AtkWay()
{
	
	if (_playerAtkMouseX > _playerRC.right&&_playerAtkMouseY < _playerRC.top)//RIGHTtop
	{
		_playerAtkway = RIGHTTOP;
	}
	else if (_playerAtkMouseX < _playerRC.right&&_playerAtkMouseX >= _playerRC.left&&_playerAtkMouseY < _playerRC.top)//top
	{
		_playerAtkway = TOP;
	}
	else if (_playerAtkMouseX < _playerRC.left&&_playerAtkMouseY < _playerRC.top)//lefttop
	{
		_playerAtkway = LEFTTOP;
	}
	else if (_playerAtkMouseX < _playerRC.left&&_playerAtkMouseY > _playerRC.top&&_playerAtkMouseY <= _playerRC.bottom)//left
	{
		_playerAtkway = LEFT;
	}
	else if (_playerAtkMouseX < _playerRC.left&&_playerAtkMouseY > _playerRC.bottom)//leftbottom
	{
		_playerAtkway = LEFTBOTTOM;
	}
	else if (_playerAtkMouseX > _playerRC.left&&_playerAtkMouseX < _playerRC.right&&_playerAtkMouseY > _playerRC.bottom)//bottom
	{
		_playerAtkway = BOTTOM;
	}
	else if (_playerAtkMouseX > _playerRC.right&&_playerAtkMouseY > _playerRC.bottom)//rightbottom
	{
		_playerAtkway = RIGHTBOTTOM;
	}
	else if (_playerAtkMouseX > _playerRC.right&&_playerAtkMouseY > _playerRC.top&&_playerAtkMouseY < _playerRC.bottom)//right
	{
		_playerAtkway = RIGHT;
	}
	
}
void Player::player_ATKRenge()
{
	if (b_isATK)
	{
		switch (_playerAtkway)
		{
		case RIGHTTOP:
			_playerAtkRC[1].b_isAtkRC = true;
			_playerAtkRC[2].b_isAtkRC = true;
			break;
		case TOP:
			_playerAtkRC[0].b_isAtkRC = true;
			_playerAtkRC[1].b_isAtkRC = true;
			break;
		case LEFTTOP:
			_playerAtkRC[0].b_isAtkRC = true;
			_playerAtkRC[7].b_isAtkRC = true;
			break;
		case LEFT:
			_playerAtkRC[6].b_isAtkRC = true;
			_playerAtkRC[7].b_isAtkRC = true;
			break;
		case LEFTBOTTOM:
			_playerAtkRC[6].b_isAtkRC = true;
			_playerAtkRC[5].b_isAtkRC = true;
			break;
		case BOTTOM:
			_playerAtkRC[5].b_isAtkRC = true;
			_playerAtkRC[4].b_isAtkRC = true;
			break;
		case RIGHTBOTTOM:
			_playerAtkRC[3].b_isAtkRC = true;
			_playerAtkRC[4].b_isAtkRC = true;
			break;
		case RIGHT:
			_playerAtkRC[2].b_isAtkRC = true;
			_playerAtkRC[3].b_isAtkRC = true;
			break;
		case NONE:
			for (int i = 0; i < 8; i++)
			{
				_playerAtkRC[i].b_isAtkRC = false;
			}
			break;
		}
	}
}
void Player::player_ATK()
{
	if (b_isATK)
	{
		_playerAtkCount++;
		if(_playerAtkCount > 30)
		{
			b_isATK = false;
		}
	}
	if (!b_isATK)
	{
		_playerAtkCount=0;
		_playerAtkway = NONE;
	}
}
void Player::player_Move()
{
	if (_playerWay == Left)
	{
		switch (_playerMove)
		{
		case Idle:
			_playerimg = IMAGEMANAGER->findImage("LEFT_IDLE");
			_playerani = IMAGEMANAGER->findAnimation("LEFT_IDLE");
			_playerani->start();
			break;
		case Move:
			_playerimg = IMAGEMANAGER->findImage("LEFT_MOVE");
			_playerani = IMAGEMANAGER->findAnimation("LEFT_MOVE");
			_playerani->start();
			break;
		case Jump:
			_playerimg = IMAGEMANAGER->findImage("LEFT_JUMP");
			break;
		}
	}
	else if (_playerWay == Right)
	{
		switch (_playerMove)
		{

		case Idle:
			_playerimg = IMAGEMANAGER->findImage("RIGHT_IDLE");
			_playerani = IMAGEMANAGER->findAnimation("RIGHT_IDLE");
			_playerani->start();
			break;
		case Move:
			_playerimg = IMAGEMANAGER->findImage("RIGHT_MOVE");
			_playerani = IMAGEMANAGER->findAnimation("RIGHT_MOVE");
			_playerani->start();
			break;
		case Jump:
			_playerimg = IMAGEMANAGER->findImage("RIGHT_JUMP");
			break;

		}
	}
}
void Player::player_Jump()
{
	if (b_isJump)
	{
		_playerMove = Jump;
		_playerJumpGravity = 0.5f;
		_playerRC.top -= _playerJumpPower;
		_playerRC.bottom -= _playerJumpPower;
		_playerJumpPower -= _playerJumpGravity;
		/*if (_playerRC.top <200)
		{
			b_isMAXJump = true;
			b_isJump = false;
		}*/
	}
	if((!b_isJump|| b_isMAXJump))
	{
		_playerJumpGravity = 10.0f;
		_playerRC.top += _playerJumpGravity;
		_playerRC.bottom += _playerJumpGravity;
	}
}
void Player::player_JumpDown()
{
	int _playerY = (21 * _PLAYER_RECT_NUM) / 2;
	
	_jumpDownplayerProbeY = _focousplayerY + _playerY;

	for (int i = _focousplayerY; i < _jumpDownplayerProbeY + 10; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			COLORREF color = GetPixel(_backGroundImg->getMemDC(), _focousplayerX, i);

			jumpDown_r = GetRValue(color);
			jumpDown_g = GetGValue(color);
			jumpDown_b = GetBValue(color);
			if (!(r == 255 && g == 0 && b == 255))
			{
			
				b_isJumpDown = false;
				b_isPixelCollision = false;
				_jumpDownCount++;
				break;
			}
			else
			{
				b_isJumpDown = true;
			}
		}
	}
	if (b_isJumpDown)
	{
		_playerMove = Jump;
		_playerJumpGravity = 10.0f;
		_playerRC.top += _playerJumpGravity;
		_playerRC.bottom += _playerJumpGravity;
		
	} 
	if (_jumpDownCount > 20)
	{
		b_isPixelCollision = true;
		_jumpDownCount = 0;
	}
}
void Player::player_Focus()
{
	//플레이어 방향 지정
	if (m_ptMouse.x+ CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 < _playerRC.right)
	{
		_playerWay = Left;
	}
	if (m_ptMouse.x + CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 > _playerRC.right)
	{
		_playerWay = Right;
	}
}
void Player::player_LeftMove()
{
	_playerframeSpeed = 0.18;
	_playerMove = Move;
	OffsetRect(&_playerRC, -_playerSpeed, 0);

	if ((KEYMANAGER->isStayKeyDown(VK_SPACE)|| KEYMANAGER->isStayKeyDown('W')) && !b_isMAXJump)
	{
		_playerJumpPower = 5.0f;
		b_isJump = true;
		b_isPixelCollision = false;
	}
}
void Player::player_RightMove()
{
	_playerframeSpeed = 0.18;
	_playerMove = Move;
	OffsetRect(&_playerRC, _playerSpeed, 0);
	if ((KEYMANAGER->isStayKeyDown(VK_SPACE) || KEYMANAGER->isStayKeyDown('W')) && !b_isMAXJump)
	{
		_playerJumpPower = 5.0f;
		b_isJump = true;
		b_isPixelCollision = false;
	}
}
void Player::player_Idle()
{
	_playerMove = Idle;
	_playerframeSpeed = 0.15;
	if ((KEYMANAGER->isStayKeyDown(VK_SPACE) || KEYMANAGER->isStayKeyDown('W')) && !b_isMAXJump)
	{
		_playerJumpPower = 5.0f;
		b_isJump = true;
		b_isPixelCollision = false;
	}
}
void Player::player_State()
{
	RECT temp;
	//바닥이 아니면 픽셀 검출을 하고
	if (IntersectRect(&temp, &_playerRC, &_stage->getGroud()))
	{
		b_isPixelCollision = false;
		b_isJump = false;
		b_isMAXJump = false;
		_playerRC.bottom = _stage->getGroud().top;
		_playerRC.top = _playerRC.bottom - (21 * _PLAYER_RECT_NUM);
		if (b_isLeft || b_isRight)
		{
			_playerMove = Move;
		}
		else
		{
			_playerMove = Idle;
		}
	}
	//만약 픽셀이 마젠타에 멈춰있으면 b_isPixelOn이다.
	else if(b_isPixelOn)
	{
		b_isPixelCollision = true;
		if (b_isLeft||b_isRight)
		{
			_playerMove = Move;
		}
		else
		{
			_playerMove = Idle;
		}
	}
	else
	{
		_playerMove = Jump;
	}
	
	
}
void Player::player_Die()
{
	if (_playerHP <= 0)
	{
	b_isDie = true;
	_playerimg= IMAGEMANAGER->findImage("Die");
	_playerMove = Die;
	_playerRC = RectMakeCenter(_focousplayerX,_focousplayerY+5, 21 * _PLAYER_RECT_NUM, 17 * _PLAYER_RECT_NUM);
	}
}
////////////////////////////////////////////////////////
Player::Player()
{
}
Player::~Player()
{
}
void Player::stage_Make(SCENE_KIND scencekind)
{
	_stage->stage_Make(scencekind);
	_ground = _stage->getGroud();
	_sceneKind = scencekind;
}
////////////////////////////////////////////////////////
HRESULT Player::init()
{
	//아이들상태
	IMAGEMANAGER->addFrame("LEFT_IDLE", "resource/image/플레이어/왼쪽아이들.bmp", 68 * _PLAYER_RECT_NUM, 21 * _PLAYER_RECT_NUM, 4, 1, 1);
	IMAGEMANAGER->addFrame("RIGHT_IDLE", "resource/image/플레이어/오른쪽아이들.bmp", 68 * _PLAYER_RECT_NUM, 21 * _PLAYER_RECT_NUM, 4, 1, 1);
	//이동
	IMAGEMANAGER->addFrame("LEFT_MOVE", "resource/image/플레이어/왼쪽이동.bmp", 238 * _PLAYER_RECT_NUM, 21 * _PLAYER_RECT_NUM, 14, 1, 1);
	IMAGEMANAGER->addFrame("RIGHT_MOVE", "resource/image/플레이어/오른쪽이동.bmp", 238 * _PLAYER_RECT_NUM, 21 * _PLAYER_RECT_NUM, 14, 1, 1);
	//점프
	IMAGEMANAGER->addImage("LEFT_JUMP", "resource/image/플레이어/왼쪽점프.bmp", 17 * _PLAYER_RECT_NUM, 21 * _PLAYER_RECT_NUM, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RIGHT_JUMP", "resource/image/플레이어/오른쪽점프.bmp", 17 * _PLAYER_RECT_NUM, 21 * _PLAYER_RECT_NUM, true, RGB(255, 0, 255));
	//플레이어다이
	IMAGEMANAGER->addImage("Die","resource/image/플레이어/다이.bmp", 21 * _PLAYER_RECT_NUM, 17 * _PLAYER_RECT_NUM, true, RGB(255, 0, 255));
	//플레이어공격이펙트
	//swing
	IMAGEMANAGER->addImage("Left_Swing","resource/image/플레이어/swing/좌이펙터.bmp",70,142, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Right_Swing","resource/image/플레이어/swing/우이펙터.bmp",70,142, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Top_Swing","resource/image/플레이어/swing/위이펙터.bmp",140,70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Bottom_Swing","resource/image/플레이어/swing/아래이펙터.bmp",140,70, true, RGB(255, 0, 255));



	//플레이어 테스트 
	IMAGEMANAGER->addFrameImage("단검위아래","resource/image/웨폰/위아래공격.bmp",14*3,18*3,2,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("단검좌우","resource/image/웨폰/왼쪽오른쪽공격.bmp",36*3,7*3,2,1, true, RGB(255, 0, 255));




	_stage = new stage;
	_stage -> init();

	_playerWay = Left;
	_playerMove = Idle;
	_playerimg = IMAGEMANAGER->findImage("LEFT_IDLE");
	_playerani = IMAGEMANAGER->findAnimation("LEFT_IDLE");
	_playerani->start();
	_playerRC = RectMakeCenter(WINSIZEX / 2, (WINSIZEY / 2)+200, 17 * _PLAYER_RECT_NUM, 21 * _PLAYER_RECT_NUM);
	//CAMERAMANAGER->setCemraCenter(PointMake(0,600));

	///////////플레이어 공격/////////
	_playerWeaponHeight = 50;
	_playerAtkway = NONE;
	_playerAtkCount = 0;
	
	///////////////////////////////////
	/////////////플레이어 스테이터스///////////////
	_playerSpeed = 3;
	_playerHP = 80;
	_playerAtk = 10;
	/////////////////////////////////////////////

	_weapon_UpDown = IMAGEMANAGER->findImage("단검위아래");
	_weapon_LeftRight = IMAGEMANAGER->findImage("단검좌우");

	/////////////////////////////////////////////
	_effect_SwingLeft= IMAGEMANAGER->findImage("Left_Swing");
	_effect_SwingRight= IMAGEMANAGER->findImage("Right_Swing");
	_effect_SwingTop= IMAGEMANAGER->findImage("Top_Swing");
	_effect_SwingBottom = IMAGEMANAGER->findImage("Bottom_Swing");





	//////////////////////////////////////////////
	_dashWay = DASH_NONE;
	_playDashGage = 3;
	_player_DashDistanceCount = 0;
	_player_DashCount = 0;
	/////////////////////////////////////

	_jumpDownCount = 0;

	////////픽셀충돌////////////
	//플레이어 만의 배경
	IMAGEMANAGER->addImage("플레이어배경", "resource/image/배경/맵(플레이어수정)2.bmp", 4200, 1200, true, RGB(255, 0, 255));
	_backGroundImg = IMAGEMANAGER->findImage("플레이어배경");
	
		
	b_isPixelCollision = true;
	b_isATK = false;
	b_isJump = false; 
	b_isMAXJump = false;
	b_isDash = false;
	b_isDie = false;
	b_isAtkrender = false;
	////////디버그////////
	b_Debug = false;
	/////////////////////
	return S_OK;
}
void Player::release()
{
	IMAGEMANAGER->deleteImage("LEFT_IDLE");
	IMAGEMANAGER->deleteImage("RIGHT_IDLE");
	IMAGEMANAGER->deleteImage("LEFT_MOVE");
	IMAGEMANAGER->deleteImage("RIGHT_MOVE");
	IMAGEMANAGER->deleteImage("LEFT_JUMP");
	IMAGEMANAGER->deleteImage("RIGHT_JUMP");
	IMAGEMANAGER->deleteImage("Die");
	IMAGEMANAGER->deleteImage("단검위아래");
	IMAGEMANAGER->deleteImage("단검좌우");
	IMAGEMANAGER->deleteImage("Left_Swing");
	IMAGEMANAGER->deleteImage("Right_Swing");
	IMAGEMANAGER->deleteImage("Top_Swing");
	IMAGEMANAGER->deleteImage("Bottom_Swing");


	IMAGEMANAGER->deleteImage("플레이어배경");

	_stage->release();
	SAFE_DELETE(_stage);
} 
//================================================
//##					업데이트					##
//================================================
void Player::update()
{
	// 여기서 배경은 업데이트
	update_sounds();
	if (!b_isDie)
	{
		player_Focus();
		_focousplayerX = _playerRC.right - (_playerRC.right - _playerRC.left) / 2;
		_focousplayerY = _playerRC.bottom - (_playerRC.bottom - _playerRC.top) / 2;
		player_Camera();
		//찬호 백그라운드 고정시키기 위한 렉트
		_playerbackGround = RectMakeCenter(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y, WINSIZEX, WINSIZEY);

		player_Idle();

		if (KEYMANAGER->isStayKeyDown('S'))
		{
			player_JumpDown();
		}
		if (KEYMANAGER->isStayKeyDown('A'))//left_rc
		{
			player_LeftMove();
			b_isLeft = true;
		}
		if (KEYMANAGER->isStayKeyDown('D'))//right_rc
		{
			b_isRight = true;
			player_RightMove();
		}
		if (KEYMANAGER->isOnceKeyUp('A'))
		{
			b_isLeft = false;
		}
		if (KEYMANAGER->isOnceKeyUp('D'))
		{
			b_isRight = false;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_SPACE) || KEYMANAGER->isOnceKeyUp('W'))
		{
			b_isPixelCollision = true;
		}
		if (!b_isJump)
		{
			b_isPixelCollision = true;
		}

		player_Jump();
		//만약픽셀 충돌이 on 되면
		if (b_isPixelCollision)
		{
			Player_PixelCollision();
		}

		//플레이어 상태
		player_State();




		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_playerAtkMouseX = m_ptMouse.x + CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2;
			_playerAtkMouseY = m_ptMouse.y + CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2;
			renderWay();
			b_isAllATK = true;
			b_isATK = true;
			b_LbuttonDown = true;
		}
		else { b_LbuttonDown = false; }
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			b_LbuttonUp = true;
		}
		else { b_LbuttonUp = false; }
		if (b_isAllATK&& (b_isATK||!b_isATK))
		{
			b_isAtkrender = true;
			_renderCount++;
		}
		if (_renderCount > 30)
		{
			b_isAtkrender = false;
			b_isAllATK = false;
			_renderCount = 0;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _playDashGage > 0)
		{
			_playDashGage--;
			_player_DashPointX = m_ptMouse.x + CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2;
			_player_DashPointY = m_ptMouse.y + CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2;
			b_isDash = true;
			player_Dash();
		}
		if (b_isDash)
		{
			_player_DashDistanceCount++;
			player_DashMove();
		}




		player_DashCharge();
		player_AtkRCMake();
		player_AtkWay();
		player_ATKRenge();
		weapon_RCMake();
		_effect_RectMake();
		player_ATK();



		_playerani->frameUpdate(_playerframeSpeed);

		player_Move();//움직이는 이미지
		player_Die();
	}



	//////////////////////////////////////////////////
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		SCENEMANAGER->changeScene("startscene");
	}
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		_playDashGage++;
		_playerJumpGravity = 0.5f;
	}
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		_playerHP = 80;
		if(b_isDie)
		{
		b_isDie = !b_isDie;
		}
	}

	//================================================
	//##				디버그 : F1					##
	//================================================
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		b_Debug = !b_Debug;
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		b_isPixelCollision = !b_isPixelCollision;
	}
}


void Player::render()
{

	if (b_Debug)
	{
		_backGroundImg->render(getMemDC());
		char str[128];
		wsprintf(str, "| 플레이어 무브 : %d |플레이어 HP : %d|공격 : %d|%d",_playerMove, _playerHP, b_isATK, _focousplayerX);
		TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 - 400, 0, str, strlen(str));
		char str2[128];
		wsprintf(str2, "| _playerAtkMouseX : %d | _playerAtkMouseY : %d |%d|%d|공격시간 : %d|%d|%d|", _playerAtkMouseX, _playerAtkMouseY,m_ptMouse.x,m_ptMouse.y,_playerAtkCount, _renderCount, _playerAtkway);
		TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 - 300, 25, str2, strlen(str2));
		char str3[128];
		wsprintf(str3, "| 대쉬 게이지  : %d|%d|", _playDashGage, _dashWay);
		TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 - 300, 50, str3, strlen(str3));
		char str4[128];
		wsprintf(str4, "| R : %d| G : %d| B : %d |b_isPixelCollision : %d|b_pixel : %d |b_isJump : %d|jumpDownCount: %d",100,100,100, b_isPixelCollision, b_isPixelOn, b_isJump, _jumpDownCount);
		TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 - 300, 75 , str4, strlen(str4));
		

		Rectangle(getMemDC(), _stage->getGroud().left, _stage->getGroud().top, _stage->getGroud().right, _stage->getGroud().bottom);
		for (int i = 0; i < 8; i++)
		{
				//Rectangle(getMemDC(), _playerAtkRC[i].player_AtkRC.left, _playerAtkRC[i].player_AtkRC.top, _playerAtkRC[i].player_AtkRC.right, _playerAtkRC[i].player_AtkRC.bottom);
			if (_playerAtkRC[i].b_isAtkRC)
			{
				TextOut(getMemDC(), _playerAtkRC[i].player_AtkRC.right - (_playerAtkRC[i].player_AtkRC.right - _playerAtkRC[i].player_AtkRC.left) / 2,
					_playerAtkRC[i].player_AtkRC.bottom - (_playerAtkRC[i].player_AtkRC.bottom - _playerAtkRC[i].player_AtkRC.top) / 2, "O", strlen("O"));
			}
			else
			{
				TextOut(getMemDC(), _playerAtkRC[i].player_AtkRC.right - (_playerAtkRC[i].player_AtkRC.right - _playerAtkRC[i].player_AtkRC.left) / 2,
					_playerAtkRC[i].player_AtkRC.bottom - (_playerAtkRC[i].player_AtkRC.bottom - _playerAtkRC[i].player_AtkRC.top) / 2, "X", strlen("X"));
			}
		
		}
		

		Rectangle(getMemDC(), _playerRC.left, _playerRC.top, _playerRC.right, _playerRC.bottom);
		
	}
	
	if (b_isAtkrender)
	{
		weapon_Render();
		_effect_Render();
	}
	
	if (_playerMove == Move)
	{
	
		_playerimg->aniRender(getMemDC(), _playerRC.left, _playerRC.top, _playerani);
	}
	else if (_playerMove == Idle)
	{
		
		_playerimg->aniRender(getMemDC(), _playerRC.left, _playerRC.top, _playerani);
	}
	else if (_playerMove == Jump)
	{
		_playerimg->render(getMemDC(), _playerRC.left, _playerRC.top);
	}
	else if (_playerMove == Die)
	{
		_playerimg->render(getMemDC(), _playerRC.left, _playerRC.top);
	}
}
