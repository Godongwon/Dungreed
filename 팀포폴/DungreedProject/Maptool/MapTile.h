#pragma once
// �� Ÿ���� ���� �����Ѵ�.
struct Cell
{
	RECT rc = { 0, };		// ���� ��ġ
	POINT pt = { 0, };		// ���� ��ǥ
	// ������ �ִ� Ÿ�� ����
	bool bTile = false;		// Ÿ���� ������ �ִ��� ����
	int tileIdx = 0;	// ��� ���� �̹����� ������ �ִ��� �ε���
	RECT img_rc = { 0, };	// ��� ���� �̹����� ������ �ִ��� ���� ��ġ
	// Ÿ���� ���õƴ��� ����
	bool bSelected = false;
};
// Ÿ���� ũ�⸦ �����ϴ� �κ�
const int MULTIPLE_TILE = 2;
#define TILE_WIDTH		16 * MULTIPLE_TILE
#define TILE_HEIGHT		16 * MULTIPLE_TILE
// Ÿ���� �ִ� ������ �����ϴ� �κ�
const int _MAX_TILE_W = WINSIZEX / TILE_WIDTH * 2;
const int _MAX_TILE_H = WINSIZEY / TILE_HEIGHT * 2;
// ���� ������ ũ�⸦ �����ϴ� �κ�
const int _BOARD_BUFFER_W = _MAX_TILE_W * TILE_WIDTH;
const int _BOARD_BUFFER_H = _MAX_TILE_H * TILE_HEIGHT;
