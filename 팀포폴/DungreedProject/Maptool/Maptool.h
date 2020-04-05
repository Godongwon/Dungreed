#pragma once
#include "base/gameNode.h"
#include "Maptool/MapTile.h"
// 맵툴이 사용할 구조체를 정의한다.

class Maptool : public gameNode
{
private:
	//============================================================
	//==				보드 그릴 때 쓰는 변수						==
	//============================================================
	// 맵툴 보드의 크기
	static const int _MAX_BOARD_W = 25;
	static const int _MAX_BOARD_H = 18;
	// 샘플 보드의 크기
	const int _MAX_SAMPLE_W = 6;
	const int _MAX_SAMPLE_H = 14;
	// 타일을 그릴 보드다.
	RECT _board;
	// 보드에 타일을 그릴 Cell이다.
	Cell _boardCells[_MAX_TILE_H][_MAX_TILE_W];
	// 보드 셀을 그릴 백버퍼다.
	image * _boardBuffer;
	POINT _currentBoard_pt;				// 보드 버퍼에 더해줄 가상 좌표
	POINT _inBoard_mouse_pt = { 0, };	// 보드에서 쓸 마우스 좌표
	// 마우스 드래그 했을 때 그릴 렉트다.
	RECT _selectRect;
	bool _bSelectStart = true;
	bool _bDragReverse = false;
	POINT _inBoardClick_pt;
	//============================================================
	//==				샘플 그릴 때 쓰는 변수						==
	//============================================================
	RECT _sampleBoard;
	// 샘플 타일을 그릴 Cell이다.
	static const int _CELL_W = 5;
	static const int _CELL_H = 11;
	const int _CELL_BLANK_W = 5;
	const int _CELL_BLANK_H = 4;
	Cell _sampleCells[_CELL_H][_CELL_W];
	// 어느 샘플 타일을 셋팅 했는지 알려주는 변수다.
	Cell _extractionTile;
	// 샘플 타일 이미지다.
	image * _sampleImg;
	int _tileCountX;
	int _tileCountY;
	// 샘플 타일셋의 인덱스다.
	int _sampleIdx = 1;
	//============================================================
	//==					버튼 변수								==
	//============================================================
	RECT _buttonBoard;
	RECT _settingTileRect;
	RECT _prevRect, _nextRect, _numRect;
	RECT _setRect, _delRect;
	bool _bPrev = false;
	bool _bNext = true;
	// 디버그모드용 변수
	bool _bDebug;
protected:
	// 여기서 맵을 save, load 한다.
	void save_map();
	void load_map();
	//============================================================
	//==				샘플 처리 함수								==
	//============================================================
	// 여기서 선택한 샘플을 셋팅한다.
	void set_sampleTile();
	void draw_sampleImg();
	void init_extractionTile();
	// 여기서 샘플 보드의 Cell을 초기화한다.
	void init_sampleCells();
	void draw_sampleCells();
	//============================================================
	//==				버튼 처리 함수								==
	//============================================================
	// 샘플 보드의 버튼 RECT를 초기화한다.
	void init_sampleButtonRect();
	void draw_sampleButtonRect();
	// 버튼 이미지를 초기화한다.
	void init_sampleButtonImg();
	// 여기서 샘플 보드의 버튼을 초기화한다.
	void init_sampleButton();
	void draw_sampleButton();
	//============================================================
	//==				보드 처리 함수								==
	//============================================================
	// 여기서 보드에 타일을 셋팅한다.
	void set_tileToBoard(bool bSetButton);
	// 타일을 지울 때 처리
	void delete_tileSelect();
	void delete_tileToBoard();
	// 여기서 타일을 그릴 셀을 선택한다.
	void select_boardCells();
	void select_boardCells(RECT selected_rc);
	// 여기서 보드를 초기화한다.
	void init_boardCells();
	void init_defaultBoard();
	void draw_board();
	// 보드의 타일을 그리는 렌더 함수를 모은 것
	void draw_boardCells();
	void draw_boardCell_number(int x, int y,
		char * str, POINT pt, int count);
	void draw_tileToBoard();
	// 드래그 할 때 보이는 사각형 렌더
	void draw_selectRect();
	// 보드에서 내가 드래그 할때 그릴 렉트를 셋팅한다.
	void set_selectStart(POINT pt);
	void set_selectEnd(POINT pt);
	// 보드에서 쓸 마우스 좌표를 셋팅한다.
	void set_inBoard_mouse_pt();
	// 가상 좌표가 출력 범위를 넘어가지 못하도록 막는다.
	POINT limit_currentBoard_pt(POINT pt);
public:
	Maptool();
	~Maptool();
	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳
};