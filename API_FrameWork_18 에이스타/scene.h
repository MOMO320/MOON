#pragma once
#include "gameNode.h"
#include "player.h"

class scene : public gameNode
{
public:
	scene();
	~scene();

	image * Zobject;
	HRESULT init();
	void release();
	void update();
	void sceneRender(image * img);
	void imageInit();
	void closeBlackSceneRender(bool _isAlpha , BYTE _alpha ,const char * _sceneName);
	void openBlackSceneRender(bool _isAlpha, BYTE _alpha);


protected:
	int m_count;
	image * blackScene;
	float time = 0.0f;
	float addDeley = 0.1f;
	float pastTime = 0.0f;
	BYTE alpha = 0;


};

