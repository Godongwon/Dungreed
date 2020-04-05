#pragma once
#include"gameNode.h"
class effect :  public gameNode
{

private:
	image * _effectImage;		//����Ʈ �̹���
	animation* _effectAni;		//����Ʈ �ִϸ��̼�

	int _x, _y;					//����Ʈ ��Ʈ�� ��ǥ
	float _elapsedTime;			//����Ʈ ����ð�(�ӵ�)
	bool _isRunning;			//������̳�?

public:
	effect();
	~effect();
	//����Ʈ �ʱ�ȭ(����Ʈ �̹���, ����Ʈ �������� ���α���, ���α��� FPS, ����Ʈ �ӵ�)
	HRESULT init(image* effectImage, int frameW, int frameH, int FPS, float elapsedTime);
	void release();
	void update();
	void render();

	//���� ���ϴ� ��ǥ�� ����Ʈ��Ʈ����
	void startEffect(int x, int y);
	//����Ʈ ���߱�
	void stopEffect();
	//����Ʈ ��������� ���°� ��������
	bool getIsRunning() { return _isRunning; }
};

