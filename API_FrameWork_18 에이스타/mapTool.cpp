#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
	:m_isGroundChoice(false), m_isWallChoice(false)
{
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	gameNode::init(true);

	IconGround[0] = IMAGEMANAGER->findImage("ic������1");
	IconGround[1] = IMAGEMANAGER->findImage("ic������2");
	IconGround[2] = IMAGEMANAGER->findImage("ic������");

	IconWall[0] = IMAGEMANAGER->findImage("ic������1");
	IconWall[1] = IMAGEMANAGER->findImage("ic������2");

	m_DungeonTile[0] = IMAGEMANAGER->findImage("������1");
	m_DungeonTile[1] = IMAGEMANAGER->findImage("������2");
	m_DungeonTile[2] = IMAGEMANAGER->findImage("������");
	m_WallTile[0] = IMAGEMANAGER->findImage("������1");
	m_WallTile[1] = IMAGEMANAGER->findImage("������2");


	mapToolSetUp();

	GR_OnceTile.m_backGroun = BR_NULL;
	WA_OnceTile.m_wall = WA_NULL;

	return S_OK;
}

void mapTool::release()
{
	IMAGEMANAGER->release();
}

void mapTool::update()
{

}

void mapTool::debugRender()  // ���ڸ� ���
{
	// ������Ʈ Ÿ�� DEBUG ����(BOX)
	for (int i = 0; i < BACKTILEX; i++)
	{
		for (int j = 0; j < BACKTILEY; j++)
		{
			AlphaRectangle(getMemDC(), m_tiles[i*BACKTILEX + j].m_rc.left,
				m_tiles[i*BACKTILEX + j].m_rc.top, m_tiles[i*BACKTILEX + j].m_rc.right, m_tiles[i*BACKTILEX + j].m_rc.bottom);
		}
	}
}

void mapTool::mapToolMenuRender()
{
	/* ���� ���� �޴� â */
	IMAGEMANAGER->render("��������", getMemDC(), WINSIZEX / 2 + 210, 50);

	printText(getMemDC(), subject[0].c_str(), "����������_ac Bold", WINSIZEX / 2 + 300, 190, 55, RGB(0, 0, 0), true, RGB(255, 0, 255));
	for (int i = 0; i < GROUNDTILEX; i++)
		IconGround[i]->render(getMemDC(), m_groundTiles[i].m_rcTile.left + (i * 15), m_groundTiles[i].m_rcTile.top);

	printText(getMemDC(), subject[1].c_str(), "����������_ac Bold", WINSIZEX / 2 + 300, 280, 55, RGB(0, 0, 0), true, RGB(255, 0, 255));
	for (int i = 0; i < WALLTILEX; i++)
		IconWall[i]->render(getMemDC(), m_wallTiles[i].m_rcTile.left + (i * 100), m_wallTiles[i].m_rcTile.top);
}


void mapTool::render()
{
	// �ٴ� �ѷ� �ֱ�
	onceTileRender();
}


void mapTool::mapToolSetUp()
{
	OnceTileIconRange();

	// << ���� �� ���� >>
	// [ m_tiles ]
	for (int i = 0; i < BACKTILEX; i++)
	{
		for (int j = 0; j < BACKTILEY; j++)
		{
			// ���ʿ� �� �ٴ� Ÿ�� ��Ʈ ��ġ ����
			SetRect(&m_tiles[i*BACKTILEX + j].m_rc,
				j*OBJ_TILESIZE,
				i*OBJ_TILESIZE,
				j*OBJ_TILESIZE + OBJ_TILESIZE,
				i*OBJ_TILESIZE + OBJ_TILESIZE);
		}
	}
	// [ m_OnceTile ]
	SetRect(&GR_OnceTile.m_rc, 0, 0, GR_TILESIZEX, GR_TILESIZEY);
	SetRect(&WA_OnceTile.m_rc, 0, 0, GR_TILESIZEX, GR_TILESIZEY);
}

void mapTool::setMap()
{
	// ������ �ٴ�Ÿ�� ���콺�� �����Ͽ� ������ currentTile�� �ѱ��
	for (int i = 0; i < GROUNDTILEX; i++)
	{
		if (PtInRect(&m_groundTiles[i].m_rcTile, m_ptMouse))
		{
			m_currentTile.x = m_groundTiles[i].m_terrainX;
			m_isGroundChoice = true;
			break;
		}
	}

	for (int i = 0; i < WALLTILEX; i++)
	{
		if (PtInRect(&m_wallTiles[i].m_rcTile, m_ptMouse))
		{
			m_currentTile.x = m_wallTiles[i].m_terrainX;
			m_isWallChoice = true;
			break;
		}
	}
	//---------------------------------------------------------------


	// ���� Ÿ��(ground)
	if (m_isGroundChoice)
	{
		for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
		{
			if (PtInRect(&GR_OnceTile.m_rc, m_ptMouse))
			{
				GR_OnceTile.m_x = m_currentTile.x;
				GR_OnceTile.m_backGroun = m_backGroundSelect(m_currentTile.x);
				GR_OnceTile.m_img = m_DungeonTile[GR_OnceTile.m_backGroun];
				m_isGroundChoice = false;
			}
			else m_isGroundChoice = false;
			InvalidateRect(m_hWnd, NULL, false);
			break;
		}
	}

	// ���� Ÿ��(wall)
	if (m_isWallChoice)
	{
		for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
		{
			if (PtInRect(&WA_OnceTile.m_rc, m_ptMouse))
			{
				WA_OnceTile.m_x = m_currentTile.x;
				WA_OnceTile.m_wall = m_wallSelect(m_currentTile.x);
				WA_OnceTile.m_img = m_WallTile[WA_OnceTile.m_wall];
				m_isWallChoice = false;
			}
			else m_isWallChoice = false;
			InvalidateRect(m_hWnd, NULL, false);
			break;
		}
	}
}


void mapTool::save()
{
}

void mapTool::load()
{
}

TERRAIN mapTool::m_terrainSelect(int frameX, int frameY)
{
	return TERRAIN();
}

OBJECT mapTool::m_objSelect(int frameX, int frameY)
{
	return OBJECT();
}

BACKGROUND mapTool::m_backGroundSelect(int imageX)
{
	if (imageX == 0)
	{
		return BR_ROOM1;
	}
	else if (imageX == 1)
	{
		return BR_ROOM2;
	}
	else if (imageX == 2)
	{
		return BR_BOSSROOM;
	}

}

WALL mapTool::m_wallSelect(int imageX)
{
	if (imageX == 0)
	{
		return WA_WALL1;
	}
	else if (imageX == 1)
	{
		return WA_WALL2;
	}
}

void mapTool::onceTileRender()
{
	if (GR_OnceTile.m_backGroun != BR_NULL)
	{
		GR_OnceTile.m_img->render(getMemDC(), 0, 0);
	}

	if (WA_OnceTile.m_wall != WA_NULL)
	{
		WA_OnceTile.m_img->render(getMemDC(), 0, 0);
	}
}

void mapTool::terrainTileRender()
{
}

void mapTool::objectTileRender()
{

}

void mapTool::OnceTileIconRange()
{
	// << ������ �� ���� >>
	for (int i = 1; i <= GROUNDTILEX; i++)
	{
		// �ٴ� ���� �̹��� ��ǥ ������ ���ش�.( left , top , right , bottom )
		SetRect(&m_groundTiles[i - 1].m_rcTile,
			((WINSIZEX / 2 + 290) - IconGround[i - 1]->getWidth()) + (i * OBJ_TILESIZE),
			250,
			((WINSIZEX / 2 + 290) - IconGround[i - 1]->getWidth()) + (i* OBJ_TILESIZE + OBJ_TILESIZE),
			250 + IconGround[i - 1]->getWidth());
		m_groundTiles[i].m_terrainX = i;
	}

	for (int i = 0; i <= WALLTILEX; i++)
	{   // �� ���� �̹��� ��ǥ ������ ���ش�.
		SetRect(&m_wallTiles[i].m_rcTile,
			((WINSIZEX / 2 + 420) - IconWall[i]->getWidth()) + (i* OBJ_TILESIZE),
			380,
			((WINSIZEX / 2 + 420) - IconWall[i]->getWidth()) + (i* OBJ_TILESIZE + OBJ_TILESIZE),
			380 + IconWall[i]->getWidth());
		m_wallTiles[i].m_terrainX = i;
	}

}
