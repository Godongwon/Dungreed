#include "stdafx.h"
#include "effectManager.h"
#include "base/effect.h"

effectManager::effectManager()
{
}


effectManager::~effectManager()
{
}

HRESULT effectManager::init()
{
	return S_OK;
}

void effectManager::release()
{
	viTotalEffect vIter;		//��� ����Ʈ ������ ����
	miEffect mIter;				//����ƮŬ���� ����ִ� �༮

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		//����Ʈ�� ��� �ִ� ��
		for (mIter = vIter->begin(); mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				//����Ʈ Ŭ������ ���� ����
				viEffect vArriter;

				for (vArriter = mIter->second.begin(); vArriter != mIter->second.end();)
				{
					//����Ʈ Ŭ���� ������
					(*vArriter)->release();
					SAFE_DELETE(*vArriter);
					vArriter = mIter->second.erase(vArriter);
				}
			}
			else
			{
				++mIter;
			}
		}
	}
}

void effectManager::update()
{
	viTotalEffect vIter;
	miEffect mIter;

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			viEffect vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->update();
			}
		}
	}

}

void effectManager::render()
{
	viTotalEffect vIter;
	miEffect mIter;

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			viEffect vArrIter;

			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->render();
			}
		}
	}
}

void effectManager::addEffect(string effectKey, char * imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer)
{

	image* img;
	vEffect vEffectBuffer; //����Ʈ ����
	mEffect mArrEffect;		//������ ���� ����Ʈ

							//�̹������� �̹����Ŵ����� ����� �Ǿ� �ִٸ�
	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else
	{
		img = IMAGEMANAGER->addImage(effectKey, imageName, imageW, imageH, true, RGB(255, 0, 255));
	}

	//���� ũ�⸸ŭ ����Ʈ�� �Ҵ��� �ʱ�ȭ �ؼ� ���ͷ� �����.
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, frameW, frameH, fps, elapsedTime);
	}

	//���� ��� ����Ʈ ���۸� �ʿ� �ִ´�.
	mArrEffect.insert(make_pair(effectKey, vEffectBuffer));
	//�ʿ� ��� ���͸� ��Ż���Ϳ� ����.
	m_vTotalEffect.push_back(mArrEffect);


}

void effectManager::play(string effectKey, int x, int y)
{
	viTotalEffect vIter;
	miEffect mIter;

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{

			//����Ʈ Ű���� ���ؼ� ���� �ʴٸ� ���� ������ �ѱ���.
			if (!(mIter->first == effectKey))break;


			//����Ʈ Ű���� ��ġ�ϸ� ����Ʈ�� �÷��� ����.
			viEffect vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning())continue;
				(*vArrIter)->startEffect(x, y);
				return;
			}
		}
	}
}
