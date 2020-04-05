#pragma once

#define PI		3.141592653
#define PI2		PI*2

#define PI_2	(PI / 2)
#define PI_4	(PI / 4)
#define PI_8	(PI / 8)
#define PI_16	(PI / 16)
#define PI_32	(PI / 32)
namespace UTIL
{
	//�Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);
	float getAngle(float x1, float y1, float x2, float y2);
	// �� ���� �Ÿ��� �������� ������ �� ã��
	//focus: ������, distance: ���ذŸ�, degree: ���ذ���
	POINT get_point_aroundFocusD(POINT focus, double distance, double degree);
	// �� ���� �Ÿ��� �������� ������ �� ã��
	//focus: ������, distance: ���ذŸ�, radian: ���ذ���
	POINT get_point_aroundFocusR(POINT focus, double distance, double radian);
	// �簢���� �������� ����纯���� ������ִ� �Լ�
	POINT * get_parallelogram_toRect(RECT rc);
	// ����纯���� ���ϴ� ������ŭ ȸ�����ִ� �Լ�
	POINT * rotate_parallelogramD(POINT * parallelogram, POINT focus, double degree);
	POINT * rotate_parallelogramR(POINT * parallelogram, POINT focus, double radian);
}