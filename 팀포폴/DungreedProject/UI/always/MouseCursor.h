#pragma once
#include "base/gameNode.h"
#include "base/singletonBase.h"
class MouseCursor: public gameNode, public singletonBase<MouseCursor>
{
private:
	image * _cursor_img;
	POINT _init_pt;
	RECT _currentDraw_rect;
	// ��� ������ Ŀ���� ������� ���Ѵ�.
	bool _bAim = true;
protected:
	void set_currentDraw_rect(bool makeCenter);
public:
	// Ŀ���� �ٲٷ��� �� �Լ��� ���ϸ� �ȴ�.
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