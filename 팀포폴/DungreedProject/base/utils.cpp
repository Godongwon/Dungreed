#include "stdafx.h"
#include "utils.h"

namespace UTIL
{
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		if (y2 > y1)
		{
			angle = -angle;

			if (angle >= (float)(2 * PI)) angle -= (float)(2 * PI);
		}

		return angle;
	}
	POINT get_point_aroundFocusD(POINT focus, double distance, double degree)
	{
		// ������ �� focus ���� distance ��ŭ ������ �ִ� ���� ���ϴ� �Լ�
		double seta = PI * degree / 180;	//�ﰢ�Լ��� �� seta ��(radian)
		POINT destination = { 0, };		//ã�Ƴ� ��
		// ��Ȯ�� ����� ���ؼ� double �ӽ� ������ ����Ѵ�.
		double x, y;
		// sin(seta), cos(seta)�� �Ÿ��� ���Ѵ�.
		// ��� ��������(seta�� �˷���), �󸶳� ������ �ִ���(distance�� �˷���)
		double cosResult = cos(seta) * distance;
		double sinResult = sin(seta) * distance;
		// ���� ��ǥ�� �����Ѵ�.
		x = focus.x + cosResult;
		y = focus.y - sinResult;
		// ����� �������� ��ǥ�� �����Ѵ�.
		destination.x = (LONG)x;
		destination.y = (LONG)y;
		return destination;
	}
	POINT get_point_aroundFocusR(POINT focus, double distance, double radian)
	{
		// ������ �� focus ���� distance ��ŭ ������ �ִ� ���� ���ϴ� �Լ�
		double seta = radian;		//�ﰢ�Լ��� �� seta ��(radian)
		POINT destination = { 0, };		//ã�Ƴ� ��
		// ��Ȯ�� ����� ���ؼ� double �ӽ� ������ ����Ѵ�.
		double x, y;
		// sin(seta), cos(seta)�� �Ÿ��� ���Ѵ�.
		// ��� ��������(seta�� �˷���), �󸶳� ������ �ִ���(distance�� �˷���)
		double cosResult = cos(seta) * distance;
		double sinResult = sin(seta) * distance;
		// ���� ��ǥ�� �����Ѵ�.
		x = focus.x + cosResult;
		y = focus.y - sinResult;
		// ����� �������� ��ǥ�� �����Ѵ�.
		destination.x = (LONG)x;
		destination.y = (LONG)y;
		return destination;
	}
	POINT * get_parallelogram_toRect(RECT rc)
	{
		// RECT �����κ��� ����纯���� ���� �����ϴ� �Լ�
		POINT * parallelogram = new POINT[4];
		parallelogram[0] = { rc.left, rc.top };
		parallelogram[1] = { rc.right, rc.top };
		parallelogram[2] = { rc.right, rc.bottom };
		parallelogram[3] = { rc.left, rc.bottom };

		return parallelogram;
	}
	POINT* rotate_parallelogramD(POINT * parallelogram, POINT focus, double degree)
	{
		// ����纯���� ���ϴ� ������ŭ ȸ�����ִ� �Լ�
		double seta = PI * degree / 180;	//�ﰢ�Լ��� �� seta ��(radian)
		POINT * resultParall = new POINT[4];
		// ��Ȯ�� ����� ���ؼ� double �ӽú����� ����Ѵ�.
		double x, y;
		// ��ǥȸ�� ������ ���� ��ǥ�� �����Ѵ�.
		for (int i = 0; i < 4; i++)
		{
			x = (parallelogram + i)->x;
			y = (parallelogram + i)->y;
			(resultParall + i)->x = (LONG)(
				(y - focus.y) * sin(seta) +
				(x - focus.x) * cos(seta) + focus.x
				);
			(resultParall + i)->y = (LONG)(
				(y - focus.y) * cos(seta) -
				(x - focus.x) * sin(seta) + focus.y
				);
		}
		return resultParall;
	}
	POINT* rotate_parallelogramR(POINT * parallelogram, POINT focus, double radian)
	{
		// ����纯���� ���ϴ� ������ŭ ȸ�����ִ� �Լ�
		double seta = radian;	//�ﰢ�Լ��� �� seta ��(radian)
		POINT * resultParall = new POINT[4];
		// ��Ȯ�� ����� ���ؼ� double �ӽú����� ����Ѵ�.
		double x, y;
		// ��ǥȸ�� ������ ���� ��ǥ�� �����Ѵ�.
		for (int i = 0; i < 4; i++)
		{
			x = (parallelogram + i)->x;
			y = (parallelogram + i)->y;
			(resultParall + i)->x = (LONG)(
				(y - focus.y) * sin(seta) +
				(x - focus.x) * cos(seta) + focus.x
				);
			(resultParall + i)->y = (LONG)(
				(y - focus.y) * cos(seta) -
				(x - focus.x) * sin(seta) + focus.y
				);
		}
		return resultParall;
	}
}//namespace UTIL
