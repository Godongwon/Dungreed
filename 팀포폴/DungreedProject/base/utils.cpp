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
		// 임의의 점 focus 에서 distance 만큼 떨어져 있는 점을 구하는 함수
		double seta = PI * degree / 180;	//삼각함수에 쓸 seta 값(radian)
		POINT destination = { 0, };		//찾아낸 점
		// 정확한 계산을 위해서 double 임시 변수를 사용한다.
		double x, y;
		// sin(seta), cos(seta)를 거리에 곱한다.
		// 어느 방향으로(seta가 알려줌), 얼마나 떨어져 있는지(distance가 알려줌)
		double cosResult = cos(seta) * distance;
		double sinResult = sin(seta) * distance;
		// 기준 좌표에 적용한다.
		x = focus.x + cosResult;
		y = focus.y - sinResult;
		// 결과를 바탕으로 좌표에 대입한다.
		destination.x = (LONG)x;
		destination.y = (LONG)y;
		return destination;
	}
	POINT get_point_aroundFocusR(POINT focus, double distance, double radian)
	{
		// 임의의 점 focus 에서 distance 만큼 떨어져 있는 점을 구하는 함수
		double seta = radian;		//삼각함수에 쓸 seta 값(radian)
		POINT destination = { 0, };		//찾아낸 점
		// 정확한 계산을 위해서 double 임시 변수를 사용한다.
		double x, y;
		// sin(seta), cos(seta)를 거리에 곱한다.
		// 어느 방향으로(seta가 알려줌), 얼마나 떨어져 있는지(distance가 알려줌)
		double cosResult = cos(seta) * distance;
		double sinResult = sin(seta) * distance;
		// 기준 좌표에 적용한다.
		x = focus.x + cosResult;
		y = focus.y - sinResult;
		// 결과를 바탕으로 좌표에 대입한다.
		destination.x = (LONG)x;
		destination.y = (LONG)y;
		return destination;
	}
	POINT * get_parallelogram_toRect(RECT rc)
	{
		// RECT 정보로부터 평행사변형을 만들어서 리턴하는 함수
		POINT * parallelogram = new POINT[4];
		parallelogram[0] = { rc.left, rc.top };
		parallelogram[1] = { rc.right, rc.top };
		parallelogram[2] = { rc.right, rc.bottom };
		parallelogram[3] = { rc.left, rc.bottom };

		return parallelogram;
	}
	POINT* rotate_parallelogramD(POINT * parallelogram, POINT focus, double degree)
	{
		// 평행사변형을 원하는 각도만큼 회전해주는 함수
		double seta = PI * degree / 180;	//삼각함수에 쓸 seta 값(radian)
		POINT * resultParall = new POINT[4];
		// 정확한 결과를 위해서 double 임시변수를 사용한다.
		double x, y;
		// 좌표회전 공식을 현재 좌표에 대입한다.
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
		// 평행사변형을 원하는 각도만큼 회전해주는 함수
		double seta = radian;	//삼각함수에 쓸 seta 값(radian)
		POINT * resultParall = new POINT[4];
		// 정확한 결과를 위해서 double 임시변수를 사용한다.
		double x, y;
		// 좌표회전 공식을 현재 좌표에 대입한다.
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
