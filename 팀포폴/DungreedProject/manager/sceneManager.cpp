#include "stdafx.h"
#include "sceneManager.h"
#include "base/gameNode.h"

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}
//������� �ΰ����� �ʱ�ȭ ����.
gameNode* sceneManager::_currentScene = nullptr;
HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	miSceneList iter = _mSceneList.begin();
	for (iter; iter != _mSceneList.end();)
	{
		//����
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene)iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	_mSceneList.clear();
}

void sceneManager::update()
{
	if (_currentScene)
	{
		_currentScene->update();
	}
}

void sceneManager::render()
{
	if (_currentScene)_currentScene->render();
}

gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{

	if(!scene)return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return nullptr;

}

HRESULT sceneManager::changeScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//��ã���� E_FAIL
	if (find == _mSceneList.end())return E_FAIL;

	//�ٲٷ��¾��� ������̶� ���Ƶ� E_FAIL
	if (find->second == _currentScene)return E_FAIL;

	//������� �Դٸ� ������ ���� �� ���� �ʱ�ȭ�ϰ� ��������.
	if (SUCCEEDED(find->second->init()))
	{
		//Ȥ�� ������ ���� �ִٸ� ������
		if (_currentScene)_currentScene->release();

		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}
