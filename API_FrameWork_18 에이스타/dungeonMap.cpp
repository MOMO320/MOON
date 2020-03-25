#include "stdafx.h"
#include "dungeonMap.h"

dungeonMap::dungeonMap():
	m_dungeonManager(new dungeonMapManager) 
{
}

dungeonMap::~dungeonMap()
{
	delete m_dungeonManager;
}

