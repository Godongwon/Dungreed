#pragma once
#include "base/gameNode.h"
#include "base/singletonBase.h"
class MouseCursor: public gameNode, public singletonBase<MouseCursor>
{
private:
	image * _cursor_img;
	POINT _init_pt;
	RECT _currentDraw_rect;
	// 어느 종류의 커서를 출력할지 정한다.
	bool _bAim = true;
protected:
	void set_currentDraw_rect(bool makeCenter);
public:
	// 커서를 바꾸려면 이 함수를 콜하면 된다.
	void change_cursor() { _bAim = !_bAim; }
	void set_cursor(bool bAim) { _bAim = bAim; }
public:
	MouseCursor();
	~MouseCursor();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

#define MOUSECURSOR		MouseCursor::getSingleton()