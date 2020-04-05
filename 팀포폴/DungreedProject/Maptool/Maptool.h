#pragma once
#include "base/gameNode.h"
#include "Maptool/MapTile.h"
// ������ ����� ����ü�� �����Ѵ�.

class Maptool : public gameNode
{
private:
	//============================================================
	//==				���� �׸� �� ���� ����						==
	//============================================================
	// ���� ������ ũ��
	static const int _MAX_BOARD_W = 25;
	static const int _MAX_BOARD_H = 18;
	// ���� ������ ũ��
	const int _MAX_SAMPLE_W = 6;
	const int _MAX_SAMPLE_H = 14;
	// Ÿ���� �׸� �����.
	RECT _board;
	// ���忡 Ÿ���� �׸� Cell�̴�.
	Cell _boardCells[_MAX_TILE_H][_MAX_TILE_W];
	// ���� ���� �׸� ����۴�.
	image * _boardBuffer;
	POINT _currentBoard_pt;				// ���� ���ۿ� ������ ���� ��ǥ
	POINT _inBoard_mouse_pt = { 0, };	// ���忡�� �� ���콺 ��ǥ
	// ���콺 �巡�� ���� �� �׸� ��Ʈ��.
	RECT _selectRect;
	bool _bSelectStart = true;
	bool _bDragReverse = false;
	POINT _inBoardClick_pt;
	//============================================================
	//==				���� �׸� �� ���� ����						==
	//============================================================
	RECT _sampleBoard;
	// ���� Ÿ���� �׸� Cell�̴�.
	static const int _CELL_W = 5;
	static const int _CELL_H = 11;
	const int _CELL_BLANK_W = 5;
	const int _CELL_BLANK_H = 4;
	Cell _sampleCells[_CELL_H][_CELL_W];
	// ��� ���� Ÿ���� ���� �ߴ��� �˷��ִ� ������.
	Cell _extractionTile;
	// ���� Ÿ�� �̹�����.
	image * _sampleImg;
	int _tileCountX;
	int _tileCountY;
	// ���� Ÿ�ϼ��� �ε�����.
	int _sampleIdx = 1;
	//============================================================
	//==					��ư ����								==
	//============================================================
	RECT _buttonBoard;
	RECT _settingTileRect;
	RECT _prevRect, _nextRect, _numRect;
	RECT _setRect, _delRect;
	bool _bPrev = false;
	bool _bNext = true;
	// ����׸��� ����
	bool _bDebug;
protected:
	// ���⼭ ���� save, load �Ѵ�.
	void save_map();
	void load_map();
	//============================================================
	//==				���� ó�� �Լ�								==
	//============================================================
	// ���⼭ ������ ������ �����Ѵ�.
	void set_sampleTile();
	void draw_sampleImg();
	void init_extractionTile();
	// ���⼭ ���� ������ Cell�� �ʱ�ȭ�Ѵ�.
	void init_sampleCells();
	void draw_sampleCells();
	//============================================================
	//==				��ư ó�� �Լ�								==
	//============================================================
	// ���� ������ ��ư RECT�� �ʱ�ȭ�Ѵ�.
	void init_sampleButtonRect();
	void draw_sampleButtonRect();
	// ��ư �̹����� �ʱ�ȭ�Ѵ�.
	void init_sampleButtonImg();
	// ���⼭ ���� ������ ��ư�� �ʱ�ȭ�Ѵ�.
	void init_sampleButton();
	void draw_sampleButton();
	//============================================================
	//==				���� ó�� �Լ�								==
	//============================================================
	// ���⼭ ���忡 Ÿ���� �����Ѵ�.
	void set_tileToBoard(bool bSetButton);
	// Ÿ���� ���� �� ó��
	void delete_tileSelect();
	void delete_tileToBoard();
	// ���⼭ Ÿ���� �׸� ���� �����Ѵ�.
	void select_boardCells();
	void select_boardCells(RECT selected_rc);
	// ���⼭ ���带 �ʱ�ȭ�Ѵ�.
	void init_boardCells();
	void init_defaultBoard();
	void draw_board();
	// ������ Ÿ���� �׸��� ���� �Լ��� ���� ��
	void draw_boardCells();
	void draw_boardCell_number(int x, int y,
		char * str, POINT pt, int count);
	void draw_tileToBoard();
	// �巡�� �� �� ���̴� �簢�� ����
	void draw_selectRect();
	// ���忡�� ���� �巡�� �Ҷ� �׸� ��Ʈ�� �����Ѵ�.
	void set_selectStart(POINT pt);
	void set_selectEnd(POINT pt);
	// ���忡�� �� ���콺 ��ǥ�� �����Ѵ�.
	void set_inBoard_mouse_pt();
	// ���� ��ǥ�� ��� ������ �Ѿ�� ���ϵ��� ���´�.
	POINT limit_currentBoard_pt(POINT pt);
public:
	Maptool();
	~Maptool();
	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};