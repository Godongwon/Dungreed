#include "stdafx.h"
#include "Scene/startscene.h"

startscene::startscene()
{
}

startscene::~startscene()
{
}

HRESULT startscene::init()
{
	SOUNDMANAGER->addSound("start", "resource/sound/back/title.wav", true, true);
	SOUNDMANAGER->play("start");
	
	IMAGEMANAGER->addImage("Logo", "resource/image/start/Logo.bmp", 156*4, 75*4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("start", "resource/image/start/start.bmp", 72*3, 12*3 , 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("set", "resource/image/start/set.bmp", 42 * 3, 12 * 3, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("exit", "resource/image/start/exit.bmp", 40 * 3, 12 * 3, 2, 1, true, RGB(255, 0, 255));
	_imgfront = new image;
	_imgfront->init("resource/image/start/Cloudfront.bmp", WINSIZEX, WINSIZEY,true,RGB(255,0,255));

	_imgmiddle = new image;
	_imgmiddle->init("resource/image/start/Cloudmiddle.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_imgLogo = IMAGEMANAGER->findImage("Logo");
	_LogoRC = RectMakeCenter(WINSIZEX / 2, 200, IMAGEMANAGER->findImage("Logo")->getWidth(), IMAGEMANAGER->findImage("Logo")->getHeight());

	_imgstart = IMAGEMANAGER->findImage("start");
	startrc = RectMakeCenter(WINSIZEX / 2, WINSIZEY-200, _imgstart->getFrameWidth(), _imgstart->getFrameHeight());

	_imgset = IMAGEMANAGER->findImage("set");
	setrc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 160, _imgset->getFrameWidth(), _imgset->getFrameHeight());

	_imgexit = IMAGEMANAGER->findImage("exit");
	exitrc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 118, _imgexit->getFrameWidth(), _imgexit->getFrameHeight());

	_loopX = 0;
	_frontloopX = 0;
	return S_OK;
}

void startscene::release()
{
	
	IMAGEMANAGER->deleteImage("exit");

	IMAGEMANAGER->deleteImage("set");

	IMAGEMANAGER->deleteImage("start");

	IMAGEMANAGER->deleteImage("Logo");

	SAFE_DELETE(_imgfront);
	SAFE_DELETE(_imgmiddle);
}

void startscene::update()
{
	_loopX++;
	_frontloopX += 2;
	

	if (startrc.left<m_ptMouse.x && startrc.right>m_ptMouse.x && startrc.top<m_ptMouse.y && startrc.bottom >m_ptMouse.y)
	{
		_imgstart->setFrameX(1);
	}
	else
	{
		_imgstart->setFrameX(0);
	}
	if (setrc.left<m_ptMouse.x && setrc.right>m_ptMouse.x && setrc.top < m_ptMouse.y && setrc.bottom >m_ptMouse.y)
	{
		_imgset->setFrameX(1);
	}

	else
	{
		_imgset->setFrameX(0);
	}
	if (exitrc.left<m_ptMouse.x && exitrc.right>m_ptMouse.x && exitrc.top < m_ptMouse.y && exitrc.bottom >m_ptMouse.y)
	{
		_imgexit->setFrameX(1);
	}
	else
	{
		_imgexit->setFrameX(0);
	}
	//============================================================================
	//##							   씬 변환 조건							    ##
	//============================================================================
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
	//============================================================================
	//##							   게임시작 조건문							##
	//============================================================================
		if (PtInRect(&startrc, m_ptMouse))
		{
			SOUNDMANAGER->stop("start");
			SCENEMANAGER->changeScene("townScene");
		}
		if (PtInRect(&setrc, m_ptMouse))
		{
			SCENEMANAGER->changeScene("Maptool");
		}
		if (PtInRect(&exitrc, m_ptMouse))
		{
			PostQuitMessage(0);
		}
	}


}

void startscene::render()
{
	
	_runframe = 0;
	_startframe = 0;
	_imgmiddle->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX, 0) ;
	_imgfront->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _frontloopX, 0);
	_imgLogo->render(getMemDC(), _LogoRC.left, _LogoRC.top); 
	
	_imgset->frameRender(getMemDC(), setrc.left, setrc.top, _imgset->getFrameX(), 0);
	_imgexit->frameRender(getMemDC(), exitrc.left, exitrc.top, _imgexit->getFrameX(), 0);
	_imgstart->frameRender(getMemDC(), startrc.left, startrc.top, _imgstart->getFrameX(), 0);

	//시작화면 확인 상자
	//Rectangle(getMemDC(), setrc.left, setrc.top, setrc.right, setrc.bottom);
	//Rectangle(getMemDC(), exitrc.left, exitrc.top, exitrc.right, exitrc.bottom);
	//Rectangle(getMemDC(), startrc.left, startrc.top, startrc.right, startrc.bottom);
	
}	




 