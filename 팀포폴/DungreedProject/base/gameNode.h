#pragma once
#include"image.h"

//����� �̹����� ����ƽ���� ����

//static image* _backBuffer = IMAGEMANAGER->addImage("backbuffer", WINSIZEX, WINSIZEY);
class gameNode
{

private:
	static image * _backBuffer;		//�����

									//void setBackBuffer();		//����� ����

	HDC _hdc;
	bool _managerInit;

public:
	gameNode();
	~gameNode();


	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void render();


	static image* setBackBuffer();

	//����� ������
	image* getBackBuffer() { return _backBuffer; }

	//�߰�(�޸� DC)
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	//�߰� HDC���
	HDC getHDC() { return _hdc; }


	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

