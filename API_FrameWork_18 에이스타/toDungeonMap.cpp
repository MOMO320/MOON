#include "stdafx.h"
#include "toDungeonMap.h"

toDungeonMap::toDungeonMap()
{
}

toDungeonMap::~toDungeonMap()
{
}

HRESULT toDungeonMap::init()
{
	toDungeon = IMAGEMANAGER->findImage("town2");
	//m_intoDungeonCollision = RectMake(2500, 1390, 100, 300);
	return S_OK;
}

void toDungeonMap::release()
{
	IMAGEMANAGER->deleteAll();
}

void toDungeonMap::update()
{
}

void toDungeonMap::render()
{
	toDungeon->render(getMemDC(), 0, 0);
	//colorRectangle(getMemDC(), m_intoDungeonCollision.left, m_intoDungeonCollision.top,100,100, 0,255,0);
}
