#pragma once
#include "frontMap.h"

class firstDungeonScene : public gameNode
{
public:
	firstDungeonScene();
	~firstDungeonScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void doorAni(DungeonDoor _door);
	void aniStart(DungeonDoor _door);
	void rectRender();

private:
	frontMap * m_firstMap;

	image * subjectImg;
	animation * subjectAni;

	// 던전문
	DungeonDoor forestDoorDown;
	DungeonDoor forestDoorUp;
	animation*	tempAni;


	//블랙씬
	image *			blackScene;
	BYTE			alpha = 0;
	float			addDeley = 0.1f;
	float			pastTime = 0.0f;
};

