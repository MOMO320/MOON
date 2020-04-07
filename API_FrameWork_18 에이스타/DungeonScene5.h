#pragma once
#include "dungeonMap4.h"
#include "gameNode.h"
#include "flea.h"
#include "aStar.h"

class DungeonScene5 : public gameNode
{
	DungeonScene5();
	~DungeonScene5();

	HRESULT init();
	void release();
	void update();
	void render();

private:
	dungeonMap4 * m_Map4;
	flea * m_flea;

	vector<flea*> v_flea;


};

