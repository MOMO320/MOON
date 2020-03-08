#pragma once
#include "gameNode.h"
#include "dungeonMap.h"
#include "player.h"

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
	dungeonMap* m_dunGeonMap;
	player*		m_player;
};

