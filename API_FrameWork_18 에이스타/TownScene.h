#pragma once
#include "scene.h"
#include "townMap.h"

class TownScene : public scene 
{
public:
	TownScene();
	~TownScene();

	HRESULT init();
	void release();
	void update();
	void render();

private:
	townMap * m_townMap;
	RECT playerCollision;
	image* blackScene;

	// 씬전환 넘겨주는 시간
	float addDeleyTime = 0.1f;
	float pastTime = 0.0f;
	float time = 0;

	bool isNextScene = false;
	BYTE alpha = 0;
};

