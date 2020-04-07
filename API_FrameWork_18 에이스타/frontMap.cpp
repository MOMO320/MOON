#include "stdafx.h"
#include "frontMap.h"

frontMap::frontMap()
{
}

frontMap::~frontMap()
{
}

HRESULT frontMap::init()
{
	m_dungeonManager->init();
	m_dungeonManager->addOnceLoad("onceMap9.map", m_onceMap, 2);
	m_dungeonManager->addLoad("map9.map", m_map, m_pos, BACKTILEX, BACKTILEY, m_attribute, 288, 48);
	
	wallRectSet();

	return S_OK;
}

void frontMap::release()
{
}

void frontMap::update()
{
}

void frontMap::render()
{
	m_dungeonManager->mapOnceRender(m_onceMap);
	m_dungeonManager->mapTerrainRender(m_map);
	m_dungeonManager->mapObjRender(m_dungeonManager->img_mapToolTile[1], m_map, 0);
	m_dungeonManager->mapObjRender(m_dungeonManager->img_mapToolTile[2], m_map, 1);
	m_dungeonManager->mapObjRender(m_dungeonManager->img_mapToolTile[3], m_map, 2);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{	// º®
		for (int i = 0; i < 4; i++)
		{
			Rectangle(getMemDC(), m_wall[i].rc.left, m_wall[i].rc.top, m_wall[i].rc.right, m_wall[i].rc.bottom);
		}
	}

}

void frontMap::wallRectSet()
{
	m_wall[0].rc = RectMake(0, 0, WINSIZEX, 70);	// À§
	m_wall[1].rc = RectMake(0, WINSIZEY - 70, WINSIZEX, 70); //bottom
	m_wall[2].rc = RectMake(0, 0, 120, WINSIZEY);	//left
	m_wall[3].rc = RectMake(WINSIZEX - 120, 0, 120, WINSIZEY);	//right

	for (int i = 0; i < 4; i++)
	{
		m_wall[i].obj = OBJ_DONGO;
	}
}
