#pragma once
#include "base/singletonBase.h"
class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction(){}

	//������ ���ڹ��������� ������ �޾ƿ´�.0~������ ����
	inline int getInt(int num)
	{
		return rand() % num;
	}
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};
