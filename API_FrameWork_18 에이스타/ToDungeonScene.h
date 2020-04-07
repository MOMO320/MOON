#pragma once
#include "scene.h"
#include "toDungeonMap.h"
#include "Ui.h"

class ToDungeonScene : public scene
{
public:
	ToDungeonScene();
	~ToDungeonScene();

	HRESULT init();
	void release();
	void update();
	void render();
	void doorAni();
	void aniStart();

private:
	toDungeonMap *  m_toDungeonMap;
	Ui *			m_ui;

	// 던전문 
	DungeonDoor forestDoor;
	bool		isInSide = false;
	bool		isFirstAni = false;
	bool		isBlack = false;
	animation*	tempAni;

	RECT			playerCollision;
	RECT			playerMoveRect;
	image *			upObject;
	bool			isStart = false;

	//블랙씬
	image *			blackScene;
	BYTE			alpha = 0;
	float			addDeley = 0.1f;
	float			pastTime = 0.0f;
	bool			isOnce = false;

};

