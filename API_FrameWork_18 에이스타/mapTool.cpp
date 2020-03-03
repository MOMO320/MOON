#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
	:m_isGroundChoice(false), m_isWallChoice(false), m_mapToolBookCount(0)
{
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	gameNode::init(true);

	IconGround[0] = IMAGEMANAGER->findImage("ic던전룸1");
	IconGround[1] = IMAGEMANAGER->findImage("ic던전룸2");
	IconGround[2] = IMAGEMANAGER->findImage("ic보스룸");

	IconWall[0] = IMAGEMANAGER->findImage("ic던전벽1");
	IconWall[1] = IMAGEMANAGER->findImage("ic던전벽2");

	m_DungeonTile[0] = IMAGEMANAGER->findImage("던전룸1");
	m_DungeonTile[1] = IMAGEMANAGER->findImage("던전룸2");
	m_DungeonTile[2] = IMAGEMANAGER->findImage("보스룸");
	m_WallTile[0] = IMAGEMANAGER->findImage("던전벽1");
	m_WallTile[1] = IMAGEMANAGER->findImage("던전벽2");

	m_nextPageImg.m_img = IMAGEMANAGER->findImage("다음페이지");
	m_beforePageImg.m_img = IMAGEMANAGER->findImage("이전페이지");

	mapToolSetUp();

	GR_OnceTile.m_backGroun = BR_NULL;
	WA_OnceTile.m_wall = WA_NULL;

	updateRect();

	return S_OK;
}

void mapTool::release()
{
	IMAGEMANAGER->release();
}

void mapTool::update()
{
	

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && CAMERAMANAGER->getCameraXY().x > 0)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x - 50, CAMERAMANAGER->getCameraCenter().y));
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x + 50, CAMERAMANAGER->getCameraCenter().y));
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && CAMERAMANAGER->getCameraXY().y > 0)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y - 50));
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y + 50));

	}
}

void mapTool::debugRender()  // 상자만 출력
{
	// 오브젝트 타일 DEBUG 랜더(BOX)
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
	/* 맵툴 선택 메뉴 창 */
	IMAGEMANAGER->render("맵툴메인",CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 + 210 , 50);
	m_nextPageImg.m_img->render(CAMERAMANAGER->getCameraDC(), m_nextPageImg.m_rc.left, m_nextPageImg.m_rc.top);
	m_beforePageImg.m_img->render(CAMERAMANAGER->getCameraDC(), m_beforePageImg.m_rc.left, m_beforePageImg.m_rc.top);
	
	switch (m_mapToolBookCount)
	{
	case ONCETILE:
		printText(CAMERAMANAGER->getCameraDC(), tileTypeName[m_mapToolBookCount].c_str(), "나눔스퀘어_ac ExtraBold", WINSIZEX - 315, 135, 50, RGB(0, 0, 0), true, RGB(255, 0, 255));
		onceTileMenuRender();
		break;
	case TERRAINTILE:
		printText(CAMERAMANAGER->getCameraDC(), tileTypeName[m_mapToolBookCount].c_str(), "나눔스퀘어_ac ExtraBold", WINSIZEX - 315, 135, 50, RGB(0, 0, 0), true, RGB(255, 0, 255));
		break;
	case OBJECTTILE:
		printText(CAMERAMANAGER->getCameraDC(), tileTypeName[m_mapToolBookCount].c_str(), "나눔스퀘어_ac ExtraBold", WINSIZEX - 315, 135, 50, RGB(0, 0, 0), true, RGB(255, 0, 255));
		break;
	default:
		break;
	}

	
}


void mapTool::render() // 타일 이미지 뿌려주기(오른쪽)
{
	// 바닥 뿌려 주기
	onceTileRender();

}


void mapTool::mapToolSetUp()
{
	OnceTileIconRange();

	// << 왼쪽 맵 셋팅 >>
	// [ m_tiles ]
	for (int i = 0; i < BACKTILEX; i++)
	{
		for (int j = 0; j < BACKTILEY; j++)
		{
			// 왼쪽에 깔 바닥 타일 렉트 위치 지정
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
	// 오른쪽 바닥타일 마우스로 선택하여 데이터 currentTile에 넘기기
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


	// 왼쪽 타일(ground)
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

	// 왼쪽 타일(wall)
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
	setUi();
}

void mapTool::setUi()
{
	if (PtInRect(&m_nextPageImg.m_rc, m_ptMouse))
	{
		if (m_mapToolBookCount == 2)
			m_mapToolBookCount = 0;
		else
			m_mapToolBookCount++;
	}

	if (PtInRect(&m_beforePageImg.m_rc, m_ptMouse))
	{
		if (m_mapToolBookCount == 0)
			m_mapToolBookCount = 2;
		else
			m_mapToolBookCount--;
	}

}

void mapTool::save()
{
}

void mapTool::load()
{
}
//======================================================================================
//			 타일별 이미지 SELECT 하는 함수()
//======================================================================================
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

TERRAIN mapTool::m_terrainSelect(int frameX, int frameY)
{
	return TERRAIN();
}

OBJECT mapTool::m_objSelect(int frameX, int frameY)
{
	return OBJECT();
}
// 타일별 이미지 SELECT 하는 함수 끝

//======================================================================================
//			 타일맵 메뉴 타일별 랜더 함수()
//======================================================================================

void mapTool::onceTileMenuRender()
{
	printText(CAMERAMANAGER->getCameraDC(), subject[0].c_str(), "나눔스퀘어_ac ExtraBold", WINSIZEX - 270, 210, 40, RGB(0, 0, 0), true, RGB(255, 0, 255));
	for (int i = 0; i < GROUNDTILEX; i++)
		IconGround[i]->render(CAMERAMANAGER->getCameraDC(), m_groundTiles[i].m_rcTile.left + (i * 15), m_groundTiles[i].m_rcTile.top);

	printText(CAMERAMANAGER->getCameraDC(), subject[1].c_str(), "나눔스퀘어_ac ExtraBold", WINSIZEX - 250, 360, 40, RGB(0, 0, 0), true, RGB(255, 0, 255));
	for (int i = 0; i < WALLTILEX; i++)
		IconWall[i]->render(CAMERAMANAGER->getCameraDC(), m_wallTiles[i].m_rcTile.left + (i * 100), m_wallTiles[i].m_rcTile.top);
}

void mapTool::terrainMenuRender()
{
}

void mapTool::objectMenuRender()
{

}
//타일맵 메뉴 타일별 랜더 함수 처리 끝


//======================================================================================
//			 타일맵 타일별 이미지 랜더 함수()
//======================================================================================

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
//타일맵 타일별 이미지 랜더 함수 끝

//======================================================================================
//			타일별 정렬 함수()
//======================================================================================
void mapTool::OnceTileIconRange()
{
	// << 오른쪽 맵 셋팅 >>
	for (int i = 1; i <= GROUNDTILEX; i++)
	{
		// 바닥 맵툴 이미지 좌표 설정을 해준다.( left , top , right , bottom )
		SetRect(&m_groundTiles[i - 1].m_rcTile,
			((WINSIZEX / 2 + 290) - IconGround[i - 1]->getWidth()) + (i * OBJ_TILESIZE),
			270,
			((WINSIZEX / 2 + 290) - IconGround[i - 1]->getWidth()) + (i* OBJ_TILESIZE + OBJ_TILESIZE),
			270 + IconGround[i - 1]->getWidth());
		m_groundTiles[i].m_terrainX = i;
	}

	for (int i = 0; i <= WALLTILEX; i++)
	{   // 벽 맵툴 이미지 좌표 설정을 해준다.
		SetRect(&m_wallTiles[i].m_rcTile,
			((WINSIZEX / 2 + 420) - IconWall[i]->getWidth()) + (i* OBJ_TILESIZE),
			410,
			((WINSIZEX / 2 + 420) - IconWall[i]->getWidth()) + (i* OBJ_TILESIZE + OBJ_TILESIZE),
			410 + IconWall[i]->getWidth());
		m_wallTiles[i].m_terrainX = i;
	}

}

void mapTool::updateRect() // 업데이트 되는 렉트위치(ui버튼)
{
	SetRect(&m_nextPageImg.m_rc,
		WINSIZEX - 90,
		125,
		(WINSIZEX - 90) + m_nextPageImg.m_img->getWidth(),
		125 + m_nextPageImg.m_img->getHeight()
		);
	
	SetRect(&m_beforePageImg.m_rc,
		WINSIZEX / 2 + 250,
		125,
		(WINSIZEX / 2 + 250) + m_beforePageImg.m_img->getWidth(),
		125 + m_beforePageImg.m_img->getHeight()
	);
}


