#include "stdafx.h"
#include "HpBar.h"


void HpBar::sync_hpFromPlayer()
{
	_playerCurrentHp = PLAYER->get_playerHP();
	if (_playerCurrentHp <= 0)
	{
		_playerCurrentHp = 0;
	}
	_PlayerHpBar_W = _imgPlayerHpBar->getWidth() * ((double)_playerCurrentHp / (double)_playerMaxHp);
	_PlayerHpBar = RectMake(_PlayerHpBar.left, _PlayerHpBar.top, (int)(_PlayerHpBar_W), _PlayerHpBar.bottom);
	// 찰랑거리는 이미지의 렉트 위치도 바뀐다.
	_hpWave_rect = RectMake(
		_PlayerHpBar.right,
		_PlayerHpBar.top,
		_img_hpWave->getFrameWidth(), _img_hpWave->getFrameHeight());
}
HpBar::HpBar()
{
}
HpBar::~HpBar()
{
}
HRESULT HpBar::init()
{
	_imgPlayerHpBar = IMAGEMANAGER->addImage("PlayerHpBar",
		"resource/image/UI/playerHp.bmp", 49 * _MULTIPLE + 2, 10 * _MULTIPLE + 2,
		true, RGB(255, 0, 255));

	_imgPlayerBackHpBar = IMAGEMANAGER->addImage("PlayerBackHpBar",
		"resource/image/UI/PlayerLifeBaseCopy.bmp",
		74 * _MULTIPLE, 16 * _MULTIPLE, true, RGB(255, 0, 255));

	_PlayerBackHpBar = RectMake(
		CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 + 6,
		CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2 + 10, _imgPlayerBackHpBar->getWidth(), _imgPlayerBackHpBar->getHeight());
	_PlayerHpBar = RectMake(
		_PlayerBackHpBar.right - _imgPlayerHpBar->getWidth() - 8,
		_PlayerBackHpBar.top + 8,
		_imgPlayerHpBar->getWidth(), _imgPlayerHpBar->getHeight());
	_PlayerHpBar_W = (double)_imgPlayerHpBar->getWidth();
	_PlayerHpBar_H = (double)_imgPlayerHpBar->getHeight();
	//============================================================
	//==				HP가 찰랑거리는 이미지						==
	//============================================================
	_img_hpWave = new image;
	_img_hpWave->init("resource/image/UI/life_wave.bmp",
		42 * _MULTIPLE,
		10 * _MULTIPLE + 2, 7, 1);
	_hpWave_rect = RectMake(
		_PlayerHpBar.right,
		_PlayerHpBar.top,
		_img_hpWave->getFrameWidth(), 
		_img_hpWave->getFrameHeight());
	_img_hpWave->set_frameSection(1, 0, 6, 5, 1);
	_img_hpWave->setFrameX(0);
	//============================================================
	//==				플레이어에게 가져오는 데이터					==
	//============================================================
	_playerMaxHp = PLAYER->get_playerMaxHP();
	_playerCurrentHp = 0;
	_playerLevel = 1;
	return S_OK;
}

void HpBar::release()
{
	_img_hpWave->release();
	_img_hpWave = nullptr;
	IMAGEMANAGER->deleteImage("PlayerHpBar");
	IMAGEMANAGER->deleteImage("PlayerBackHpBar");
	_imgPlayerBackHpBar = nullptr;
	_imgPlayerHpBar = nullptr;
}

void HpBar::update()
{
	sync_hpFromPlayer();
	_img_hpWave->frameUpdate(false);
}

void HpBar::render()
{
	// HP Bar 뒷면 그리는 부분
	_imgPlayerBackHpBar->render(CAMERAMANAGER->getCameraDC(), _PlayerBackHpBar.left, _PlayerBackHpBar.top);
	
	if (_hpWave_rect.right > _PlayerBackHpBar.right || 
		_playerCurrentHp >= _playerMaxHp || _playerCurrentHp <= 0) 
	{
		// HP Bar 앞면 그리는 부분
		_imgPlayerHpBar->render(CAMERAMANAGER->getCameraDC(), _PlayerHpBar.left, _PlayerHpBar.top, 0, 0,
			(int)(_PlayerHpBar_W), (int)(_PlayerHpBar_H));
	}//if: 플레이어 피가 꽉 차있거나, 0이면 hp wave를 렌더하지 않는다.
	else
	{
		// HP Bar 앞면 그리는 부분
		_imgPlayerHpBar->render(CAMERAMANAGER->getCameraDC(), 
			_PlayerHpBar.left, _PlayerHpBar.top, 0, 0,
			(int)(_PlayerHpBar_W - _img_hpWave->getFrameWidth() / 2), (int)(_PlayerHpBar_H));
		// 찰랑거리는 이미지 렌더하는 부분
		_img_hpWave->frameRender(CAMERAMANAGER->getCameraDC(), 
			(int)(_hpWave_rect.left - _img_hpWave->getFrameWidth() / 2), _hpWave_rect.top);
	}//else: 플레이어 피가 닳면 hp wave를 렌더한다.
	//============================================================
	//==				HP 글씨 그리는 부분						==
	//============================================================
	char str[128];
	wsprintf(str, "%d", _playerLevel);
	FontTextOut(CAMERAMANAGER->getCameraDC(),
		_PlayerHpBar.left - 38,
		_PlayerHpBar.top + 4,
		str, 25, "궁서체", RGB(254, 254, 254));

	wsprintf(str, "%d / %d", _playerMaxHp, _playerCurrentHp);
	FontTextOut(CAMERAMANAGER->getCameraDC(),
		_PlayerHpBar.left + 30,
		_PlayerHpBar.top + 4,
		str, 25, "궁서체", RGB(254, 254, 254));
	/*TextOut(CAMERAMANAGER->getCameraDC(),
		_PlayerHpBar.left + _imgPlayerHpBar->getWidth()/2 - 10,
		_PlayerHpBar.top + _imgPlayerHpBar->getHeight()/2, str, strlen(str));*/
}
