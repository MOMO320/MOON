#include "stdafx.h"
#include "dungeonMap.h"

dungeonMap::dungeonMap()
{
}

dungeonMap::~dungeonMap()
{
}

HRESULT dungeonMap::init()
{
	img_mapToolTile[0] = IMAGEMANAGER->findImage("산성터레인");			 // 터레인 이미지
	img_mapToolTile[1] = IMAGEMANAGER->findImage("통과되는오브젝트");		 // 오브젝트 이미지
	img_mapToolTile[2] = IMAGEMANAGER->findImage("통과안되는오브젝트1");	 //	오브젝트 이미지
	img_mapToolTile[3] = IMAGEMANAGER->findImage("통과안되는오브젝트2");	 //	오브젝트 이미지
	
	img_groundTiles[0] = IMAGEMANAGER->findImage("던전룸1");
	img_groundTiles[1] = IMAGEMANAGER->findImage("던전룸2");
	img_groundTiles[2] = IMAGEMANAGER->findImage("보스룸");

	img_wallTiles[0] = IMAGEMANAGER->findImage("던전벽1");
	img_wallTiles[1] = IMAGEMANAGER->findImage("던전벽2");
	
	load();	
	onceLoad();

	return S_OK;
}

void dungeonMap::release()
{
	IMAGEMANAGER->release();
}

void dungeonMap::update()
{
}

void dungeonMap::render()
{
	mapOnceRender();
	mapTerrainRender();
	mapObjRender(img_mapToolTile[1], 0);
	mapObjRender(img_mapToolTile[2], 1);
	mapObjRender(img_mapToolTile[3], 2);
}



void dungeonMap::onceLoad()
{
	HANDLE file;
	DWORD read;

	// 한번에 찍어내는 타일들
	file = CreateFile("onceMap.map", GENERIC_READ,1, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, m_onceMap, sizeof(tagOnceTile) * (2), &read, NULL);
}

void dungeonMap::load()
{
	HANDLE file;
	DWORD read;

	// 하나씩 찍어내는 타일들
	file = CreateFile("map.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, m_map, sizeof(tagTile)* BACKTILEX * BACKTILEY, &read, NULL);

	m_pos[0] = 162; // 플레이어 시작 좌표
	m_pos[1] = 199;	// 플레이어 나가는 좌표

	// 속성을 정의 하자
	memset(m_attribute, 0, sizeof(DWORD)*BACKTILEX * BACKTILEY);

	for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
	{
		if (m_map[i].m_obj == OBJ_DONGO)
			m_attribute[i] |= ATTR_UNMOVEABLE;

		if (m_map[i].m_obj == OBJ_TREE)
			m_attribute[i] |= ATTR_UNMOVEABLE;

		if (m_map[i].m_terrain == TR_ACID)
			m_attribute[i] |= ATTR_ACID;
	}

}

//======================================================================================
//			 map 랜더 함수 모음 
//======================================================================================
void dungeonMap::mapOnceRender()
{
	// 그라운드
	for (int i = 0; i < 3; i++)
	{
		m_onceMap[0].m_img = img_groundTiles[m_onceMap[0].m_backGroun];
		m_onceMap[0].m_img->render(getMemDC(),
		m_onceMap[0].m_rc.left,
		m_onceMap[0].m_rc.top);
	}

	// 벽
	for (int i = 0; i < 3; i++)
	{
		m_onceMap[1].m_img = img_wallTiles[m_onceMap[1].m_wall];
		m_onceMap[1].m_img->render(getMemDC(),
		m_onceMap[1].m_rc.left,
		m_onceMap[1].m_rc.top);
	}
}

void dungeonMap::mapTerrainRender()
{
	for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
	{
		img_mapToolTile[0]->frameRender(getMemDC(),
			m_map[i].m_rc.left,
			m_map[i].m_rc.top,
			m_map[i].m_terrainFrameX,
			m_map[i].m_terrainFrameY);
	}
}

void dungeonMap::mapObjRender(image * m_img, int m_tagTileNum)
{
	for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
	{
		m_img->frameRender(getMemDC(),
			m_map[i].m_rc.left,
			m_map[i].m_rc.top,
			m_map[i].m_objFrameX[m_tagTileNum],
			m_map[i].m_objFrameY[m_tagTileNum]);
	}
}
