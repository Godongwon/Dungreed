#include "stdafx.h"
#include "image.h"
#pragma comment(lib,"msimg32.lib")//알파블렌드를 사용하기 위해서 라이브러리 추가

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
//==				프레임 돌릴때 쓰는 함수						==
//============================================================
void image::run_frameDefault()
{
	float speed, delay;
	// 속도, 딜레이 값을 받아서 프레임을 돌린다.
	speed = _imageInfo->firstOption[1];
	delay = _imageInfo->firstOption[0];
	_imageInfo->firstCounter += (int)(speed);

	if (_imageInfo->firstCounter >= delay)
	{
		if (_imageInfo->currentFrameX < _imageInfo->maxFrameX)
		{
			// 프레임을 하나 돌리면서 카운터를 초기화한다.
			_imageInfo->currentFrameX++;
			_imageInfo->firstCounter = 0;
		}//if: 프레임이 최대 프레임보다 작다면
		// 프레임이 끝가지 돌았다면 0으로 초기화한다.
		else { _imageInfo->currentFrameX = 0; }
	}//if: 딜레이를 준다.
}
void image::run_frameSection(int section)
{
	float speed, delay;
	// section: 어느 섹션을 프레임 돌릴지 받아서 돌린다.
	switch (section)
	{
	case 1:
		// 속도, 딜레이 값을 받아서 프레임을 돌린다.
		delay = _imageInfo->firstOption[0];
		speed = _imageInfo->firstOption[1];
		_imageInfo->firstCounter += (int)speed;

		if (_imageInfo->firstCounter >= delay)
		{
			if (_imageInfo->currentFrameX < _imageInfo->firstSection[1])
			{
				// 프레임을 하나 돌리면서 카운터를 초기화한다.
				_imageInfo->currentFrameX++;
				_imageInfo->firstCounter = 0;
			}//if: 프레임이 최대 프레임보다 작거나 같다면
			else
			{
				if (_imageInfo->bSection[1] == true)
				{
					_imageInfo->currentFrameX = _imageInfo->secondSection[0];
					_imageInfo->bEnable[0] = false;
					_imageInfo->bEnable[1] = true;
					_imageInfo->bEnable[2] = false;
				}//if: 2번째 섹션이 존재한다면
				else
				{
					_imageInfo->currentFrameX = _imageInfo->firstSection[0];
					_imageInfo->bEnable[0] = true;
					_imageInfo->bEnable[1] = false;
					_imageInfo->bEnable[2] = false;
				}//else: 2번째 섹션이 없다면
			}//else: 프레임이 끝가지 돌았다면 start 값으로 초기화한다.
		}//if: 딜레이를 준다.
		break;
	case 2:
		// 속도, 딜레이 값을 받아서 프레임을 돌린다.
		delay = _imageInfo->secondOption[0];
		speed = _imageInfo->secondOption[1];
		_imageInfo->secondCounter += (int)speed;

		if (_imageInfo->secondCounter >= delay)
		{
			if (_imageInfo->currentFrameX < _imageInfo->secondSection[1])
			{
				// 프레임을 하나 돌리면서 카운터를 초기화한다.
				_imageInfo->currentFrameX++;
				_imageInfo->secondCounter = 0;
			}//if: 프레임이 최대 프레임보다 작다면
			else
			{
				if (_imageInfo->bSection[2] == true)
				{
					_imageInfo->currentFrameX = _imageInfo->thirdSection[0];
					_imageInfo->bEnable[0] = false;
					_imageInfo->bEnable[1] = false;
					_imageInfo->bEnable[2] = true;
				}//if: 3번째 섹션이 존재한다면
				else
				{
					_imageInfo->currentFrameX = _imageInfo->firstSection[0];
					_imageInfo->bEnable[0] = true;
					_imageInfo->bEnable[1] = false;
					_imageInfo->bEnable[2] = false;
				}
			}//else: 프레임이 끝가지 돌았다면 start 값으로 초기화한다.
		}//if: 딜레이를 준다.
		break;
	case 3:
		// 속도, 딜레이 값을 받아서 프레임을 돌린다.
		delay = _imageInfo->thirdOption[0];
		speed = _imageInfo->thirdOption[1];
		_imageInfo->thirdCounter += (int)speed;

		if (_imageInfo->thirdCounter >= delay)
		{
			if (_imageInfo->currentFrameX < _imageInfo->thirdSection[1])
			{
				// 프레임을 하나 돌리면서 카운터를 초기화한다.
				_imageInfo->currentFrameX++;
				_imageInfo->thirdCounter = 0;
			}//if: 프레임이 최대 프레임보다 작다면
			else
			{
				_imageInfo->currentFrameX = _imageInfo->firstSection[0];
				_imageInfo->bEnable[0] = true;
				_imageInfo->bEnable[1] = false;
				_imageInfo->bEnable[2] = false;
			}//else: 프레임이 끝가지 돌았다면 start 값으로 초기화한다.
		}//if: 딜레이를 준다.
		break;
	}
}
void image::run_frameSection_reverse(int section)
{
	float speed, delay;
	// section: 어느 섹션을 프레임 돌릴지 받아서 돌린다.
	switch (section)
	{
	case 1:
		// 속도, 딜레이 값을 받아서 프레임을 돌린다.
		delay = _imageInfo->firstOption[0];
		speed = _imageInfo->firstOption[1];
		_imageInfo->firstCounter += (int)speed;

		if (_imageInfo->firstCounter >= delay)
		{
			if (_imageInfo->currentFrameX > _imageInfo->firstSection[1])
			{
				// 프레임을 하나 돌리면서 카운터를 초기화한다.
				_imageInfo->currentFrameX--;
				_imageInfo->firstCounter = 0;
			}//if: 프레임이 최대 프레임보다 작거나 같다면
			else
			{
				if (_imageInfo->bSection[1] == true)
				{
					_imageInfo->currentFrameX = _imageInfo->secondSection[0];
					_imageInfo->bEnable[0] = false;
					_imageInfo->bEnable[1] = true;
					_imageInfo->bEnable[2] = false;
				}//if: 2번째 섹션이 존재한다면
				else
				{
					_imageInfo->currentFrameX = _imageInfo->firstSection[0];
					_imageInfo->bEnable[0] = true;
					_imageInfo->bEnable[1] = false;
					_imageInfo->bEnable[2] = false;
				}//else: 2번째 섹션이 없다면
			}//else: 프레임이 끝가지 돌았다면 start 값으로 초기화한다.
		}//if: 딜레이를 준다.
		break;
	case 2:
		// 속도, 딜레이 값을 받아서 프레임을 돌린다.
		delay = _imageInfo->secondOption[0];
		speed = _imageInfo->secondOption[1];
		_imageInfo->secondCounter += (int)speed;

		if (_imageInfo->secondCounter >= delay)
		{
			if (_imageInfo->currentFrameX > _imageInfo->secondSection[1])
			{
				// 프레임을 하나 돌리면서 카운터를 초기화한다.
				_imageInfo->currentFrameX--;
				_imageInfo->secondCounter = 0;
			}//if: 프레임이 최대 프레임보다 작다면
			else
			{
				if (_imageInfo->bSection[2] == true)
				{
					_imageInfo->currentFrameX = _imageInfo->thirdSection[0];
					_imageInfo->bEnable[0] = false;
					_imageInfo->bEnable[1] = false;
					_imageInfo->bEnable[2] = true;
				}//if: 3번째 섹션이 존재한다면
				else
				{
					_imageInfo->currentFrameX = _imageInfo->firstSection[0];
					_imageInfo->bEnable[0] = true;
					_imageInfo->bEnable[1] = false;
					_imageInfo->bEnable[2] = false;
				}
			}//else: 프레임이 끝가지 돌았다면 start 값으로 초기화한다.
		}//if: 딜레이를 준다.
		break;
	case 3:
		// 속도, 딜레이 값을 받아서 프레임을 돌린다.
		delay = _imageInfo->thirdOption[0];
		speed = _imageInfo->thirdOption[1];
		_imageInfo->thirdCounter += (int)speed;

		if (_imageInfo->thirdCounter >= delay)
		{
			if (_imageInfo->currentFrameX > _imageInfo->thirdSection[1])
			{
				// 프레임을 하나 돌리면서 카운터를 초기화한다.
				_imageInfo->currentFrameX--;
				_imageInfo->thirdCounter = 0;
			}//if: 프레임이 최대 프레임보다 작다면
			else
			{
				_imageInfo->currentFrameX = _imageInfo->firstSection[0];
				_imageInfo->bEnable[0] = true;
				_imageInfo->bEnable[1] = false;
				_imageInfo->bEnable[2] = false;
			}//else: 프레임이 끝가지 돌았다면 start 값으로 초기화한다.
		}//if: 딜레이를 준다.
		break;
	}
}
void image::run_frameUpdate(bool bDefault, bool bReverse)
{
	if (bDefault == true)
	{
		run_frameDefault();
	}//if: 섹션을 설정하지 않은 경우다.
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
		}//if: first 섹션의 프레임 돌리는 경우
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
		}//if: second 섹션의 프레임 돌리는 경우
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
		}//if: third 섹션의 프레임 돌리는 경우
	}//else: 섹션을 설정한 경우다.
}
HRESULT image::init(int width, int height)
{
	//이미지 정보가 들어있다면 릴리즈
	if (_imageInfo != NULL)release();

	//DC가져오기(현재 윈도우에 대한 화면DC를 임시로 받아옴)
	HDC hdc = GetDC(m_hWnd);
	//CreateCompatibleDC
	//비트맵을 출력하기 위해서 메모리DC를 만들어 주는 함수
	//화면 DC와 메모리 DC 호환
	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵을 생성해 주는 함수
	//SelectObject
	//기본의 비트맵 핸들을 반환하고, 새로운 비트맵을 메모리 DC가 선택하고
	//메모리 DC에 비트맵이 그려짐, 화면 DC 아니므로 모리터에 출력 x


	//이미지 정보 생성
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일 이름
	_fileName = NULL;


	//알파 블렌드 옵션

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//32비트인경우 AC_SRC_APLHA를 지정하고 그 외에는 0으로 지정함(그렇지 않으면 알파블렌딩 함수 사용 불가)
	_blendFunc.BlendOp = AC_SRC_OVER;	//블렌딩 연산자


										//알파블렌드 사용하기 위한 이미지 초기화
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//투명키 컬러 셋팅
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//리소스를 얻어오는데 실패했을때
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}
	//DC해제
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL)return E_FAIL;

	//이미지 정보가 있다면 해제
	if (_imageInfo != NULL)release();

	HDC hdc = GetDC(m_hWnd);

	//이미지 정보 생성
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

	// 이미지 회전을 위한 정보 생성
	init_forRotate(hdc);

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키
	_isTrans = isTrans;
	_transColor = transColor;


	//알파 블렌드 옵션

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//32비트인경우 AC_SRC_APLHA를 지정하고 그 외에는 0으로 지정함(그렇지 않으면 알파블렌딩 함수 사용 불가)
	_blendFunc.BlendOp = AC_SRC_OVER;	//블렌딩 연산자


										//알파블렌드 사용하기 위한 이미지 초기화
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

	//이미지 정보가 널이 아니라면(이미지가 들어있다면) 해제해라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(m_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 생성
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

	//알파 블렌드 옵션

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//32비트인경우 AC_SRC_APLHA를 지정하고 그 외에는 0으로 지정함(그렇지 않으면 알파블렌딩 함수 사용 불가)
	_blendFunc.BlendOp = AC_SRC_OVER;	//블렌딩 연산자


										//알파블렌드 사용하기 위한 이미지 초기화
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
//==				프레임 이미지 로드							==
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

	// 이미지 회전을 위한 정보 생성
	init_forRotate(hdc);

	//파일 이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//알파 블렌드 옵션

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//32비트인경우 AC_SRC_APLHA를 지정하고 그 외에는 0으로 지정함(그렇지 않으면 알파블렌딩 함수 사용 불가)
	_blendFunc.BlendOp = AC_SRC_OVER;	//블렌딩 연산자


										//알파블렌드 사용하기 위한 이미지 초기화
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//리소스를 얻어오는데 실패 했을때
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
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

	//파일 이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//알파 블렌드 옵션

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//32비트인경우 AC_SRC_APLHA를 지정하고 그 외에는 0으로 지정함(그렇지 않으면 알파블렌딩 함수 사용 불가)
	_blendFunc.BlendOp = AC_SRC_OVER;	//블렌딩 연산자


										//알파블렌드 사용하기 위한 이미지 초기화
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;


	//리소스를 얻어오는데 실패 했을때
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}
//============================================================
//==				Rotate 이미지 로드						==
//============================================================
void image::setTransColor(bool isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}
void image::init_forRotate(HDC hdc)
{
	// Rotate 하기 위해서 빈 이미지 정보 생성
	// 회전한 이미지가 정사각형이 아닐 경우, 이미지가 잘릴 수 있기 때문에
	// width, height 중 길이가 긴 것을 기준으로 정사각형 공간을 만든다.
	double size;	// 정사각형 공간을 만들기 위한 변수
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
//==		이미지 회전을 위한 평행사변형 업데이트				==
//============================================================
void image::update_parallelogram(RECT imageRect, double radian)
{
	// focus는 이미지의 중점으로 설정한다.
	POINT focus;
	focus.x = (LONG)((imageRect.left + imageRect.right) * 0.5);
	focus.y = (LONG)((imageRect.top + imageRect.bottom) * 0.5);
	_imageInfo->parallelogram = get_parallelogram_toRect(imageRect);
	_rotateImage->parallelogram = rotate_parallelogramR(
		_imageInfo->parallelogram, focus, radian);
}
//============================================================
//==				프레임 섹션 초기화							==
//============================================================
void image::set_frameSection(int enableSectionCount,
	int firstStart, int firstEnd, float firstDelay, float firstSpeed,
	int secondStart, int secondEnd, float secondDelay, float secondSpeed,
	int thirdStart, int thirdEnd, float thirdDelay, float thirdSpeed)
{
	// 내가 입력한 섹션 수에 따라서 초기화를 다르게 받는다.
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
//==				프레임 업데이트							==
//============================================================
void image::frameUpdate(bool bDefault, bool bReverse)
{
	if (_imageInfo->breakFrame == -1)
	{
		run_frameUpdate(bDefault, bReverse);
	}//if: 브레이크 프레임이 없을 경우
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
	//이미지 정보가 있다면
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
		//GdiTransparentBlt : 비트맵을 불러올 때 특정색상 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 장소의 DC
			0,						//복사될 좌표의 시작점x
			0,						//복사될 좌표의 시작점y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0,						//복사 시작지점x
			0,						//복사 시작지점y
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상(마젠타)
	}
	//원본 이미지 그대로 출력할거냐?
	else
	{
		//SRCCOPY : 복사해주는 함수 가로 세로를 재정의해서 복사
		//DC간의 영역끼리 고속복사 해주는 함수
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}
void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		//특정색상을 DC영역에서 제외해주는 함수
		GdiTransparentBlt(hdc,		//복사될 DC영역
			destX,					//복사될 DC영역에 뿌려줄 좌표
			destY,
			_imageInfo->width,		//복사될 가로 크기
			_imageInfo->height,		//복사될 세로 크기
			_imageInfo->hMemDC,		//복사할 DC
			0, 0,					//복사할 좌표
			_imageInfo->width,		//복사할 가로 크기
			_imageInfo->height,		//복사할 세로 크기
			_transColor);			//제외할 칼라
	}
	else
	{
		//백버퍼에 있는 걸 앞으로 고속복사해주는 함수
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
//뿌릴 곳X, Y           뿌려올 곳 X, Y(left, top)  가로,        세로
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)
	{
		//특정색상을 DC영역에서 제외해주는 함수
		GdiTransparentBlt(hdc,		//복사될 DC영역
			destX,					//복사될 DC영역에 뿌려줄 좌표
			destY,
			sourWidth,				//복사될 가로 크기
			sourHeight,				//복사될 세로 크기
			_imageInfo->hMemDC,		//복사할 DC
			sourX, sourY,			//복사할 좌표
			sourWidth,				//복사할 가로 크기
			sourHeight,				//복사할 세로 크기
			_transColor);			//제외할 칼라
	}
	else
	{
		//백버퍼에 있는 걸 앞으로 고속복사해주는 함수
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
	//정밀 보정
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//그려지는(복사되어오는) 이미지의 영역
	RECT rcSour;
	int sourWidth;
	int sourHeight;


	//그려지는 DC 영역
	RECT rcDest;
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;
	//세로 루프 영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{

		//소스 영역의 높이 계산
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어 갔다면(화면 밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀의 값을 올려준다.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프 영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 가로계산
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어가면
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 양만큼 라이트값을 왼쪽으로
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자
			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}
void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha)
{
	//정밀 보정
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//그려지는(복사되어오는) 이미지의 영역
	RECT rcSour;
	int sourWidth;
	int sourHeight;


	//그려지는 DC 영역
	RECT rcDest;
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;
	//세로 루프 영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{

		//소스 영역의 높이 계산
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어 갔다면(화면 밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀의 값을 올려준다.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프 영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 가로계산
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어가면
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 양만큼 라이트값을 왼쪽으로
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자
			alphaRender(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top, alpha);
		}
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		//출력해야 될 DC에 그려져 있는 내용을 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, (int)(_imageInfo->x), (int)(_imageInfo->y), SRCCOPY);
		//출력해야 될 이미지를 그린다.
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _transColor);
		//블렌드 DC를 출력해야할 DC에 그린다.
		AlphaBlend(hdc, (int)(_imageInfo->x), (int)(_imageInfo->y),
			_imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);

	}
	//원본이미지 그대로 알파 블렌딩 할꺼냐
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
