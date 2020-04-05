#include "stdafx.h"
#include "imageManager.h"

imageManager::imageManager()
{
}
imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{
	return S_OK;
}
void imageManager::release()
{
	deleteAll();
}

image * imageManager::addImage(string strKey, int width, int height)
{
	//�߰��Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ������  ����
	if (img) return img;

	img = new image;
	//�̹����� �ʱ�ȭ ���� ������ 
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image * imageManager::addImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}


	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	if (img) return img;

	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}
	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	_mImageList.insert(make_pair(strKey, img));

	return img;

}
image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	//�߰� �Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ������ ����
	if (img) return img;

	img = new image;
	//�̹����� ����� �ʱ�ȭ ���� ������
	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}
//============================================
//##		�̹���+�ִϸ��̼� �ʱ�ȭ			##
//============================================
image * imageManager::addFrame(string strKey, const char * fileName, 
	int width, int height, int frameX, int frameY, int fps,
	bool reverse, bool loop, bool trans, COLORREF transColor)
{
	//�߰� �Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);
	animation* ani;

	//�߰��Ϸ��� �̹����� �̹� ������ ����
	if (img) return img;

	img = new image;
	ani = new animation;
	//�̹����� ����� �ʱ�ȭ ���� ������
	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}
	// ����� �ʱ�ȭ �Ǿ��ٸ� �ִϸ��̼��� �ʱ�ȭ
	ani->init(img->getWidth(), img->getHeight(), 
		img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);
	// �̹����� �ִϸ��̼��� map�� �߰�
	_mImageList.insert(make_pair(strKey, img));
	_aniList.insert(make_pair(strKey, ani));

	return img;
}

image * imageManager::findImage(string strKey)
{
	mapImageListIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		return key->second;
	}
	return NULL;
}
animation * imageManager::findAnimation(string strKey)
{
	auto ani = _aniList.find(strKey);
	if (ani != _aniList.end())
	{
		return ani->second;
	}
	return nullptr;
}

bool imageManager::deleteImage(string strKey)
{
	//�ش� Ű �˻�
	mapImageListIter key = _mImageList.find(strKey);

	//Ű�� ã����
	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);
		return true;
	}
	return false;
}
bool imageManager::deleteAnimation(string strKey)
{
	auto ani = _aniList.find(strKey);
	if (ani != _aniList.end())
	{
		SAFE_DELETE(ani->second);
		_aniList.erase(ani);
		return true;
	}
	return false;
}

bool imageManager::deleteAll()
{
	//����ü�� ���鼭 ����
	mapImageListIter iter = _mImageList.begin();

	for (iter; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else { ++iter; }
	}
	swap(_mImageList, mapImageList());

	// �ִϸ��̼� ����
	auto aniIter = _aniList.begin();
	for (;aniIter != _aniList.end();)
	{
		if (aniIter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			aniIter = _aniList.erase(aniIter);
		}
		else { ++iter; }
	}
	swap(_aniList, mAniList());
	return true;
}

void imageManager::render(string strKey, HDC hdc)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);

	if (img)img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}
