#pragma once
#include "base/singletonBase.h"
#include "base/image.h"
class imageManager : public singletonBase<imageManager>
{
private:
	// map���� ���� �̹��� ���
	typedef map<string, image*> mapImageList;
	typedef map<string, image*>::iterator mapImageListIter;
	// map���� ���� ���ϸ��̼� ���
	typedef map<string, animation*> mAniList;
private:
	mapImageList _mImageList;
	mAniList _aniList;
public:
	imageManager();
	~imageManager();


	HRESULT init();
	void release();
	//Ű ������ �� ��Ʈ�� �ʱ�ȭ
	image* addImage(string strKey, int width, int height);
	//Ű������ �̹��� ���� �ʱ�ȭ
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans = true, COLORREF transColor = RGB(255, 0, 255));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);
	//Ű������ ������ �̹��� ���� �ʱ�ȭ
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans = true, COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans = true, COLORREF transColor = RGB(255, 0, 255));
	// Ű��, ���ϸ�, ���ϳʺ�, ���ϳ���, ���������Ӽ�, ���������Ӽ�, �ʴ������Ӽ�, 1�����Ӵ� ������, Ʈ�������� ����, Ʈ���� �÷� 
	image* addFrame(string strKey, const char* fileName,
		int width, int height, int frameX, int frameY, int fps = 1,
		bool reverse = false, bool loop = true,
		bool trans = true, COLORREF transColor = RGB(255, 0, 255));
	//�̹��� Ű������ ã�Ƽ� ����
	image* findImage(string strKey);
	animation* findAnimation(string strKey);
	//�̹��� Ű������ ����
	bool deleteImage(string strKey);
	bool deleteAnimation(string strKey);
	//�̹��� ��ü����
	bool deleteAll();

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
};

