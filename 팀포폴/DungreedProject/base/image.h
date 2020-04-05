#pragma once
#include"animation.h"
class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//리소스 로딩
		LOAD_FILE,			//파일 로딩
		LOAD_EMPTY,			//빈 비트맵 파일
		LOAD_END
	};
	typedef struct tagImage
	{
		DWORD	resID;		//리소스 ID
		HDC		hMemDC;		//메모리 DC
		HBITMAP hBit;				//비트맵(새로운 비트맵 핸들)
		HBITMAP hOBit;				//올드 비트맵(기존 비트맵 핸들)
		int		width;				//이미지 가로크기
		int		height;				//이미지 세로크기
		BYTE	loadType;			//로드 타입
		float	x;					//이미지 x좌표
		float   y;					//이미지 Y좌표
		int		currentFrameX;		//현재프레임X
		int		currentFrameY;		//현재프레임Y
		int		maxFrameX;			//최대 X프레임 갯수
		int		maxFrameY;			//최대 Y프레임 갯수
		int		frameWidth;			//1프레임 가로길이
		int		frameHeight;		//1프레임 세로길이
		// 프레임 돌릴 때 3구간으로 나눠서 속도 조절 가능한 옵션 추가
		// Section:		Frame's start ~ end 
		// Option:		Frame's delay, cntSpeed
		// Counter:		각 프레임을 돌릴 카운터
		// bSection:	어느 섹션을 활성화 할건지
		// bEnable:		어느 섹션이 활성화 된건지
		int		firstSection[2];
		float	firstOption[2];
		int		firstCounter;
		int		secondSection[2];
		float	secondOption[2];
		int		secondCounter;
		int		thirdSection[2];
		float	thirdOption[2];
		int		thirdCounter;
		bool	bSection[3];
		bool	bEnable[3];
		int		breakFrame;
		// 이미지 회전 시킬 때 사용할 평행사변형을 폴리곤 형태로 정의한다.
		POINT * parallelogram;

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			x = 0;
			y = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
			// 프레임 돌릴 때 3구간으로 나눠서 속도 조절 가능한 옵션 추가
			// Section:		Frame's start ~ end 
			// Option:		Frame's delay, cntSpeed
			// Counter:		각 프레임을 돌릴 카운터
			// bSection:	어느 섹션을 활성화 할건지
			// bEnable:		어느 섹션이 활성화 된건지
			firstSection[2] = { 0, };
			firstOption[0] = 60;
			firstOption[1] = 1;
			firstCounter = 0;
			secondSection[2] = { 0, };
			secondOption[0] = 60;
			secondOption[1] = 1;
			secondCounter = 0;
			thirdSection[2] = { 0, };
			thirdOption[0] = 60;
			thirdOption[1] = 1;
			thirdCounter = 0;
			bSection[3] = { 0, };
			bEnable[3] = { 0, };
			breakFrame = -1;
			// 이미지 회전할 때 사용할 평행사변형 폴리곤
			parallelogram = nullptr;
		}// tagImage
	}IMAGE_INFO, *LPIMAGE_INFO;

	image();
	~image();

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	LPIMAGE_INFO	_rotateImage;	//Rotate 이미지 정보
	char*			_fileName;		//이미지 이름
	bool			_isTrans;		//배경색 날릴꺼니?
	COLORREF		_transColor;	//배경색 없앨 RGB

	BLENDFUNCTION	_blendFunc;		//알파블렌드 위한정보
	LPIMAGE_INFO	_blendImage;	//알파 블렌드를 사용하기 위한 이미지 정보
protected:
	// 이미지 프레임 돌릴 때 쓰는 함수
	void run_frameDefault();
	void run_frameSection(int section);
	void run_frameSection_reverse(int section);
	void run_frameUpdate(bool bDefualt, bool bReverse);
public:
	//빈 비트맵 이미지 초기화
	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height,
		bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, 
		float x, float y, int width, int height,
		bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	//프레임 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans = true, 
		COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, 
		int width, int height, int frameX, int frameY, 
		bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	//투명값 셋팅
	void setTransColor(bool isTrans, COLORREF transColor);
	//============================================================
	//==		이미지 회전을 위한 평행사변형 처리함수				==
	//============================================================
	// 이미지 회전을 위해서 평행사변형, rotateImage를 전부 설정한다.
	void init_forRotate(HDC hdc);
	void update_parallelogram(RECT imageRect, double radian);
	//============================================================
	//==			프레임 애니메이션을 위한 함수					==
	//============================================================
	void set_frameSection(int enableSectionCount, 
		int firstStart, int firstEnd,
		float firstDelay = 60, float firstSpeed = 1,
		int secondStart = 0, int secondEnd = 0,
		float secondDelay = 60, float secondSpeed = 1,
		int thirdStart = 0, int thirdEnd = 0,
		float thirdDelay = 60, float thirdSpeed = 1);
	// 프레임 이미지 업데이트
	void frameUpdate(bool bDefault = true, bool bReverse = false);
	void set_breakFrame(int breakFrame = -1);

	//삭제
	void release();

	//렌더(내가 지정한 위치에 이미지 출력)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int width, int height);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	//프레임렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int width, int height);
	//루프렌더(hdc, 루프시킬영역, x오프셋, y오프셋)
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);
	//알파렌더
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	//애니렌더
	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	
	//============================================================
	//==				이미지 회전 후 Render						==
	//============================================================
	// 회전할 이미지의 평행사변형 가져오기
	inline POINT * get_rotateParallelogram() { return _rotateImage->parallelogram; }
	inline POINT * get_parallelogram() { return _imageInfo->parallelogram; }

	//DC가져와라
	inline HDC getMemDC() { return _imageInfo->hMemDC; }


	//이미지 좌표x 얻기
	inline float getX() { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	//이미지 좌표y 얻기
	inline float getY() { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	//이미지 센터 좌표 셋팅
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//가로,세로크기 얻기
	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	//바운딩 박스(충돌용)
	inline RECT getBoundingBox()
	{
		RECT rc = RectMakeCenter((int)(_imageInfo->x), (int)(_imageInfo->y), 
			_imageInfo->width, _imageInfo->height);
		return rc;
	}

	//프레임 x 셋팅
	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//프레임 y 셋팅
	inline int getFrameY() { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//1프레임 가로세로 크기
	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

	//맥스프레임 x,y
	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }


};

