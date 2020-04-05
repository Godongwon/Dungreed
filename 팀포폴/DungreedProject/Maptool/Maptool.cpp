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
//==				클릭한 샘플 타일을 추출						==
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
				// 여기서 루프를 탈출한다.
				y = _MAX_SAMPLE_H;
				break;
			}//if: 클릭한 샘플 타일 추출
		}
	}
}
void Maptool::draw_sampleImg()
{
	// 가져온 타일 이미지의 갯수다.
	int countX, countY;
	countX = (int)(_sampleImg->getWidth() / TILE_WIDTH);
	countY = (int)(_sampleImg->getHeight() / TILE_HEIGHT);
	// 타일을 출력한다.
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
//==			샘플 타일을 그릴 Cell 초기화					==
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
			// 긴 변수명을 줄이는 부분
			RECT rc = _sampleCells[y][x].rc;
			POINT pt = _sampleCells[y][x].pt;
			// 셀 렉트 띄우는 부분
			Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
			// 좌표 띄우는 부분
			wsprintf(str, "(%d, %d)", pt.y, pt.x);
			TextOut(getMemDC(), rc.left, rc.top + 2, str, strlen(str));
		}
	}
}
//============================================================
//==				샘플 보드의 버튼 초기화	 ->					==
//============================================================
void Maptool::init_sampleButtonRect()
{
	// 샘플 보드가 끝나는 지점의 위치를 가져온다.
	int x = _sampleBoard.left;
	int y = _sampleBoard.bottom;
	y += (int)(_CELL_BLANK_H * 2);
	// 버튼 보드를 초기화한다.
	int width = (int)(_CELL_W * TILE_WIDTH + _CELL_BLANK_W * (_CELL_W - 1));
	int height = TILE_HEIGHT;
	_buttonBoard = RectMake(x, y, width, height);
	// 각 버튼 별 렉트를 초기화한다.
	// 가운데 내가 선택한 타일을 보여주는 부분
	x = _buttonBoard.left;
	y = _buttonBoard.top;
	width = _buttonBoard.right - _buttonBoard.left;
	height = _buttonBoard.bottom - _buttonBoard.top;
	_settingTileRect = RectMakeCenter(
		(int)(x + width * 0.5), (int)(y + height * 0.5),
		TILE_WIDTH, TILE_HEIGHT);
	// 이전 타일
	x = (int)(_settingTileRect.right + _CELL_BLANK_W * 0.5);
	y = _settingTileRect.top;
	width = (int)((_buttonBoard.right - x) / 3 + _CELL_BLANK_W);
	_prevRect = RectMake(x, y, width + 1, height);
	// 숫자 보여주는 곳
	x = (int)(x + width + _CELL_BLANK_W * 0.5);
	_numRect = RectMake(x, y, width, height);
	// 다음 타일
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
	// 디버그용 렉트 렌더
	// 어느 타일을 선택했는지
	Rectangle(getMemDC(), _settingTileRect.left, _settingTileRect.top,
		_settingTileRect.right, _settingTileRect.bottom);
	// 현재 보고 있는 이미지 인덱스
	Rectangle(getMemDC(), _numRect.left, _numRect.top,
		_numRect.right, _numRect.bottom);
	// 이전, 다음 버튼
	Rectangle(getMemDC(), _prevRect.left, _prevRect.top,
		_prevRect.right, _prevRect.bottom);
	Rectangle(getMemDC(), _nextRect.left, _nextRect.top,
		_nextRect.right, _nextRect.bottom);
	// Set, Del 버튼
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
	// 이미지 대신 일단 글씨로 보여준다.
	char str[128];
	wsprintf(str, "%d", _sampleIdx);
	// 이미지가 있는 건 이미지로 대체한다.
	image * button;
	button = IMAGEMANAGER->findImage("Button_Set");
	button->render(getMemDC(), _setRect.left, _setRect.top);
	button = IMAGEMANAGER->findImage("Button_Del");
	button->render(getMemDC(), _delRect.left, _delRect.top);

	// 샘플 타일
	if (_extractionTile.bTile == true)
	{
		if (_extractionTile.img_rc.left == -1 &&
			_extractionTile.img_rc.top == -1)
		{
			button = IMAGEMANAGER->findImage("Button_X");
			button->render(getMemDC(),
				_settingTileRect.left, _settingTileRect.top);
		}//if: Delete 명령이 셋팅되어 있다면
		else
		{
			_sampleImg->render(getMemDC(),
				_settingTileRect.left, _settingTileRect.top,
				(int)(_extractionTile.img_rc.left),
				(int)(_extractionTile.img_rc.top),
				TILE_WIDTH, TILE_HEIGHT);
		}
	}//if: 타일이 셋팅되어 있다면

	// 화살표
	if (_sampleIdx <= 1) { _bPrev = false; }
	else
	{
		_bPrev = true;
		button = IMAGEMANAGER->findImage("Button_Prev");
		button->render(getMemDC(), _prevRect.left, _prevRect.top);
	}
	// _sampleIdx 숫자
	TextOut(getMemDC(), _numRect.left, _numRect.top,
		str, strlen(str));
	button = IMAGEMANAGER->findImage("Button_Next");
	button->render(getMemDC(), _nextRect.left, _nextRect.top);
}
//============================================================
//==				타일을 보드에 매핑							==
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
				}//if: 내가 선택한 셀이 존재한다면 타일을 셋팅한다.
			}//if: 셋 버튼을 눌렀다면
			else
			{
				if (PtInRect(&_boardCells[y][x].rc, _inBoard_mouse_pt))
				{
					_boardCells[y][x].img_rc = _extractionTile.img_rc;
					_boardCells[y][x].tileIdx = _sampleIdx;
					_boardCells[y][x].bTile = true;
				}//if: 내 인보드 마우스에 위치한 셀을
			}//if: 셋 버튼을 안눌렀다면
		}
	}
}
void Maptool::delete_tileSelect()
{
	// 선택 타일 그림을 x로 바꾼다.
	_extractionTile.img_rc.left = -1;
	_extractionTile.img_rc.top = -1;
	_extractionTile.bTile = true;
	// 선택된 타일이 있다면 타일을 지운다.
	for (int y = 0; y < _MAX_TILE_H; y++)
	{
		for (int x = 0; x < _MAX_TILE_W; x++)
		{
			// 모든 셀의 선택을 해제한다.
			_boardCells[y][x].bSelected = false;
		}
	}
}
void Maptool::delete_tileToBoard()
{
	// 선택 타일 그림을 x로 바꾼다.
	_extractionTile.img_rc.left = -1;
	_extractionTile.img_rc.top = -1;
	_extractionTile.bTile = true;
	for (int y = 0; y < _MAX_TILE_H; y++)
	{
		for (int x = 0; x < _MAX_TILE_W; x++)
		{
			// 선택한 모든 셀을 보드에서 지운다.
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
				}//if: 타일을 선택했을 때
				else
				{
					_sampleImg->render(_boardBuffer->getMemDC(),
						_boardCells[drawY][drawX].rc.left,
						_boardCells[drawY][drawX].rc.top,
						_boardCells[drawY][drawX].img_rc.left,
						_boardCells[drawY][drawX].img_rc.top,
						TILE_WIDTH, TILE_HEIGHT);
				}//else: 타일을 선택하지 않았을 때
			}//if: 보드에 타일이 존재한다면
		}
	}
}
void Maptool::draw_selectRect()
{
	DrawFocusRect(_boardBuffer->getMemDC(), &_selectRect);
}
//============================================================
//==			드래그 할 때 그리는 RECT 셋팅					==
//============================================================
void Maptool::set_selectStart(POINT pt)
{
	_selectRect.left = pt.x;
	_selectRect.top = pt.y;

}
void Maptool::set_selectEnd(POINT pt)
{
	// 만약 right, bottom이 시작점보다 왼쪽에 있다면 (시작점, 끝점)을 swap 한다.
	// RECT 의 right 셋팅
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
	// 가상 좌표가 출력 범위를 넘어가지 못하도록 막는다.
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
//==			타일을 그릴 보드 Cell 선택						==
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
//==					보드 Cell 초기화						==
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
	char str[128];	// 렉트에 숫자를 출력할 변수
	int counter = 0;	// 렉트 숫자를 세는 변수
	// 보드 버퍼 화면을 따라서 다른 셀을 출력하기 위한 변수
	int drawX, drawY;
	POINT drawBoard_pt;
	// 함수 내에서 쓸 임시변수, 변수명을 짧게 만든다.
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
			// 보드와 셀의 싱크를 맞춘다.
			rc = _boardCells[drawY][drawX].rc;
			pt = _boardCells[drawY][drawX].pt;
			bSelected = _boardCells[drawY][drawX].bSelected;
			bTile = _boardCells[drawY][drawX].bTile;

			counter = drawY + drawX;	// 출력할 숫자 카운트
			// 셀 렉트 띄우는 부분
			if (bSelected == true)
			{
				ColorRect(_boardBuffer->getMemDC(), rc, RGB(0, 255, 64));
			}//if: 선택한 타일
			else
			{
				ColorRect(_boardBuffer->getMemDC(), rc, RGB(255, 255, 255));
				// 숫자 띄우는 부분
				draw_boardCell_number(rc.left, rc.top, str, pt, counter);
			}//else: 선택하지 않은 타일
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
	}//if: 디버그면 좌표 띄운다.
	else
	{
		wsprintf(str, "%d", count);
		TextOut(_boardBuffer->getMemDC(), x + 1, y + 3, str, strlen(str));
	}//else: 아니면 숫자 띄운다.
}
//============================================================
//==					보드 초기화							==
//============================================================
void Maptool::init_defaultBoard()
{
	_board = RectMake(10, 10,
		TILE_WIDTH * _MAX_BOARD_W, TILE_WIDTH * _MAX_BOARD_H);
	// 샘플을 초기화한다.
	_sampleBoard = RectMake(_board.right + 10, _board.top + TILE_HEIGHT * 2,
		TILE_WIDTH * _MAX_SAMPLE_W, TILE_WIDTH * (_MAX_SAMPLE_H - 1));
	// 보드를 그릴 버퍼의 크기를 잡아준다.
	// 크기는 구현할 맵의 최대 타일 갯수 * 타일 픽셀 크기
	_boardBuffer = new image;
	_boardBuffer->init((int)(_BOARD_BUFFER_W), (int)(_BOARD_BUFFER_H));
	// 가져온 맵의 왼쪽 끝을 초기위치로 보여준다.
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
//==				#init 초기화								==
//============================================================
HRESULT Maptool::init()
{
	init_defaultBoard();
	init_boardCells();
	init_sampleCells();
	// 여기서 샘플 이미지를 불러온다.
	_sampleImg = IMAGEMANAGER->addImage("SampleTile",
		"resource/image/map/MapTile1.bmp",
		(int)(512 * MULTIPLE_TILE), (int)(320 * MULTIPLE_TILE));
	// 여기서 샘플 버튼을 초기화한다.
	init_sampleButton();
	init_sampleButtonImg();
	// 여기서 추출한 타일을 초기화한다.
	init_extractionTile();
	_bDebug = false;
	// 마우스 커서를 초기화한다.
	MOUSECURSOR->init();
	MOUSECURSOR->set_cursor(false);
	return S_OK;
}
void Maptool::release()
{
}
//============================================================
//==				#update	업데이트							==
//============================================================
void Maptool::update()
{
	// 보드에서 쓸 가상 마우스 좌표를 설정한다.
	set_inBoard_mouse_pt();
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//============================================================
		//==			여기서 타일을 그릴 보드 셀 선택					==
		//============================================================
		if (PtInRect(&_board, _inBoard_mouse_pt))
		{
			select_boardCells();
		}//if: 보드를 클릭했다면
		//============================================================
		//==				여기서 맵타일 셋팅							==
		//============================================================
		if ((bool)(PtInRect(&_sampleBoard, m_ptMouse)) == true
			&& (bool)(PtInRect(&_setRect, m_ptMouse)) == false)
		{
			set_sampleTile();
		}//if: 셋 버튼을 누르지 않고, 샘플 보드를 클릭했다면
	//============================================================
	//==				여기서 버튼 처리							==
	//============================================================
		if (PtInRect(&_setRect, m_ptMouse))
		{
			set_tileToBoard(true);
		}//if: Set 버튼을 클릭했다면
		if (PtInRect(&_delRect, m_ptMouse))
		{
			delete_tileToBoard();
		}//if: Del 버튼을 클릭했다면
		if (PtInRect(&_prevRect, m_ptMouse) && _bPrev == true)
		{
			_sampleIdx--;
		}//if: prev 버튼을 클릭했다면
		if (PtInRect(&_nextRect, m_ptMouse) && _bNext == true)
		{
			_sampleIdx++;
		}//if: prev 버튼을 클릭했다면

	}//if: 마우스 왼클릭
	else if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		//============================================================
		//==			여기서 드래그 렉트 셋팅							==
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
		}//if: 보드의 안을 드래그 중이라면
	}//if: 마우스 왼쪽 드래그
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (PtInRect(&_board, m_ptMouse))
		{
			set_selectEnd(_inBoard_mouse_pt);
			select_boardCells(_selectRect);
			set_selectStart({ 0, 0 });
			set_selectEnd({ 0, 0 });
			_bSelectStart = true;
		}//if: 보드의 안에서 드래그 끝났다면 보드셀을 선택한다.
		else
		{
			set_selectStart({ 0, 0 });
			set_selectEnd({ 0, 0 });
			_bSelectStart = true;
		}//else: 드래그를 이상하게 했다면 값을 0으로 밀어버린다.
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//============================================================
		//==				여기서 보드에 타일 처리						==
		//============================================================
		if (PtInRect(&_board, m_ptMouse) && _extractionTile.bTile == true)
		{
			set_tileToBoard(false);
		}//if: 타일이 존재한다면 보드에 셋
		//============================================================
		//==				여기서 버튼 처리							==
		//============================================================
		if (PtInRect(&_delRect, m_ptMouse))
		{
			delete_tileSelect();
		}//if: Del 버튼을 클릭했다면
	}//if: 마우스 오른클릭
	else if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		//============================================================
		//==				여기서 보드에 타일 처리						==
		//============================================================
		if (PtInRect(&_board, m_ptMouse) && _extractionTile.bTile == true)
		{
			set_tileToBoard(false);
		}
	}//if: 마우스 오른쪽 드래그
	//============================================================
	//==					Save & Load							==
	//============================================================
	if (KEYMANAGER->isOnceKeyDown('2')) { save_map(); }
	else if (KEYMANAGER->isOnceKeyDown('3')) { load_map(); }
	//============================================================
	//==				여기서 방향키 처리							==
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
	// 마우스 커서 업데이트
	MOUSECURSOR->update();
	//============================================================
	//==			디버그모드를 껐다가 키는 부분					==
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
	// 백버퍼 새카맣게 렌더
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	// 보드 버퍼를 새하얗게 렌더
	PatBlt(_boardBuffer->getMemDC(), 0, 0,
		_BOARD_BUFFER_W, _BOARD_BUFFER_H, WHITENESS);
	// 카메라 버퍼 셋팅
	draw_board();
	draw_boardCells();
	draw_sampleImg();
	draw_sampleButton();
	draw_tileToBoard();
	// 여기서 드래그 할 때 보이는 RECT 렌더
	draw_selectRect();
	// 여기서 보드 버퍼를 렌더
	_boardBuffer->render(getMemDC(), _board.left, _board.top,
		(int)(_currentBoard_pt.x * TILE_WIDTH),
		(int)(_currentBoard_pt.y * TILE_HEIGHT),
		(int)(_MAX_BOARD_W * TILE_WIDTH),
		(int)(_MAX_BOARD_H * TILE_HEIGHT));
	if (_bDebug == true) { draw_sampleCells(); }
	// 마우스 커서 렌더
	MOUSECURSOR->render();
}
