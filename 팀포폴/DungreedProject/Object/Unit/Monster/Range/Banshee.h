#pragma once
#include"Object/Unit/Monster/Monster.h"
#include"Object/Missile/Note.h"
class Banshee : public Monster
{
private:
	Note * _note;
protected:
	void compareAttack_Banshees();
public:
	Banshee();
	~Banshee();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�

};

