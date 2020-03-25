#include "stdafx.h"
#include "dungeonMap2.h"

dungeonMap2::dungeonMap2()
{
}

dungeonMap2::~dungeonMap2()
{
}

HRESULT dungeonMap2::init()
{
	m_dungeonManager->init();
	m_dungeonManager->addOnceLoad("onceMap2.map", m_onceMap, 2);
	m_dungeonManager->addLoad("map2.map", m_map, m_pos, BACKTILEX, BACKTILEY, m_attribute, 162, 199);
	
	wallRectSet();

	return S_OK;
}

void dungeonMap2::release()
{
	m_dungeonManager->release();
}

void dungeonMap2::update()
{
}

void dungeonMap2::render()
{
	m_dungeonManager->mapOnceRender(m_onceMap);
	m_dungeonManager->mapTerrainRender(m_map);
	m_dungeonManager->mapObjRender(m_dungeonManager->img_mapToolTile[1], m_map, 0);
	m_dungeonManager->mapObjRender(m_dungeonManager->img_mapToolTile[2], m_map, 1);
	m_dungeonManager->mapObjRender(m_dungeonManager->img_mapToolTile[3], m_map, 2);
}

void dungeonMap2::wallRectSet()
{
	m_wall[0].rc = RectMake(0, 0, WINSIZEX, 70);	// ��
	m_wall[1].rc = RectMake(0, WINSIZEY - 70, WINSIZEX, 70); //bottom
	m_wall[2].rc = RectMake(0, 0, 120, WINSIZEY);	//left
	m_wall[3].rc = RectMake(WINSIZEX - 120, 0, 120, WINSIZEY);	//right

	for (int i = 0; i < 4; i++)
	{
		m_wall[i].obj = OBJ_DONGO;
	}
}
