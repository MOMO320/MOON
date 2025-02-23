#include "stdafx.h"
#include "sceneManager.h"
#include"gameNode.h"

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}
//현재씬을 널값으로 초기화 하자.
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
		//삭제
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

	//못찾으면 E_FAIL
	if (find == _mSceneList.end())return E_FAIL;

	//바꾸려는씬이 현재씬이랑 같아도 E_FAIL
	if (find->second == _currentScene)return E_FAIL;

	//여기까지 왔다면 문제가 없다 즉 씬을 초기화하고 변경하자.
	if (SUCCEEDED(find->second->init()))
	{
		//혹시 기존에 씬이 있다면 릴리즈
		if (_currentScene)_currentScene->release();

		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}

bool sceneManager::scenePush(std::string sceneName , bool _isSet)
{
	POINT pt;
	pt.x = WINSIZEX/2;
	pt.y = WINSIZEY/2;
	auto find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end())
		return false;

	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		sceneStack.push(find->second);
		_currentScene->isOnChange();
		
		if (_isSet)
		{
		   CAMERAMANAGER->setCameraCenter(pt);
		}
		return true;
	}
}

bool sceneManager::scenePop()
{
	if (sceneStack.size() > 1)
	{
		sceneStack.top()->release();
		sceneStack.pop();
		_currentScene = sceneStack.top();
		_currentScene->isOnChange();
	}
	return true;
}