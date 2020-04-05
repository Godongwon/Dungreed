#include "stdafx.h"
#include "Maptool.h"
#include "UI/always/MouseCursor.h"
void Maptool::save_map()
{
	HANDLE mapfile = CreateFile("save/map1.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD writeTemp;
	WriteFile(mapfile, _boardCells, sizeof(_boardCells),
		&writeTemp, NULL);
	CloseHandle(mapfile);
}
void Maptool::load_map()
{
	HANDLE mapfile = CreateFile("save/map1.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
	DWORD readTemp;
	ReadFile(mapfile, _boardCells, sizeof(_boardCells),
		&readTemp, NULL);
	CloseHandle(mapfile);
}
//============================================================
//==				Ŭ���� ���� Ÿ���� ����						==
//============================================================
void Maptool::set_sampleTile()
{
	for (int y = 0; y < _MAX_SAMPLE_H; y++)
	{
		for (int x = 0; x < _MAX_SAMPLE_W; x++)
		{
			if (PtInRect(&_sampleCells[y][x].rc, m_ptMouse))
			{
				_extractionTile.img_rc.left =
					_sampleCells[y][x].pt.x * TILE_WIDTH;
				_extractionTile.img_rc.top =
					_sampleCells[y][x].pt.y * TILE_HEIGHT;
				_extractionTile.tileIdx = _sampleIdx;
				_extractionTile.bTile = true;
				// ���⼭ ������ Ż���Ѵ�.
				y = _MAX_SAMPLE_H;
				break;
			}//if: Ŭ���� ���� Ÿ�� ����
		}
	}
}
void Maptool::draw_sampleImg()
{
	// ������ Ÿ�� �̹����� ������.
	int countX, countY;
	countX = (int)(_sampleImg->getWidth() / TILE_WIDTH);
	countY = (int)(_sampleImg->getHeight() / TILE_HEIGHT);
	// Ÿ���� ����Ѵ�.
	for (int y = 0; y < _CELL_H; y++)
	{
		for (int x = 0; x < _CELL_W; x++)
		{
			RECT cellRc = _sampleCells[y][x].rc;
			POINT cellPt = _sampleCells[y][x].pt;
			_sampleImg->render(getMemDC(), cellRc.left, cellRc.top,
				cellPt.x * TILE_WIDTH, cellPt.y * TILE_HEIGHT,
				TILE_WIDTH, TILE_HEIGHT);
		}
	}
}
void Maptool::init_extractionTile()
{
	_extractionTile.rc = { 0, };
	_extractionTile.pt = { 0, };
	_extractionTile.bTile = false;
	_extractionTile.tileIdx = 0;
	_extractionTile.img_rc = { 0, };
}
//============================================================
//==			���� Ÿ���� �׸� Cell �ʱ�ȭ					==
//============================================================
void Maptool::init_sampleCells()
{
	int currentX = _sampleBoard.left;
	int currentY = _sampleBoard.top;
	for (int y = 0; y < _CELL_H; y++)
	{
		currentY += _CELL_BLANK_H;
		for (int x = 0; x < _CELL_W; x++)
		{
			currentX += _CELL_BLANK_W;
			_sampleCells[y][x].rc = RectMake(currentX, currentY,
				TILE_WIDTH, TILE_HEIGHT);
			_sampleCells[y][x].pt.x = x;
			_sampleCells[y][x].pt.y = y;
			currentX += TILE_WIDTH;
		}
		currentY += TILE_WIDTH;
		currentX = _sampleBoard.left;
	}
}
void Maptool::draw_sampleCells()
{
	char str[128];
	for (int y = 0; y < _CELL_H; y++)
	{
		for (int x = 0; x < _CELL_W; x++)
		{
			// �� �������� ���̴� �κ�
			RECT rc = _sampleCells[y][x].rc;
			POINT pt = _sampleCells[y][x].pt;
			// �� ��Ʈ ���� �κ�
			Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
			// ��ǥ ���� �κ�
			wsprintf(str, "(%d, %d)", pt.y, pt.x);
			TextOut(getMemDC(), rc.left, rc.top + 2, str, strlen(str));
		}
	}
}
//============================================================
//==				���� ������ ��ư �ʱ�ȭ	 ->					==
//============================================================
void Maptool::init_sampleButtonRect()
{
	// ���� ���尡 ������ ������ ��ġ�� �����´�.
	int x = _sampleBoard.left;
	int y = _sampleBoard.bottom;
	y += (int)(_CELL_BLANK_H * 2);
	// ��ư ���带 �ʱ�ȭ�Ѵ�.
	int width = (int)(_CELL_W * TILE_WIDTH + _CELL_BLANK_W * (_CELL_W - 1));
	int height = TILE_HEIGHT;
	_buttonBoard = RectMake(x, y, width, height);
	// �� ��ư �� ��Ʈ�� �ʱ�ȭ�Ѵ�.
	// ��� ���� ������ Ÿ���� �����ִ� �κ�
	x = _buttonBoard.left;
	y = _buttonBoard.top;
	width = _buttonBoard.right - _buttonBoard.left;
	height = _buttonBoard.bottom - _buttonBoard.top;
	_settingTileRect = RectMakeCenter(
		(int)(x + width * 0.5), (int)(y + height * 0.5),
		TILE_WIDTH, TILE_HEIGHT);
	// ���� Ÿ��
	x = (int)(_settingTileRect.right + _CELL_BLANK_W * 0.5);
	y = _settingTileRect.top;
	width = (int)((_buttonBoard.right - x) / 3 + _CELL_BLANK_W);
	_prevRect = RectMake(x, y, width + 1, height);
	// ���� �����ִ� ��
	x = (int)(x + width + _CELL_BLANK_W * 0.5);
	_numRect = RectMake(x, y, width, height);
	// ���� Ÿ��
	x = (int)(x + width + _CELL_BLANK_W * 0.5);
	_nextRect = RectMake(x, y, width + 1, height);
	// Set
	x = _buttonBoard.left;
	width = (int)((_settingTileRect.left - x) * 0.5);
	_setRect = RectMake(x, y, width, height);
	// del
	x += width;
	_delRect = RectMake(x, y, width, height);
}
void Maptool::draw_sampleButtonRect()
{
	// ����׿� ��Ʈ ����
	// ��� Ÿ���� �����ߴ���
	Rectangle(getMemDC(), _settingTileRect.left, _settingTileRect.top,
		_settingTileRect.right, _settingTileRect.bottom);
	// ���� ���� �ִ� �̹��� �ε���
	Rectangle(getMemDC(), _numRect.left, _numRect.top,
		_numRect.right, _numRect.bottom);
	// ����, ���� ��ư
	Rectangle(getMemDC(), _prevRect.left, _prevRect.top,
		_prevRect.right, _prevRect.bottom);
	Rectangle(getMemDC(), _nextRect.left, _nextRect.top,
		_nextRect.right, _nextRect.bottom);
	// Set, Del ��ư
	Rectangle(getMemDC(), _setRect.left, _setRect.top,
		_setRect.right, _setRect.bottom);
	Rectangle(getMemDC(), _delRect.left, _delRect.top,
		_delRect.right, _delRect.bottom);
}
void Maptool::init_sampleButtonImg()
{
	int width, height;
	// Set
	width = (int)(_setRect.right - _setRect.left - (_CELL_BLANK_W * 0.5));
	height = (int)(_setRect.bottom - _setRect.top - (_CELL_BLANK_H * 0.5));
	IMAGEMANAGER->addImage("Button_Set",
		"resource/image/map/button/Button_Set.bmp", width, height);
	// Del
	width = (int)(_delRect.right - _delRect.left - (_CELL_BLANK_W * 0.5));
	height = (int)(_delRect.bottom - _delRect.top - (_CELL_BLANK_H * 0.5));
	IMAGEMANAGER->addImage("Button_Del",
		"resource/image/map/button/Button_Del.bmp", width, height);
	// X
	width = (int)(_settingTileRect.right - _settingTileRect.left - (_CELL_BLANK_W * 0.5));;
	height = (int)(_settingTileRect.bottom - _settingTileRect.top - (_CELL_BLANK_H * 0.5));
	IMAGEMANAGER->addImage("Button_X",
		"resource/image/map/button/Button_X.bmp", width, height);
	// <-
	width = (int)(_prevRect.right - _prevRect.left - (_CELL_BLANK_W * 0.5));
	height = (int)(_prevRect.bottom - _prevRect.top - (_CELL_BLANK_H * 0.5));
	IMAGEMANAGER->addImage("Button_Prev",
		"resource/image/map/button/Button_LeftArrow.bmp", width, height);
	//->
	width = (int)(_nextRect.right - _nextRect.left - (_CELL_BLANK_W * 0.5));
	height = (int)(_nextRect.bottom - _nextRect.top - (_CELL_BLANK_H * 0.5));
	IMAGEMANAGER->addImage("Button_Next",
		"resource/image/map/button/Button_RightArrow.bmp", width, height);
}
void Maptool::init_sampleButton()
{
	init_sampleButtonRect();
}
void Maptool::draw_sampleButton()
{
	if (_bDebug == true) { draw_sampleButtonRect(); }
	// �̹��� ��� �ϴ� �۾��� �����ش�.
	char str[128];
	wsprintf(str, "%d", _sampleIdx);
	// �̹����� �ִ� �� �̹����� ��ü�Ѵ�.
	image * button;
	button = IMAGEMANAGER->findImage("Button_Set");
	button->render(getMemDC(), _setRect.left, _setRect.top);
	button = IMAGEMANAGER->findImage("Button_Del");
	button->render(getMemDC(), _delRect.left, _delRect.top);

	// ���� Ÿ��
	if (_extractionTile.bTile == true)
	{
		if (_extractionTile.img_rc.left == -1 &&
			_extractionTile.img_rc.top == -1)
		{
			button = IMAGEMANAGER->findImage("Button_X");
			button->render(getMemDC(),
				_settingTileRect.left, _settingTileRect.top);
		}//if: Delete ����� ���õǾ� �ִٸ�
		else
		{
			_sampleImg->render(getMemDC(),
				_settingTileRect.left, _settingTileRect.top,
				(int)(_extractionTile.img_rc.left),
				(int)(_extractionTile.img_rc.top),
				TILE_WIDTH, TILE_HEIGHT);
		}
	}//if: Ÿ���� ���õǾ� �ִٸ�

	// ȭ��ǥ
	if (_sampleIdx <= 1) { _bPrev = false; }
	else
	{
		_bPrev = true;
		button = IMAGEMANAGER->findImage("Button_Prev");
		button->render(getMemDC(), _prevRect.left, _prevRect.top);
	}
	// _sampleIdx ����
	TextOut(getMemDC(), _numRect.left, _numRect.top,
		str, strlen(str));
	button = IMAGEMANAGER->findImage("Button_Next");
	button->render(getMemDC(), _nextRect.left, _nextRect.top);
}
//============================================================
//==				Ÿ���� ���忡 ����							==
//============================================================
void Maptool::set_tileToBoard(bool bSetButton)
{
	for (int y = 0; y < _MAX_TILE_H; y++)
	{
		for (int x = 0; x < _MAX_TILE_W; x++)
		{
			if (bSetButton == true)
			{
				if (_boardCells[y][x].bSelected == true)
				{
					_boardCells[y][x].img_rc = _extractionTile.img_rc;
					_boardCells[y][x].tileIdx = _sampleIdx;
					_boardCells[y][x].bTile = true;
					_boardCells[y][x].bSelected = false;
				}//if: ���� ������ ���� �����Ѵٸ� Ÿ���� �����Ѵ�.
			}//if: �� ��ư�� �����ٸ�
			else
			{
				if (PtInRect(&_boardCells[y][x].rc, _inBoard_mouse_pt))
				{
					_boardCells[y][x].img_rc = _extractionTile.img_rc;
					_boardCells[y][x].tileIdx = _sampleIdx;
					_boardCells[y][x].bTile = true;
				}//if: �� �κ��� ���콺�� ��ġ�� ����
			}//if: �� ��ư�� �ȴ����ٸ�
		}
	}
}
void Maptool::delete_tileSelect()
{
	// ���� Ÿ�� �׸��� x�� �ٲ۴�.
	_extractionTile.img_rc.left = -1;
	_extractionTile.img_rc.top = -1;
	_extractionTile.bTile = true;
	// ���õ� Ÿ���� �ִٸ� Ÿ���� �����.
	for (int y = 0; y < _MAX_TILE_H; y++)
	{
		for (int x = 0; x < _MAX_TILE_W; x++)
		{
			// ��� ���� ������ �����Ѵ�.
			_boardCells[y][x].bSelected = false;
		}
	}
}
void Maptool::delete_tileToBoard()
{
	// ���� Ÿ�� �׸��� x�� �ٲ۴�.
	_extractionTile.img_rc.left = -1;
	_extractionTile.img_rc.top = -1;
	_extractionTile.bTile = true;
	for (int y = 0; y < _MAX_TILE_H; y++)
	{
		for (int x = 0; x < _MAX_TILE_W; x++)
		{
			// ������ ��� ���� ���忡�� �����.
			if (_boardCells[y][x].bSelected == true)
			{
				_boardCells[y][x].img_rc = { -1, -1, 0, 0 };
				_boardCells[y][x].bTile = false;
				_boardCells[y][x].bSelected = false;
			}
		}
	}
}
void Maptool::draw_tileToBoard()
{
	int drawX, drawY;
	POINT draw_pt;
	for (int y = 0; y < _MAX_BOARD_H; y++)
	{
		for (int x = 0; x < _MAX_BOARD_W; x++)
		{
			draw_pt = limit_currentBoard_pt(_currentBoard_pt);
			drawX = x + draw_pt.x;
			drawY = y + draw_pt.y;
			if (_boardCells[drawY][drawX].bTile == true)
			{
				if (_boardCells[drawY][drawX].bSelected == true)
				{
					ColorRect(_boardBuffer->getMemDC(),
						_boardCells[drawY][drawX].rc, RGB(0, 128, 128));
				}//if: Ÿ���� �������� ��
				else
				{
					_sampleImg->render(_boardBuffer->getMemDC(),
						_boardCells[drawY][drawX].rc.left,
						_boardCells[drawY][drawX].rc.top,
						_boardCells[drawY][drawX].img_rc.left,
						_boardCells[drawY][drawX].img_rc.top,
						TILE_WIDTH, TILE_HEIGHT);
				}//else: Ÿ���� �������� �ʾ��� ��
			}//if: ���忡 Ÿ���� �����Ѵٸ�
		}
	}
}
void Maptool::draw_selectRect()
{
	DrawFocusRect(_boardBuffer->getMemDC(), &_selectRect);
}
//============================================================
//==			�巡�� �� �� �׸��� RECT ����					==
//============================================================
void Maptool::set_selectStart(POINT pt)
{
	_selectRect.left = pt.x;
	_selectRect.top = pt.y;

}
void Maptool::set_selectEnd(POINT pt)
{
	// ���� right, bottom�� ���������� ���ʿ� �ִٸ� (������, ����)�� swap �Ѵ�.
	// RECT �� right ����
	_selectRect.right = pt.x;
	_selectRect.bottom = pt.y;
}
void Maptool::set_inBoard_mouse_pt()
{
	_inBoard_mouse_pt.x = m_ptMouse.x + _currentBoard_pt.x * TILE_WIDTH;
	_inBoard_mouse_pt.y = m_ptMouse.y + _currentBoard_pt.y * TILE_HEIGHT;
}
POINT Maptool::limit_currentBoard_pt(POINT pt)
{
	int limitX = _MAX_TILE_W - _MAX_BOARD_W;
	int limitY = _MAX_TILE_H - _MAX_BOARD_H;
	// ���� ��ǥ�� ��� ������ �Ѿ�� ���ϵ��� ���´�.
	POINT draw_pt = { 0, };
	if (pt.x < 0) { draw_pt.x = 0; }
	else if (pt.x > limitX)
	{
		draw_pt.x = (LONG)(_MAX_TILE_W - _MAX_BOARD_W);
	}
	else
	{
		draw_pt.x = pt.x;
	}
	if (pt.y < 0) { draw_pt.y = 0; }
	else if (pt.y > limitY)
	{
		draw_pt.y = (LONG)(_MAX_TILE_H - _MAX_BOARD_H);
	}
	else
	{
		draw_pt.y = pt.y;
	}
	return draw_pt;
}
//============================================================
//==			Ÿ���� �׸� ���� Cell ����						==
//============================================================
void Maptool::select_boardCells()
{
	for (int y = 0; y < _MAX_TILE_H; y++)
	{
		for (int x = 0; x < _MAX_TILE_W; x++)
		{
			if (PtInRect(&_boardCells[y][x].rc, _inBoard_mouse_pt))
			{
				_boardCells[y][x].bSelected = true;
			}
		}
	}
}
void Maptool::select_boardCells(RECT selected_rc)
{
	for (int y = 0; y < _MAX_TILE_H; y++)
	{
		for (int x = 0; x < _MAX_TILE_W; x++)
		{
			if (IntersectRect(&RECT(), &_boardCells[y][x].rc, &_selectRect))
			{
				_boardCells[y][x].bSelected = true;
			}
		}
	}
}
//============================================================
//==					���� Cell �ʱ�ȭ						==
//============================================================
void Maptool::init_boardCells()
{
	int currentX = 0;
	int currentY = 0;
	for (int y = 0; y < _MAX_TILE_H; y++)
	{
		for (int x = 0; x < _MAX_TILE_W; x++)
		{
			_boardCells[y][x].rc = RectMake(currentX, currentY,
				TILE_WIDTH, TILE_HEIGHT);
			_boardCells[y][x].pt.x = x;
			_boardCells[y][x].pt.y = y;
			currentX += TILE_WIDTH;
		}
		currentY += TILE_WIDTH;
		currentX = 0;
	}
}
void Maptool::draw_boardCells()
{
	char str[128];	// ��Ʈ�� ���ڸ� ����� ����
	int counter = 0;	// ��Ʈ ���ڸ� ���� ����
	// ���� ���� ȭ���� ���� �ٸ� ���� ����ϱ� ���� ����
	int drawX, drawY;
	POINT drawBoard_pt;
	// �Լ� ������ �� �ӽú���, �������� ª�� �����.
	RECT rc;
	POINT pt;
	bool bSelected;
	bool bTile;
	for (int y = 0; y < _MAX_BOARD_H; y++)
	{
		for (int x = 0; x < _MAX_BOARD_W; x++)
		{
			drawBoard_pt = limit_currentBoard_pt(_currentBoard_pt);
			drawX = x + drawBoard_pt.x;
			drawY = y + drawBoard_pt.y;
			// ����� ���� ��ũ�� �����.
			rc = _boardCells[drawY][drawX].rc;
			pt = _boardCells[drawY][drawX].pt;
			bSelected = _boardCells[drawY][drawX].bSelected;
			bTile = _boardCells[drawY][drawX].bTile;

			counter = drawY + drawX;	// ����� ���� ī��Ʈ
			// �� ��Ʈ ���� �κ�
			if (bSelected == true)
			{
				ColorRect(_boardBuffer->getMemDC(), rc, RGB(0, 255, 64));
			}//if: ������ Ÿ��
			else
			{
				ColorRect(_boardBuffer->getMemDC(), rc, RGB(255, 255, 255));
				// ���� ���� �κ�
				draw_boardCell_number(rc.left, rc.top, str, pt, counter);
			}//else: �������� ���� Ÿ��
		}
	}
}
void Maptool::draw_boardCell_number(int x, int y,
	char * str, POINT pt, int count)
{
	if (_bDebug == true)
	{
		wsprintf(str, "(%d, %d)", pt.y, pt.x);
		TextOut(_boardBuffer->getMemDC(), x, y + 2, str, strlen(str));
	}//if: ����׸� ��ǥ ����.
	else
	{
		wsprintf(str, "%d", count);
		TextOut(_boardBuffer->getMemDC(), x + 1, y + 3, str, strlen(str));
	}//else: �ƴϸ� ���� ����.
}
//============================================================
//==					���� �ʱ�ȭ							==
//============================================================
void Maptool::init_defaultBoard()
{
	_board = RectMake(10, 10,
		TILE_WIDTH * _MAX_BOARD_W, TILE_WIDTH * _MAX_BOARD_H);
	// ������ �ʱ�ȭ�Ѵ�.
	_sampleBoard = RectMake(_board.right + 10, _board.top + TILE_HEIGHT * 2,
		TILE_WIDTH * _MAX_SAMPLE_W, TILE_WIDTH * (_MAX_SAMPLE_H - 1));
	// ���带 �׸� ������ ũ�⸦ ����ش�.
	// ũ��� ������ ���� �ִ� Ÿ�� ���� * Ÿ�� �ȼ� ũ��
	_boardBuffer = new image;
	_boardBuffer->init((int)(_BOARD_BUFFER_W), (int)(_BOARD_BUFFER_H));
	// ������ ���� ���� ���� �ʱ���ġ�� �����ش�.
	_currentBoard_pt.x = 0;
	_currentBoard_pt.y = _MAX_TILE_H - _MAX_BOARD_H;
}
void Maptool::draw_board()
{
	Rectangle(getMemDC(), _board.left, _board.top,
		_board.right, _board.bottom);
	if (_bDebug == true)
	{
		Rectangle(getMemDC(), _sampleBoard.left, _sampleBoard.top,
			_sampleBoard.right, _sampleBoard.bottom);
	}
}
Maptool::Maptool()
{
}
Maptool::~Maptool()
{
}
//============================================================
//==				#init �ʱ�ȭ								==
//============================================================
HRESULT Maptool::init()
{
	init_defaultBoard();
	init_boardCells();
	init_sampleCells();
	// ���⼭ ���� �̹����� �ҷ��´�.
	_sampleImg = IMAGEMANAGER->addImage("SampleTile",
		"resource/image/map/MapTile1.bmp",
		(int)(512 * MULTIPLE_TILE), (int)(320 * MULTIPLE_TILE));
	// ���⼭ ���� ��ư�� �ʱ�ȭ�Ѵ�.
	init_sampleButton();
	init_sampleButtonImg();
	// ���⼭ ������ Ÿ���� �ʱ�ȭ�Ѵ�.
	init_extractionTile();
	_bDebug = false;
	// ���콺 Ŀ���� �ʱ�ȭ�Ѵ�.
	MOUSECURSOR->init();
	MOUSECURSOR->set_cursor(false);
	return S_OK;
}
void Maptool::release()
{
}
//============================================================
//==				#update	������Ʈ							==
//============================================================
void Maptool::update()
{
	// ���忡�� �� ���� ���콺 ��ǥ�� �����Ѵ�.
	set_inBoard_mouse_pt();
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//============================================================
		//==			���⼭ Ÿ���� �׸� ���� �� ����					==
		//============================================================
		if (PtInRect(&_board, _inBoard_mouse_pt))
		{
			select_boardCells();
		}//if: ���带 Ŭ���ߴٸ�
		//============================================================
		//==				���⼭ ��Ÿ�� ����							==
		//============================================================
		if ((bool)(PtInRect(&_sampleBoard, m_ptMouse)) == true
			&& (bool)(PtInRect(&_setRect, m_ptMouse)) == false)
		{
			set_sampleTile();
		}//if: �� ��ư�� ������ �ʰ�, ���� ���带 Ŭ���ߴٸ�
	//============================================================
	//==				���⼭ ��ư ó��							==
	//============================================================
		if (PtInRect(&_setRect, m_ptMouse))
		{
			set_tileToBoard(true);
		}//if: Set ��ư�� Ŭ���ߴٸ�
		if (PtInRect(&_delRect, m_ptMouse))
		{
			delete_tileToBoard();
		}//if: Del ��ư�� Ŭ���ߴٸ�
		if (PtInRect(&_prevRect, m_ptMouse) && _bPrev == true)
		{
			_sampleIdx--;
		}//if: prev ��ư�� Ŭ���ߴٸ�
		if (PtInRect(&_nextRect, m_ptMouse) && _bNext == true)
		{
			_sampleIdx++;
		}//if: prev ��ư�� Ŭ���ߴٸ�

	}//if: ���콺 ��Ŭ��
	else if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		//============================================================
		//==			���⼭ �巡�� ��Ʈ ����							==
		//============================================================
		if (PtInRect(&_board, m_ptMouse))
		{
			if (_bSelectStart == true)
			{
				set_selectStart(_inBoard_mouse_pt);
				_bSelectStart = false;
			}
			else
			{
				set_selectEnd(_inBoard_mouse_pt);
			}
		}//if: ������ ���� �巡�� ���̶��
	}//if: ���콺 ���� �巡��
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (PtInRect(&_board, m_ptMouse))
		{
			set_selectEnd(_inBoard_mouse_pt);
			select_boardCells(_selectRect);
			set_selectStart({ 0, 0 });
			set_selectEnd({ 0, 0 });
			_bSelectStart = true;
		}//if: ������ �ȿ��� �巡�� �����ٸ� ���弿�� �����Ѵ�.
		else
		{
			set_selectStart({ 0, 0 });
			set_selectEnd({ 0, 0 });
			_bSelectStart = true;
		}//else: �巡�׸� �̻��ϰ� �ߴٸ� ���� 0���� �о������.
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//============================================================
		//==				���⼭ ���忡 Ÿ�� ó��						==
		//============================================================
		if (PtInRect(&_board, m_ptMouse) && _extractionTile.bTile == true)
		{
			set_tileToBoard(false);
		}//if: Ÿ���� �����Ѵٸ� ���忡 ��
		//============================================================
		//==				���⼭ ��ư ó��							==
		//============================================================
		if (PtInRect(&_delRect, m_ptMouse))
		{
			delete_tileSelect();
		}//if: Del ��ư�� Ŭ���ߴٸ�
	}//if: ���콺 ����Ŭ��
	else if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		//============================================================
		//==				���⼭ ���忡 Ÿ�� ó��						==
		//============================================================
		if (PtInRect(&_board, m_ptMouse) && _extractionTile.bTile == true)
		{
			set_tileToBoard(false);
		}
	}//if: ���콺 ������ �巡��
	//============================================================
	//==					Save & Load							==
	//============================================================
	if (KEYMANAGER->isOnceKeyDown('2')) { save_map(); }
	else if (KEYMANAGER->isOnceKeyDown('3')) { load_map(); }
	//============================================================
	//==				���⼭ ����Ű ó��							==
	//============================================================
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_currentBoard_pt.x--;
	}
	else if (KEYMANAGER->isStayKeyDown('D'))
	{
		_currentBoard_pt.x++;
	}
	else if (KEYMANAGER->isStayKeyDown('W'))
	{
		_currentBoard_pt.y--;
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		_currentBoard_pt.y++;
	}
	// ���콺 Ŀ�� ������Ʈ
	MOUSECURSOR->update();
	//============================================================
	//==			����׸�带 ���ٰ� Ű�� �κ�					==
	//============================================================
	if (KEYMANAGER->isToggleKey('1') == true && _bDebug == false)
	{
		_bDebug = true;
	}
	else if (KEYMANAGER->isToggleKey('1') == false)
	{
		_bDebug = false;
	}
}

void Maptool::render()
{
	// ����� ��ī�İ� ����
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	// ���� ���۸� ���Ͼ�� ����
	PatBlt(_boardBuffer->getMemDC(), 0, 0,
		_BOARD_BUFFER_W, _BOARD_BUFFER_H, WHITENESS);
	// ī�޶� ���� ����
	draw_board();
	draw_boardCells();
	draw_sampleImg();
	draw_sampleButton();
	draw_tileToBoard();
	// ���⼭ �巡�� �� �� ���̴� RECT ����
	draw_selectRect();
	// ���⼭ ���� ���۸� ����
	_boardBuffer->render(getMemDC(), _board.left, _board.top,
		(int)(_currentBoard_pt.x * TILE_WIDTH),
		(int)(_currentBoard_pt.y * TILE_HEIGHT),
		(int)(_MAX_BOARD_W * TILE_WIDTH),
		(int)(_MAX_BOARD_H * TILE_HEIGHT));
	if (_bDebug == true) { draw_sampleCells(); }
	// ���콺 Ŀ�� ����
	MOUSECURSOR->render();
}
