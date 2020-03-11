#pragma once
#include "gameNode.h"
#include "dungeonMapManager.h"

class dungeonMap1 : public gameNode
{
public:
	dungeonMap1();
	~dungeonMap1();

	HRESULT init();
	void release();
	void update();
	void render();

	DWORD*		getAttribute() { return m_attribute; }
	tagTile*	getMap() { return m_map; }
	int			getPosFirst() { return m_pos[0]; }
	int			getPosSecond() { return m_pos[1]; }

	tagTile			   m_map[BACKTILEX * BACKTILEY];

private:
	dungeonMapManager* m_dungeonManager;

	DWORD			   m_attribute[BACKTILEX * BACKTILEY];
	tagOnceTile	       m_onceMap[2];
	int				   m_pos[2];

};

