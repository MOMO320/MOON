#pragma once
#include"gameNode.h"
#include"mapTool.h"
#include"startMenuScene.h"
#include"mapToolScene.h"

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

	
private:
	mapTool*			m_mapTool;
	startMenuScene*		m_startMenuScene;
	mapToolScene*		m_mapToolScene;


};
