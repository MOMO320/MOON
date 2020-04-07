#pragma once
#include"singletonBase.h"
#include <stack>

class gameNode;
class sceneManager :  public singletonBase<sceneManager>
{
private:

	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	//ÇöÀç¾À
	static gameNode* _currentScene;
	//¸ñ·Ï
	mSceneList _mSceneList;
	stack<gameNode*> sceneStack;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();
	//¾ÀÃß°¡ÇÏ±â
	gameNode* addScene(string sceneName, gameNode* scene);

	HRESULT changeScene(string sceneName);

	bool scenePush(std::string sceneName , bool _isSet);
	bool scenePop();
};

