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
	img_mapToolTile[0] = IMAGEMANAGER->findImage("�꼺�ͷ���");			 // �ͷ��� �̹���
	img_mapToolTile[1] = IMAGEMANAGER->findImage("����Ǵ¿�����Ʈ");		 // ������Ʈ �̹���
	img_mapToolTile[2] = IMAGEMANAGER->findImage("����ȵǴ¿�����Ʈ1");	 //	������Ʈ �̹���
	img_mapToolTile[3] = IMAGEMANAGER->findImage("����ȵǴ¿�����Ʈ2");	 //	������Ʈ �̹���
	
	img_groundTiles[0] = IMAGEMANAGER->findImage("������1");
	img_groundTiles[1] = IMAGEMANAGER->findImage("������2");
	img_groundTiles[2] = IMAGEMANAGER->findImage("������");

	img_wallTiles[0] = IMAGEMANAGER->findImage("������1");
	img_wallTiles[1] = IMAGEMANAGER->findImage("������2");
	
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

	// �ѹ��� ���� Ÿ�ϵ�
	file = CreateFile("onceMap.map", GENERIC_READ,1, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, m_onceMap, sizeof(tagOnceTile) * (2), &read, NULL);
}

void dungeonMap::load()
{
	HANDLE file;
	DWORD read;

	// �ϳ��� ���� Ÿ�ϵ�
	file = CreateFile("map.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, m_map, sizeof(tagTile)* BACKTILEX * BACKTILEY, &read, NULL);

	m_pos[0] = 162; // �÷��̾� ���� ��ǥ
	m_pos[1] = 199;	// �÷��̾� ������ ��ǥ

	// �Ӽ��� ���� ����
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
//			 map ���� �Լ� ���� 
//======================================================================================
void dungeonMap::mapOnceRender()
{
	// �׶���
	for (int i = 0; i < 3; i++)
	{
		m_onceMap[0].m_img = img_groundTiles[m_onceMap[0].m_backGroun];
		m_onceMap[0].m_img->render(getMemDC(),
		m_onceMap[0].m_rc.left,
		m_onceMap[0].m_rc.top);
	}

	// ��
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
