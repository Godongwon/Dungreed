#pragma once
#include"animation.h"
class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//���ҽ� �ε�
		LOAD_FILE,			//���� �ε�
		LOAD_EMPTY,			//�� ��Ʈ�� ����
		LOAD_END
	};
	typedef struct tagImage
	{
		DWORD	resID;		//���ҽ� ID
		HDC		hMemDC;		//�޸� DC
		HBITMAP hBit;				//��Ʈ��(���ο� ��Ʈ�� �ڵ�)
		HBITMAP hOBit;				//�õ� ��Ʈ��(���� ��Ʈ�� �ڵ�)
		int		width;				//�̹��� ����ũ��
		int		height;				//�̹��� ����ũ��
		BYTE	loadType;			//�ε� Ÿ��
		float	x;					//�̹��� x��ǥ
		float   y;					//�̹��� Y��ǥ
		int		currentFrameX;		//����������X
		int		currentFrameY;		//����������Y
		int		maxFrameX;			//�ִ� X������ ����
		int		maxFrameY;			//�ִ� Y������ ����
		int		frameWidth;			//1������ ���α���
		int		frameHeight;		//1������ ���α���
		// ������ ���� �� 3�������� ������ �ӵ� ���� ������ �ɼ� �߰�
		// Section:		Frame's start ~ end 
		// Option:		Frame's delay, cntSpeed
		// Counter:		�� �������� ���� ī����
		// bSection:	��� ������ Ȱ��ȭ �Ұ���
		// bEnable:		��� ������ Ȱ��ȭ �Ȱ���
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
		// �̹��� ȸ�� ��ų �� ����� ����纯���� ������ ���·� �����Ѵ�.
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
			// ������ ���� �� 3�������� ������ �ӵ� ���� ������ �ɼ� �߰�
			// Section:		Frame's start ~ end 
			// Option:		Frame's delay, cntSpeed
			// Counter:		�� �������� ���� ī����
			// bSection:	��� ������ Ȱ��ȭ �Ұ���
			// bEnable:		��� ������ Ȱ��ȭ �Ȱ���
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
			// �̹��� ȸ���� �� ����� ����纯�� ������
			parallelogram = nullptr;
		}// tagImage
	}IMAGE_INFO, *LPIMAGE_INFO;

	image();
	~image();

private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	LPIMAGE_INFO	_rotateImage;	//Rotate �̹��� ����
	char*			_fileName;		//�̹��� �̸�
	bool			_isTrans;		//���� ��������?
	COLORREF		_transColor;	//���� ���� RGB

	BLENDFUNCTION	_blendFunc;		//���ĺ��� ��������
	LPIMAGE_INFO	_blendImage;	//���� ���带 ����ϱ� ���� �̹��� ����
protected:
	// �̹��� ������ ���� �� ���� �Լ�
	void run_frameDefault();
	void run_frameSection(int section);
	void run_frameSection_reverse(int section);
	void run_frameUpdate(bool bDefualt, bool bReverse);
public:
	//�� ��Ʈ�� �̹��� �ʱ�ȭ
	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height,
		bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, 
		float x, float y, int width, int height,
		bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	//������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans = true, 
		COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, 
		int width, int height, int frameX, int frameY, 
		bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	//���� ����
	void setTransColor(bool isTrans, COLORREF transColor);
	//============================================================
	//==		�̹��� ȸ���� ���� ����纯�� ó���Լ�				==
	//============================================================
	// �̹��� ȸ���� ���ؼ� ����纯��, rotateImage�� ���� �����Ѵ�.
	void init_forRotate(HDC hdc);
	void update_parallelogram(RECT imageRect, double radian);
	//============================================================
	//==			������ �ִϸ��̼��� ���� �Լ�					==
	//============================================================
	void set_frameSection(int enableSectionCount, 
		int firstStart, int firstEnd,
		float firstDelay = 60, float firstSpeed = 1,
		int secondStart = 0, int secondEnd = 0,
		float secondDelay = 60, float secondSpeed = 1,
		int thirdStart = 0, int thirdEnd = 0,
		float thirdDelay = 60, float thirdSpeed = 1);
	// ������ �̹��� ������Ʈ
	void frameUpdate(bool bDefault = true, bool bReverse = false);
	void set_breakFrame(int breakFrame = -1);

	//����
	void release();

	//����(���� ������ ��ġ�� �̹��� ���)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int width, int height);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	//�����ӷ���
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int width, int height);
	//��������(hdc, ������ų����, x������, y������)
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);
	//���ķ���
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	//�ִϷ���
	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	
	//============================================================
	//==				�̹��� ȸ�� �� Render						==
	//============================================================
	// ȸ���� �̹����� ����纯�� ��������
	inline POINT * get_rotateParallelogram() { return _rotateImage->parallelogram; }
	inline POINT * get_parallelogram() { return _imageInfo->parallelogram; }

	//DC�����Ͷ�
	inline HDC getMemDC() { return _imageInfo->hMemDC; }


	//�̹��� ��ǥx ���
	inline float getX() { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	//�̹��� ��ǥy ���
	inline float getY() { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	//�̹��� ���� ��ǥ ����
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//����,����ũ�� ���
	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	//�ٿ�� �ڽ�(�浹��)
	inline RECT getBoundingBox()
	{
		RECT rc = RectMakeCenter((int)(_imageInfo->x), (int)(_imageInfo->y), 
			_imageInfo->width, _imageInfo->height);
		return rc;
	}

	//������ x ����
	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//������ y ����
	inline int getFrameY() { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//1������ ���μ��� ũ��
	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

	//�ƽ������� x,y
	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }


};

