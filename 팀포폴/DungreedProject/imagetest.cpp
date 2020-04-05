#include "stdafx.h"
#include "imagetest.h"

imagetest::imagetest()
{
}
imagetest::~imagetest()
{
}

HRESULT imagetest::init()
{
	_img = new image;
	_img->init("resource/image/�÷��̾�/����.bmp", 21, 17);
	_centerFocus.x = (LONG)(WINSIZEX * 0.5);
	_centerFocus.y = (LONG)(WINSIZEY * 0.5);
	_centerRect = RectMakeCenter(_centerFocus.x, _centerFocus.y, 20, 20);
	_imgAngle = 0;
	_img_center = get_point_aroundFocusR(_centerFocus, 50, _imgAngle);
	_img_rc = RectMakeCenter(_img_center.x, _img_center.y,
		_img->getWidth(), _img->getHeight());
	_img_parall = get_parallelogram_toRect(_img_rc);
	_img_parallRotate = _img_parall;
	return S_OK;
}

void imagetest::release()
{
}

void imagetest::update()
{
	_imgAngle = getAngle(_centerFocus.x, _centerFocus.y,
		m_ptMouse.x, m_ptMouse.y);
	_img_center = get_point_aroundFocusR(_centerFocus, 50, _imgAngle);
	_img_rc = RectMakeCenter(_img_center.x, _img_center.y,
		_img->getWidth(), _img->getHeight());
	// �������� ���⼭ ������Ʈ
	_img_parall = get_parallelogram_toRect(_img_rc);
	_img_parallRotate = rotate_parallelogramR(_img_parall, _img_center, _imgAngle);
	// �̹����� ���⼭ ȸ��
	_img->update_parallelogram(_img_rc, _imgAngle);
}

void imagetest::render()
{
	// ������
	Polygon(getMemDC(), _img_parallRotate, 4);
	Polygon(getMemDC(), _img->get_rotateParallelogram(), 4);
	// ���� 
	wsprintf(str, "����: (%d, %d), (%d, %d), (%d, %d), (%d, %d)",
		_img_parallRotate[0].x, _img_parallRotate[0].y,
		_img_parallRotate[1].x, _img_parallRotate[1].y,
		_img_parallRotate[2].x, _img_parallRotate[2].y,
		_img_parallRotate[3].x, _img_parallRotate[3].y);
	TextOut(getMemDC(), 20, 20, str, strlen(str));
	// �� �̹��� �� 
	wsprintf(str, "�̹���: (%d, %d), (%d, %d), (%d, %d), (%d, %d)",
		_img->get_rotateParallelogram()[0].x, _img->get_rotateParallelogram()[0].y,
		_img->get_rotateParallelogram()[1].x, _img->get_rotateParallelogram()[1].y,
		_img->get_rotateParallelogram()[2].x, _img->get_rotateParallelogram()[2].y,
		_img->get_rotateParallelogram()[3].x, _img->get_rotateParallelogram()[3].y);
	TextOut(getMemDC(), 20, 40, str, strlen(str));

	// ����
	Rectangle(getMemDC(), _centerRect.left, _centerRect.top, 
		_centerRect.right, _centerRect.bottom);
}