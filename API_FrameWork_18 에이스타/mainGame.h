#pragma once
#include"gameNode.h"
#include"mapTool.h"
#include"startMenuScene.h"
#include"mapToolScene.h"
#include"DugeonScene.h"
#include "DugeonScene2.h"
#include "DugeonScene3.h"
#include "DungeonScene5.h"
#include"scene.h"
#include "TownScene.h"
#include "ToDungeonScene.h"
#include "firstDungeonScene.h"
#include "invenScene.h"
#include "item.h"

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
	TownScene *			c_townScene;
	ToDungeonScene *	c_toDungeonScene;
	firstDungeonScene * c_firstScene;
	invenScene *		c_invenScene;
	item *				c_item;

	MAPTOOLKIND			m_maptoolKind;

	// ´øÀü¾À
	DugeonScene*		m_DungeonScene1;
	DugeonScene2*		m_DungeonScene2;
	DugeonScene3*		m_DungeonScene3;
	DungeonScene5*		m_DungeonScene5;

	ENEMYDIRECTION		m_direction;

};
