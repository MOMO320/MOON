#pragma once
#include "gameNode.h"
#include "dungeonMapManager.h"


class dungeonMap : public gameNode
{
public:
	dungeonMap();
	~dungeonMap();

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual DWORD* getAttribute() = 0;
	virtual tagTile* getMap() = 0;
	virtual int getPosFirst() = 0;
	virtual int getPosSecond() = 0;
	virtual collisionWwall * getCollisionWAll() = 0;

protected :
	dungeonMapManager* m_dungeonManager;
};

