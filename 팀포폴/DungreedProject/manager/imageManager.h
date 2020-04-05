#pragma once
#include "base/singletonBase.h"
#include "base/image.h"
class imageManager : public singletonBase<imageManager>
{
private:
	// map으로 만든 이미지 목록
	typedef map<string, image*> mapImageList;
	typedef map<string, image*>::iterator mapImageListIter;
	// map으로 만든 에니메이션 목록
	typedef map<string, animation*> mAniList;
private:
	mapImageList _mImageList;
	mAniList _aniList;
public:
	imageManager();
	~imageManager();


	HRESULT init();
	void release();
	//키 값으로 빈 비트맵 초기화
	image* addImage(string strKey, int width, int height);
	//키값으로 이미지 파일 초기화
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans = true, COLORREF transColor = RGB(255, 0, 255));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);
	//키값으로 프레임 이미지 파일 초기화
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans = true, COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans = true, COLORREF transColor = RGB(255, 0, 255));
	// 키값, 파일명, 파일너비, 파일높이, 가로프레임수, 세로프레임수, 초당프레임수, 1프레임당 딜레이, 트랜스적용 여부, 트랜스 컬러 
	image* addFrame(string strKey, const char* fileName,
		int width, int height, int frameX, int frameY, int fps = 1,
		bool reverse = false, bool loop = true,
		bool trans = true, COLORREF transColor = RGB(255, 0, 255));
	//이미지 키값으로 찾아서 리턴
	image* findImage(string strKey);
	animation* findAnimation(string strKey);
	//이미지 키값으로 삭제
	bool deleteImage(string strKey);
	bool deleteAnimation(string strKey);
	//이미지 전체삭제
	bool deleteAll();

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
};

