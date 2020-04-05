#include "stdafx.h"
#include "MouseCursor.h"

void MouseCursor::set_currentDraw_rect(bool makeCenter)
{
	if (makeCenter == true)
	{
		_currentDraw_rect = RectMakeCenter(_init_pt.x + m_ptMouse.x, _init_pt.y + m_ptMouse.y,
			_cursor_img->getWidth(), _cursor_img->getHeight());
	}
	else
	{
		_currentDraw_rect = RectMake(_init_pt.x + m_ptMouse.x, _init_pt.y + m_ptMouse.y,
			_cursor_img->getWidth(), _cursor_img->getHeight());
	}
}

MouseCursor::MouseCursor()
{
}
MouseCursor::~MouseCursor()
{
}
HRESULT MouseCursor::init()
{
	_cursor_img = IMAGEMANAGER->addImage("CursorAim",
		"resource/image/UI/cursor/cursor_aim.bmp", 114 / 3, 114 / 3);
	IMAGEMANAGER->addImage("CursorArrow", "resource/image/UI/cursor/cursor_arrow.bmp", 
		(int)(9 * 2.5), (int)(11 * 2.5));
	_init_pt.x = CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2;
	_init_pt.y = CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2;
	// 마우스 커서를 지운다.
	ShowCursor(false);
	return S_OK;
}
void MouseCursor::release()
{
	ShowCursor(true);
	IMAGEMANAGER->deleteImage("CursorAim");
	IMAGEMANAGER->deleteImage("CursorArrow");
	_cursor_img = nullptr;
}
void MouseCursor::update()
{
	if (_bAim == true)
	{
		_cursor_img = IMAGEMANAGER->findImage("CursorAim");
		set_currentDraw_rect(true);
	}
	else
	{
		_cursor_img = IMAGEMANAGER->findImage("CursorArrow");
		set_currentDraw_rect(false);
	}
}
void MouseCursor::render()
{
	_cursor_img->render(CAMERAMANAGER->getCameraDC(),
		_currentDraw_rect.left, _currentDraw_rect.top);
}
