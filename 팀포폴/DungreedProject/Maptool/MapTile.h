#pragma once
// 맵 타일의 셀을 정의한다.
struct Cell
{
	RECT rc = { 0, };		// 셀의 위치
	POINT pt = { 0, };		// 셀의 좌표
	// 가지고 있는 타일 정보
	bool bTile = false;		// 타일을 가지고 있는지 여부
	int tileIdx = 0;	// 어느 샘플 이미지를 가지고 있는지 인덱스
	RECT img_rc = { 0, };	// 어느 샘플 이미지를 가지고 있는지 샘플 위치
	// 타일이 선택됐는지 여부
	bool bSelected = false;
};
// 타일의 크기를 결정하는 부분
const int MULTIPLE_TILE = 2;
#define TILE_WIDTH		16 * MULTIPLE_TILE
#define TILE_HEIGHT		16 * MULTIPLE_TILE
// 타일의 최대 갯수를 결정하는 부분
const int _MAX_TILE_W = WINSIZEX / TILE_WIDTH * 2;
const int _MAX_TILE_H = WINSIZEY / TILE_HEIGHT * 2;
// 보드 버퍼의 크기를 결정하는 부분
const int _BOARD_BUFFER_W = _MAX_TILE_W * TILE_WIDTH;
const int _BOARD_BUFFER_H = _MAX_TILE_H * TILE_HEIGHT;
