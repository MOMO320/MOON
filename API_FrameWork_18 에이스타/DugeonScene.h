#pragma once
#include "gameNode.h"
#include "dungeonMap1.h"
#include "player.h"
#include "aStar.h"

class DugeonScene : public gameNode
{
public:
	DugeonScene();
	~DugeonScene();

	HRESULT init();
	void release();
	void update();
	void render();

private:
	dungeonMap1 * m_Map1;
	player*		m_player;
	aStar*		m_aStar;
};

