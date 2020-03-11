#include "stdafx.h"
#include "dungeonMap1.h"

dungeonMap1::dungeonMap1()
	:m_dungeonManager(new dungeonMapManager)
{
}

dungeonMap1::~dungeonMap1()
{
	delete m_dungeonManager;
}

HRESULT dungeonMap1::init()
{
	m_dungeonManager->init();
	m_dungeonManager->addOnceLoad("onceMap1.map", m_onceMap, 2);
	m_dungeonManager->addLoad("map1.map", m_map, m_pos, BACKTILEX, BACKTILEY, m_attribute, 162, 199);
	return S_OK;
}

void dungeonMap1::release()
{
	m_dungeonManager->release();
}

void dungeonMap1::update()
{
}

void dungeonMap1::render()
{
	m_dungeonManager->mapOnceRender(m_onceMap);
	m_dungeonManager->mapTerrainRender(m_map);
	m_dungeonManager->mapObjRender(m_dungeonManager->img_mapToolTile[1], m_map, 0);
	m_dungeonManager->mapObjRender(m_dungeonManager->img_mapToolTile[2], m_map, 1);
	m_dungeonManager->mapObjRender(m_dungeonManager->img_mapToolTile[3], m_map, 2);
}
