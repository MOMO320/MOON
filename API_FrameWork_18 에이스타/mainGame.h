#pragma once
#include"gameNode.h"
#include"mapTool.h"
#include"startMenuScene.h"
#include"mapToolScene.h"
#include"DugeonScene.h"
#include "DugeonScene2.h"
#include"scene.h"

class mainGame : public gameNode
{
private:
	RECT rc;
	RECT rc2;

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setMap();
	void aniArray();

	
private:
	mapTool*			m_mapTool;
	startMenuScene*		m_startMenuScene;
	mapToolScene*		m_mapToolScene;
	scene	*			m_scene;
	MAPTOOLKIND			m_maptoolKind;

	// ´øÀü¾À
	DugeonScene*		m_DungeonScene1;
	DugeonScene2*		m_DungeonScene2;

};
