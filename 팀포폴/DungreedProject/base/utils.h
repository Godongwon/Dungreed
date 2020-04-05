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
	//거리
	float getDistance(float startX, float startY, float endX, float endY);
	float getAngle(float x1, float y1, float x2, float y2);
	// 한 점과 거리를 기준으로 떨어진 점 찾기
	//focus: 기준점, distance: 기준거리, degree: 기준각도
	POINT get_point_aroundFocusD(POINT focus, double distance, double degree);
	// 한 점과 거리를 기준으로 떨어진 점 찾기
	//focus: 기준점, distance: 기준거리, radian: 기준각도
	POINT get_point_aroundFocusR(POINT focus, double distance, double radian);
	// 사각형을 기준으로 평행사변형을 만들어주는 함수
	POINT * get_parallelogram_toRect(RECT rc);
	// 평행사변형을 원하는 각도만큼 회전해주는 함수
	POINT * rotate_parallelogramD(POINT * parallelogram, POINT focus, double degree);
	POINT * rotate_parallelogramR(POINT * parallelogram, POINT focus, double radian);
}