#include "stdafx.h"
#include "image.h"
#pragma comment(lib,"msimg32.lib")//���ĺ��带 ����ϱ� ���ؼ� ���̺귯�� �߰�

image::image() :_imageInfo(NULL),
_fileName(NULL),
_isTrans(false),
_transColor(RGB(0, 0, 0)),
_blendImage(NULL)
{
}
image::~image()
{
}
//============================================================
//==				������ ������ ���� �Լ�						==
//============================================================
void image::run_frameDefault()
{
	float speed, delay;
	// �ӵ�, ������ ���� �޾Ƽ� �������� ������.
	speed = _imageInfo->firstOption[1];
	delay = _imageInfo->firstOption[0];
	_imageInfo->firstCounter += (int)(speed);

	if (_imageInfo->firstCounter >= delay)
	{
		if (_imageInfo->currentFrameX < _imageInfo->maxFrameX)
		{
			// �������� �ϳ� �����鼭 ī���͸� �ʱ�ȭ�Ѵ�.
			_imageInfo->currentFrameX++;
			_imageInfo->firstCounter = 0;
		}//if: �������� �ִ� �����Ӻ��� �۴ٸ�
		// �������� ������ ���Ҵٸ� 0���� �ʱ�ȭ�Ѵ�.
		else { _imageInfo->currentFrameX = 0; }
	}//if: �����̸� �ش�.
}
void image::run_frameSection(int section)
{
	float speed, delay;
	// section: ��� ������ ������ ������ �޾Ƽ� ������.
	switch (section)
	{
	case 1:
		// �ӵ�, ������ ���� �޾Ƽ� �������� ������.
		delay = _imageInfo->firstOption[0];
		speed = _imageInfo->firstOption[1];
		_imageInfo->firstCounter += (int)speed;

		if (_imageInfo->firstCounter >= delay)
		{
			if (_imageInfo->currentFrameX < _imageInfo->firstSection[1])
			{
				// �������� �ϳ� �����鼭 ī���͸� �ʱ�ȭ�Ѵ�.
				_imageInfo->currentFrameX++;
				_imageInfo->firstCounter = 0;
			}//if: �������� �ִ� �����Ӻ��� �۰ų� ���ٸ�
			else
			{
				if (_imageInfo->bSection[1] == true)
				{
					_imageInfo->currentFrameX = _imageInfo->secondSection[0];
					_imageInfo->bEnable[0] = false;
					_imageInfo->bEnable[1] = true;
					_imageInfo->bEnable[2] = false;
				}//if: 2��° ������ �����Ѵٸ�
				else
				{
					_imageInfo->currentFrameX = _imageInfo->firstSection[0];
					_imageInfo->bEnable[0] = true;
					_imageInfo->bEnable[1] = false;
					_imageInfo->bEnable[2] = false;
				}//else: 2��° ������ ���ٸ�
			}//else: �������� ������ ���Ҵٸ� start ������ �ʱ�ȭ�Ѵ�.
		}//if: �����̸� �ش�.
		break;
	case 2:
		// �ӵ�, ������ ���� �޾Ƽ� �������� ������.
		delay = _imageInfo->secondOption[0];
		speed = _imageInfo->secondOption[1];
		_imageInfo->secondCounter += (int)speed;

		if (_imageInfo->secondCounter >= delay)
		{
			if (_imageInfo->currentFrameX < _imageInfo->secondSection[1])
			{
				// �������� �ϳ� �����鼭 ī���͸� �ʱ�ȭ�Ѵ�.
				_imageInfo->currentFrameX++;
				_imageInfo->secondCounter = 0;
			}//if: �������� �ִ� �����Ӻ��� �۴ٸ�
			else
			{
				if (_imageInfo->bSection[2] == true)
				{
					_imageInfo->currentFrameX = _imageInfo->thirdSection[0];
					_imageInfo->bEnable[0] = false;
					_imageInfo->bEnable[1] = false;
					_imageInfo->bEnable[2] = true;
				}//if: 3��° ������ �����Ѵٸ�
				else
				{
					_imageInfo->currentFrameX = _imageInfo->firstSection[0];
					_imageInfo->bEnable[0] = true;
					_imageInfo->bEnable[1] = false;
					_imageInfo->bEnable[2] = false;
				}
			}//else: �������� ������ ���Ҵٸ� start ������ �ʱ�ȭ�Ѵ�.
		}//if: �����̸� �ش�.
		break;
	case 3:
		// �ӵ�, ������ ���� �޾Ƽ� �������� ������.
		delay = _imageInfo->thirdOption[0];
		speed = _imageInfo->thirdOption[1];
		_imageInfo->thirdCounter += (int)speed;

		if (_imageInfo->thirdCounter >= delay)
		{
			if (_imageInfo->currentFrameX < _imageInfo->thirdSection[1])
			{
				// �������� �ϳ� �����鼭 ī���͸� �ʱ�ȭ�Ѵ�.
				_imageInfo->currentFrameX++;
				_imageInfo->thirdCounter = 0;
			}//if: �������� �ִ� �����Ӻ��� �۴ٸ�
			else
			{
				_imageInfo->currentFrameX = _imageInfo->firstSection[0];
				_imageInfo->bEnable[0] = true;
				_imageInfo->bEnable[1] = false;
				_imageInfo->bEnable[2] = false;
			}//else: �������� ������ ���Ҵٸ� start ������ �ʱ�ȭ�Ѵ�.
		}//if: �����̸� �ش�.
		break;
	}
}
void image::run_frameSection_reverse(int section)
{
	float speed, delay;
	// section: ��� ������ ������ ������ �޾Ƽ� ������.
	switch (section)
	{
	case 1:
		// �ӵ�, ������ ���� �޾Ƽ� �������� ������.
		delay = _imageInfo->firstOption[0];
		speed = _imageInfo->firstOption[1];
		_imageInfo->firstCounter += (int)speed;

		if (_imageInfo->firstCounter >= delay)
		{
			if (_imageInfo->currentFrameX > _imageInfo->firstSection[1])
			{
				// �������� �ϳ� �����鼭 ī���͸� �ʱ�ȭ�Ѵ�.
				_imageInfo->currentFrameX--;
				_imageInfo->firstCounter = 0;
			}//if: �������� �ִ� �����Ӻ��� �۰ų� ���ٸ�
			else
			{
				if (_imageInfo->bSection[1] == true)
				{
					_imageInfo->currentFrameX = _imageInfo->secondSection[0];
					_imageInfo->bEnable[0] = false;
					_imageInfo->bEnable[1] = true;
					_imageInfo->bEnable[2] = false;
				}//if: 2��° ������ �����Ѵٸ�
				else
				{
					_imageInfo->currentFrameX = _imageInfo->firstSection[0];
					_imageInfo->bEnable[0] = true;
					_imageInfo->bEnable[1] = false;
					_imageInfo->bEnable[2] = false;
				}//else: 2��° ������ ���ٸ�
			}//else: �������� ������ ���Ҵٸ� start ������ �ʱ�ȭ�Ѵ�.
		}//if: �����̸� �ش�.
		break;
	case 2:
		// �ӵ�, ������ ���� �޾Ƽ� �������� ������.
		delay = _imageInfo->secondOption[0];
		speed = _imageInfo->secondOption[1];
		_imageInfo->secondCounter += (int)speed;

		if (_imageInfo->secondCounter >= delay)
		{
			if (_imageInfo->currentFrameX > _imageInfo->secondSection[1])
			{
				// �������� �ϳ� �����鼭 ī���͸� �ʱ�ȭ�Ѵ�.
				_imageInfo->currentFrameX--;
				_imageInfo->secondCounter = 0;
			}//if: �������� �ִ� �����Ӻ��� �۴ٸ�
			else
			{
				if (_imageInfo->bSection[2] == true)
				{
					_imageInfo->currentFrameX = _imageInfo->thirdSection[0];
					_imageInfo->bEnable[0] = false;
					_imageInfo->bEnable[1] = false;
					_imageInfo->bEnable[2] = true;
				}//if: 3��° ������ �����Ѵٸ�
				else
				{
					_imageInfo->currentFrameX = _imageInfo->firstSection[0];
					_imageInfo->bEnable[0] = true;
					_imageInfo->bEnable[1] = false;
					_imageInfo->bEnable[2] = false;
				}
			}//else: �������� ������ ���Ҵٸ� start ������ �ʱ�ȭ�Ѵ�.
		}//if: �����̸� �ش�.
		break;
	case 3:
		// �ӵ�, ������ ���� �޾Ƽ� �������� ������.
		delay = _imageInfo->thirdOption[0];
		speed = _imageInfo->thirdOption[1];
		_imageInfo->thirdCounter += (int)speed;

		if (_imageInfo->thirdCounter >= delay)
		{
			if (_imageInfo->currentFrameX > _imageInfo->thirdSection[1])
			{
				// �������� �ϳ� �����鼭 ī���͸� �ʱ�ȭ�Ѵ�.
				_imageInfo->currentFrameX--;
				_imageInfo->thirdCounter = 0;
			}//if: �������� �ִ� �����Ӻ��� �۴ٸ�
			else
			{
				_imageInfo->currentFrameX = _imageInfo->firstSection[0];
				_imageInfo->bEnable[0] = true;
				_imageInfo->bEnable[1] = false;
				_imageInfo->bEnable[2] = false;
			}//else: �������� ������ ���Ҵٸ� start ������ �ʱ�ȭ�Ѵ�.
		}//if: �����̸� �ش�.
		break;
	}
}
void image::run_frameUpdate(bool bDefault, bool bReverse)
{
	if (bDefault == true)
	{
		run_frameDefault();
	}//if: ������ �������� ���� ����.
	else
	{
		if (_imageInfo->bSection[0] == true &&
			_imageInfo->bEnable[0] == true)
		{
			if (bReverse == true)
			{
				run_frameSection_reverse(1);
			}
			else
			{
				run_frameSection(1);
			}
		}//if: first ������ ������ ������ ���
		else if (_imageInfo->bSection[1] == true &&
			_imageInfo->bEnable[1] == true)
		{
			if (bReverse == true)
			{
				run_frameSection_reverse(2);
			}
			else
			{
				run_frameSection(2);
			}
		}//if: second ������ ������ ������ ���
		else if (_imageInfo->bSection[2] == true &&
			_imageInfo->bEnable[2] == true)
		{
			if (bReverse == true)
			{
				run_frameSection_reverse(3);
			}
			else
			{
				run_frameSection(3);
			}
		}//if: third ������ ������ ������ ���
	}//else: ������ ������ ����.
}
HRESULT image::init(int width, int height)
{
	//�̹��� ������ ����ִٸ� ������
	if (_imageInfo != NULL)release();

	//DC��������(���� �����쿡 ���� ȭ��DC�� �ӽ÷� �޾ƿ�)
	HDC hdc = GetDC(m_hWnd);
	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���ؼ� �޸�DC�� ����� �ִ� �Լ�
	//ȭ�� DC�� �޸� DC ȣȯ
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� ������ �ִ� �Լ�
	//SelectObject
	//�⺻�� ��Ʈ�� �ڵ��� ��ȯ�ϰ�, ���ο� ��Ʈ���� �޸� DC�� �����ϰ�
	//�޸� DC�� ��Ʈ���� �׷���, ȭ�� DC �ƴϹǷ� ���Ϳ� ��� x


	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� �̸�
	_fileName = NULL;


	//���� ���� �ɼ�

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//32��Ʈ�ΰ�� AC_SRC_APLHA�� �����ϰ� �� �ܿ��� 0���� ������(�׷��� ������ ���ĺ��� �Լ� ��� �Ұ�)
	_blendFunc.BlendOp = AC_SRC_OVER;	//���� ������


										//���ĺ��� ����ϱ� ���� �̹��� �ʱ�ȭ
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//����Ű �÷� ����
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//���ҽ��� �����µ� ����������
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}
	//DC����
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL)return E_FAIL;

	//�̹��� ������ �ִٸ� ����
	if (_imageInfo != NULL)release();

	HDC hdc = GetDC(m_hWnd);

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance,
		fileName, IMAGE_BITMAP,
		width,
		height,
		LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// �̹��� ȸ���� ���� ���� ����
	init_forRotate(hdc);

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű
	_isTrans = isTrans;
	_transColor = transColor;


	//���� ���� �ɼ�

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//32��Ʈ�ΰ�� AC_SRC_APLHA�� �����ϰ� �� �ܿ��� 0���� ������(�׷��� ������ ���ĺ��� �Լ� ��� �Ұ�)
	_blendFunc.BlendOp = AC_SRC_OVER;	//���� ������


										//���ĺ��� ����ϱ� ���� �̹��� �ʱ�ȭ
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;


	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ ���� �ƴ϶��(�̹����� ����ִٸ�) �����ض�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(m_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ ����
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//���� ���� �ɼ�

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//32��Ʈ�ΰ�� AC_SRC_APLHA�� �����ϰ� �� �ܿ��� 0���� ������(�׷��� ������ ���ĺ��� �Լ� ��� �Ұ�)
	_blendFunc.BlendOp = AC_SRC_OVER;	//���� ������


										//���ĺ��� ����ϱ� ���� �̹��� �ʱ�ȭ
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;


	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(m_hWnd, hdc);


	return S_OK;
}
//============================================================
//==				������ �̹��� �ε�							==
//============================================================
HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL)return E_FAIL;

	if (_imageInfo != NULL)release();

	HDC hdc = GetDC(m_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance,
		fileName,
		IMAGE_BITMAP,
		width,
		height,
		LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC,
		_imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	// �̹��� ȸ���� ���� ���� ����
	init_forRotate(hdc);

	//���� �̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���� ���� �ɼ�

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//32��Ʈ�ΰ�� AC_SRC_APLHA�� �����ϰ� �� �ܿ��� 0���� ������(�׷��� ������ ���ĺ��� �Լ� ��� �Ұ�)
	_blendFunc.BlendOp = AC_SRC_OVER;	//���� ������


										//���ĺ��� ����ϱ� ���� �̹��� �ʱ�ȭ
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���ҽ��� �����µ� ���� ������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL)return E_FAIL;


	if (_imageInfo != NULL)release();

	HDC hdc = GetDC(m_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance,
		fileName,
		IMAGE_BITMAP,
		width,
		height,
		LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC,
		_imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//���� �̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���� ���� �ɼ�

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//32��Ʈ�ΰ�� AC_SRC_APLHA�� �����ϰ� �� �ܿ��� 0���� ������(�׷��� ������ ���ĺ��� �Լ� ��� �Ұ�)
	_blendFunc.BlendOp = AC_SRC_OVER;	//���� ������


										//���ĺ��� ����ϱ� ���� �̹��� �ʱ�ȭ
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;


	//���ҽ��� �����µ� ���� ������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}
//============================================================
//==				Rotate �̹��� �ε�						==
//============================================================
void image::setTransColor(bool isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}
void image::init_forRotate(HDC hdc)
{
	// Rotate �ϱ� ���ؼ� �� �̹��� ���� ����
	// ȸ���� �̹����� ���簢���� �ƴ� ���, �̹����� �߸� �� �ֱ� ������
	// width, height �� ���̰� �� ���� �������� ���簢�� ������ �����.
	double size;	// ���簢�� ������ ����� ���� ����
	(_imageInfo->width > _imageInfo->height ?
		size = _imageInfo->width * 2 : size = _imageInfo->height * 2);
	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_EMPTY;
	_rotateImage->resID = 0;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, (int)size, (int)size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = (int)size;
	_rotateImage->height = (int)size;
}
//============================================================
//==		�̹��� ȸ���� ���� ����纯�� ������Ʈ				==
//============================================================
void image::update_parallelogram(RECT imageRect, double radian)
{
	// focus�� �̹����� �������� �����Ѵ�.
	POINT focus;
	focus.x = (LONG)((imageRect.left + imageRect.right) * 0.5);
	focus.y = (LONG)((imageRect.top + imageRect.bottom) * 0.5);
	_imageInfo->parallelogram = get_parallelogram_toRect(imageRect);
	_rotateImage->parallelogram = rotate_parallelogramR(
		_imageInfo->parallelogram, focus, radian);
}
//============================================================
//==				������ ���� �ʱ�ȭ							==
//============================================================
void image::set_frameSection(int enableSectionCount,
	int firstStart, int firstEnd, float firstDelay, float firstSpeed,
	int secondStart, int secondEnd, float secondDelay, float secondSpeed,
	int thirdStart, int thirdEnd, float thirdDelay, float thirdSpeed)
{
	// ���� �Է��� ���� ���� ���� �ʱ�ȭ�� �ٸ��� �޴´�.
	switch (enableSectionCount)
	{
	case 3:
		_imageInfo->thirdSection[0] = thirdStart;
		_imageInfo->thirdSection[1] = thirdEnd;
		_imageInfo->thirdOption[0] = thirdDelay;
		_imageInfo->thirdOption[1] = thirdSpeed;
		_imageInfo->bSection[2] = true;
		_imageInfo->bEnable[2] = true;
	case 2:
		_imageInfo->secondSection[0] = secondStart;
		_imageInfo->secondSection[1] = secondEnd;
		_imageInfo->secondOption[0] = secondDelay;
		_imageInfo->secondOption[1] = secondSpeed;
		_imageInfo->bSection[1] = true;
		_imageInfo->bEnable[1] = true;
	case 1:
		_imageInfo->firstSection[0] = firstStart;
		_imageInfo->firstSection[1] = firstEnd;
		_imageInfo->firstOption[0] = firstDelay;
		_imageInfo->firstOption[1] = firstSpeed;
		_imageInfo->bSection[0] = true;
		_imageInfo->bEnable[0] = true;
		break;
	default:
		break;
	}
}
//============================================================
//==				������ ������Ʈ							==
//============================================================
void image::frameUpdate(bool bDefault, bool bReverse)
{
	if (_imageInfo->breakFrame == -1)
	{
		run_frameUpdate(bDefault, bReverse);
	}//if: �극��ũ �������� ���� ���
	else
	{
		_imageInfo->currentFrameX = _imageInfo->breakFrame;
	}

}
void image::set_breakFrame(int breakFrame)
{
	_imageInfo->breakFrame = breakFrame;
}

void image::release()
{
	//�̹��� ������ �ִٸ�
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hOBit);
		DeleteDC(_blendImage->hMemDC);


		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}
}

void image::render(HDC hdc)
{
	if (_isTrans)
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��� �� Ư������ �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� ����� DC
			0,						//����� ��ǥ�� ������x
			0,						//����� ��ǥ�� ������y
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0,						//���� ��������x
			0,						//���� ��������y
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ����(����Ÿ)
	}
	//���� �̹��� �״�� ����Ұų�?
	else
	{
		//SRCCOPY : �������ִ� �Լ� ���� ���θ� �������ؼ� ����
		//DC���� �������� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}
void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		//Ư�������� DC�������� �������ִ� �Լ�
		GdiTransparentBlt(hdc,		//����� DC����
			destX,					//����� DC������ �ѷ��� ��ǥ
			destY,
			_imageInfo->width,		//����� ���� ũ��
			_imageInfo->height,		//����� ���� ũ��
			_imageInfo->hMemDC,		//������ DC
			0, 0,					//������ ��ǥ
			_imageInfo->width,		//������ ���� ũ��
			_imageInfo->height,		//������ ���� ũ��
			_transColor);			//������ Į��
	}
	else
	{
		//����ۿ� �ִ� �� ������ ��Ӻ������ִ� �Լ�
		BitBlt(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}
void image::render(HDC hdc, int destX, int destY, int width, int height)
{
	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			width,
			height,
			_imageInfo->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);
	}
	else
	{
		StretchBlt(hdc, destX, destY, width, height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}
//�Ѹ� ��X, Y           �ѷ��� �� X, Y(left, top)  ����,        ����
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)
	{
		//Ư�������� DC�������� �������ִ� �Լ�
		GdiTransparentBlt(hdc,		//����� DC����
			destX,					//����� DC������ �ѷ��� ��ǥ
			destY,
			sourWidth,				//����� ���� ũ��
			sourHeight,				//����� ���� ũ��
			_imageInfo->hMemDC,		//������ DC
			sourX, sourY,			//������ ��ǥ
			sourWidth,				//������ ���� ũ��
			sourHeight,				//������ ���� ũ��
			_transColor);			//������ Į��
	}
	else
	{
		//����ۿ� �ִ� �� ������ ��Ӻ������ִ� �Լ�
		BitBlt(hdc, destX, destY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		GdiTransparentBlt(hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}
void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_isTrans)
	{
		GdiTransparentBlt(hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}
void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int width, int height)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}
	if (_isTrans)
	{
		GdiTransparentBlt(hdc,
			destX,
			destY,
			width,
			height,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
	}
	else
	{
		StretchBlt(hdc, destX, destY, width, height,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	//���� ����
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//�׷�����(����Ǿ����) �̹����� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;


	//�׷����� DC ����
	RECT rcDest;
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;
	//���� ���� ����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{

		//�ҽ� ������ ���� ���
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ� ���ٸ�(ȭ�� ������ ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ������ ���� �÷��ش�.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ���� ����
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���ΰ��
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ��
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �縸ŭ ����Ʈ���� ��������
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����
			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}
void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha)
{
	//���� ����
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//�׷�����(����Ǿ����) �̹����� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;


	//�׷����� DC ����
	RECT rcDest;
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;
	//���� ���� ����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{

		//�ҽ� ������ ���� ���
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ� ���ٸ�(ȭ�� ������ ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ������ ���� �÷��ش�.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ���� ����
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���ΰ��
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ��
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �縸ŭ ����Ʈ���� ��������
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����
			alphaRender(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top, alpha);
		}
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		//����ؾ� �� DC�� �׷��� �ִ� ������ �׸���
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, (int)(_imageInfo->x), (int)(_imageInfo->y), SRCCOPY);
		//����ؾ� �� �̹����� �׸���.
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _transColor);
		//���� DC�� ����ؾ��� DC�� �׸���.
		AlphaBlend(hdc, (int)(_imageInfo->x), (int)(_imageInfo->y),
			_imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);

	}
	//�����̹��� �״�� ���� ���� �Ҳ���
	else
	{
		AlphaBlend(hdc, (int)(_imageInfo->x), (int)(_imageInfo->y), _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);

	}
}
void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);

	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);

	}
}
void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);

	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);

	}
}

void image::aniRender(HDC hdc, int destX, int destY, animation * ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}
