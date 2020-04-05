#pragma once
#include "base/singletonBase.h"
#include <bitset>
using namespace std;
#define KEYMAX 256
class keyManager :  public singletonBase<keyManager>
{
private:

	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
	
public:
	keyManager();
	~keyManager();

	HRESULT init();

	void release();

	//�ѹ��� ������
	bool isOnceKeyDown(int key);
	//�����ٰ� �³�
	bool isOnceKeyUp(int key);
	//������ �ֳ�
	bool isStayKeyDown(int key);
	//���Ű��
	bool isToggleKey(int key);
};

