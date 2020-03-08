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

	m_DrawImage = RectMakeCenter(0, 0,WINSIZEX + 480, WINSIZEY*2);

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

	img_terrainTiles = IMAGEMANAGER->findImage("산성터레인");
	img_objectTiles[0] = IMAGEMANAGER->findImage("통과되는오브젝트");
	img_objectTiles[1] = IMAGEMANAGER->findImage("통과안되는오브젝트1");
	img_objectTiles[2] = IMAGEMANAGER->findImage("통과안되는오브젝트2");

	m_saveButton.m_img = IMAGEMANAGER->findImage("세이브로드버튼");
	m_loadButton.m_img = IMAGEMANAGER->findImage("세이브로드버튼");

	mapToolSetUp();

	m_onceTile[0].m_backGroun = BR_NULL;
	m_onceTile[1].m_wall = WA_NULL;

	for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
	{
		m_tiles[i].m_terrain = TR_NULL;
		m_tiles[i].m_terrainFrameX = 10;
		m_tiles[i].m_terrainFrameY = 10;
		m_tiles[i].m_objFrameX[1] = 10;
		m_tiles[i].m_objFrameY[1] = 10;
		m_tiles[i].m_objFrameX[2] = 10;
		m_tiles[i].m_objFrameY[2] = 10;
		m_tiles[i].m_objFrameX[0] = 10;
		m_tiles[i].m_objFrameY[0] = 10;

		m_tiles[i].m_obj = OBJ_NULL;
	}
	m_currentTerrain.x = 10;
	m_currentTerrain.y = 10;

	updateRect();

	return S_OK;
}

void mapTool::release()
{
	IMAGEMANAGER->release();
	CAMERAMANAGER->relaese();
	CAMERAMANAGER->releaseSingleton();
}

void mapTool::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && CAMERAMANAGER->getCameraXY().x > 0)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x - 50, CAMERAMANAGER->getCameraCenter().y));
		OffsetRect(&m_DrawImage, -50, 0);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x + 50, CAMERAMANAGER->getCameraCenter().y));
		OffsetRect(&m_DrawImage, 50, 0);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && CAMERAMANAGER->getCameraXY().y > 0)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y - 50));
		OffsetRect(&m_DrawImage, 0, -50);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y + 50));
		OffsetRect(&m_DrawImage, 0, 50);
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

void mapTool::render() // 타일 이미지 뿌려주기(오른쪽)
{
	// 바닥 뿌려 주기
	onceTileRender();   
	 terrainTileRender();  
	objectTileRender();		
	 SecobjectTileRender();		
	ThirobjectTileRender();	
}

void mapTool::mapToolMenuRender()
{
	Rectangle(CAMERAMANAGER->getCameraDC(), m_DrawImage.left, m_DrawImage.top, m_DrawImage.right, m_DrawImage.bottom);
	/* 맵툴 선택 메뉴 창 */
	IMAGEMANAGER->render("맵툴메인",CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 + 210 , 50);
	m_nextPageImg.m_img->render(CAMERAMANAGER->getCameraDC(), m_nextPageImg.m_rc.left, m_nextPageImg.m_rc.top);
	m_beforePageImg.m_img->render(CAMERAMANAGER->getCameraDC(), m_beforePageImg.m_rc.left, m_beforePageImg.m_rc.top);
	
	// 세이브 로드 버튼 랜더
	m_saveButton.m_img->render(CAMERAMANAGER->getCameraDC(), m_saveButton.m_rc.left, m_saveButton.m_rc.top);
	m_loadButton.m_img->render(CAMERAMANAGER->getCameraDC(), m_loadButton.m_rc.left, m_loadButton.m_rc.top);
	
	printText(CAMERAMANAGER->getCameraDC(), saveLoad[0].c_str(), "나눔스퀘어_ac ExtraBold", m_saveButton.m_rc.left+35, m_saveButton.m_rc.top+10, 50, RGB(0, 0, 0), true, RGB(255, 0, 255));
	printText(CAMERAMANAGER->getCameraDC(), saveLoad[1].c_str(), "나눔스퀘어_ac ExtraBold", m_loadButton.m_rc.left + 35, m_loadButton.m_rc.top + 10, 50, RGB(0, 0, 0), true, RGB(255, 0, 255));

	switch (m_mapToolBookCount)
	{
	case ONCETILE:
		printText(CAMERAMANAGER->getCameraDC(), tileTypeName[m_mapToolBookCount].c_str(), "나눔스퀘어_ac ExtraBold", WINSIZEX - 315, 135, 50, RGB(0, 0, 0), true, RGB(255, 0, 255));
		onceTileMenuRender();
		break;
	case TERRAINTILE:
		printText(CAMERAMANAGER->getCameraDC(), tileTypeName[m_mapToolBookCount].c_str(), "나눔스퀘어_ac ExtraBold", WINSIZEX - 315, 135, 50, RGB(0, 0, 0), true, RGB(255, 0, 255));
		terrainMenuRender();
		//for (int i = 0; i < (TERRAINSIZEX* TERRAINSIZEY) - 2; i++)
		//{
		//	AlphaRectangle(CAMERAMANAGER->getCameraDC(), m_terrainTiles[i].m_rcTile.left,
		//		m_terrainTiles[i].m_rcTile.top,
		//		m_terrainTiles[i].m_rcTile.right,
		//		m_terrainTiles[i].m_rcTile.bottom);
		//}
		break;
	case FIROBJECTTILE:
		printText(CAMERAMANAGER->getCameraDC(), tileTypeName[m_mapToolBookCount].c_str(), "나눔스퀘어_ac ExtraBold", WINSIZEX - 330, 135, 50, RGB(0, 0, 0), true, RGB(255, 0, 255));
		FirObjectMenuRender();
		break;

	case SECOBJECTTILE:
		printText(CAMERAMANAGER->getCameraDC(), tileTypeName[m_mapToolBookCount].c_str(), "나눔스퀘어_ac ExtraBold", WINSIZEX - 330, 135, 50, RGB(0, 0, 0), true, RGB(255, 0, 255));
		SecObjectMenuRender();
		break;

	case THIRDOBJECTTILE:
		printText(CAMERAMANAGER->getCameraDC(), tileTypeName[m_mapToolBookCount].c_str(), "나눔스퀘어_ac ExtraBold", WINSIZEX - 330, 135, 50, RGB(0, 0, 0), true, RGB(255, 0, 255));
		ThirObjectMenuRender();
		break;

	default:
		break;
	}
}

void mapTool::save()
{
	_map[0] = CreateFile("map.map", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(_map[0], m_tiles, sizeof(tagTile)*(BACKTILEX * BACKTILEY), &write[0], NULL);
	CloseHandle(_map[0]);

	_map[1] = CreateFile("onceMap.map", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(_map[1], m_onceTile, sizeof(tagOnceTile)*(2), &write[1], NULL);
	CloseHandle(_map[1]);
}

void mapTool::load()
{
	ZeroMemory(&m_tiles, sizeof(tagTile)*(BACKTILEX * BACKTILEY));
	_map[0] = CreateFile("map.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(_map[0], m_tiles, sizeof(tagTile)*(BACKTILEX * BACKTILEY), &read, NULL);

	ZeroMemory(&m_onceTile, sizeof(tagOnceTile)*(2));
	_map[1] =  CreateFile("onceMap.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(_map[1], m_onceTile, sizeof(tagOnceTile)*(2), &read ,NULL);
}

//======================================================================================
//			 mapTool method 
//======================================================================================
void mapTool::mapToolSetUp()
{
	// << 오른쪽 맵 셋팅 >>
	OnceTileIconRange();
	TerrainRange();
	FirObjectRange();
	SceObjectRange();
	ThirObjectRange();

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
	SetRect(&m_onceTile[0].m_rc, 0, 0, GR_TILESIZEX, GR_TILESIZEY);
	SetRect(&m_onceTile[1].m_rc, 0, 0, GR_TILESIZEX, GR_TILESIZEY);
}

void mapTool::setMap()
{
	if (m_mapToolBookCount == ONCETILE)
	{
		setOnceTile();
	}
	else if(m_mapToolBookCount == TERRAINTILE)
	{
		setTerrain();
	}
	else if (m_mapToolBookCount == FIROBJECTTILE)
	{
		setObject(m_objectTiles,0, m_tiles, 0, 0);
	}
	else if (m_mapToolBookCount == SECOBJECTTILE)
	{
		setObject(m_SecObjectTiles,1, m_tiles, 2, 2);
	}
	else if (m_mapToolBookCount == THIRDOBJECTTILE)
	{
		setObject(m_ThirdObjectTiles,2, m_tiles, 1, 1);
	}
	setUi();
}

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

void mapTool::TerrainRange()
{						//2
	for (int x = 0; x < TERRAINSIZEX; x++)
	{						//4
		for (int y = 0; y < TERRAINSIZEY; y++)
		{
			m_terrainTiles[x*TERRAINSIZEY + y].m_terrainFrameX = y;
			m_terrainTiles[x*TERRAINSIZEY + y].m_terrainFrameY = x;

			SetRect(&m_terrainTiles[x*TERRAINSIZEY + y].m_rcTile,
				((WINSIZEX / 2 + 350) - img_terrainTiles->getFrameWidth()) + (y* OBJ_TILESIZE),
				210 + (x*img_terrainTiles->getFrameWidth()),
				((WINSIZEX / 2 + 350) - img_terrainTiles->getFrameWidth()) + (y* OBJ_TILESIZE + OBJ_TILESIZE),
				210 + (x * img_terrainTiles->getFrameWidth()) + img_terrainTiles->getFrameWidth());
		}
	}
}

void mapTool::FirObjectRange()
{
	for (int x = 0; x < OBJECTSIZEX; x++)
	{
		for (int y = 0; y < OBJECTSIZEY; y++)
		{

			m_objectTiles[x*OBJECTSIZEY + y].m_objFrameX = y;
			m_objectTiles[x*OBJECTSIZEY + y].m_objFrameY= x;

			SetRect(&m_objectTiles[x*OBJECTSIZEY + y].m_rcTile,
				((WINSIZEX / 2 + 350) - img_objectTiles[0]->getFrameWidth()) + (y* OBJ_TILESIZE),
				210 + (x*img_objectTiles[0]->getFrameWidth()),
				((WINSIZEX / 2 + 350) - img_objectTiles[0]->getFrameWidth()) + (y* OBJ_TILESIZE + OBJ_TILESIZE),
				210 + (x * img_objectTiles[0]->getFrameWidth()) + img_objectTiles[0]->getFrameWidth());
		}
	}
}

void mapTool::SceObjectRange()
{
	for (int x = 0; x < OBJECTSIZEX; x++)
	{
		for (int y = 0; y < OBJECTSIZEY; y++)
		{
			m_SecObjectTiles[x*OBJECTSIZEY + y].m_objFrameX = y;
			m_SecObjectTiles[x*OBJECTSIZEY + y].m_objFrameY = x;

			SetRect(&m_SecObjectTiles[x*OBJECTSIZEY + y].m_rcTile,
				((WINSIZEX / 2 + 350) - img_objectTiles[1]->getFrameWidth()) + (y* OBJ_TILESIZE),
				210 + (x*img_objectTiles[1]->getFrameWidth()),
				((WINSIZEX / 2 + 350) - img_objectTiles[1]->getFrameWidth()) + (y* OBJ_TILESIZE + OBJ_TILESIZE),
				210 + (x * img_objectTiles[1]->getFrameWidth()) + img_objectTiles[1]->getFrameWidth());
		}
	}
}

void mapTool::ThirObjectRange()
{
	for (int x = 0; x < OBJECTSIZEX; x++)
	{
		for (int y = 0; y < OBJECTSIZEY; y++)
		{
			m_ThirdObjectTiles[x*OBJECTSIZEY + y].m_objFrameX = y;
			m_ThirdObjectTiles[x*OBJECTSIZEY + y].m_objFrameY = x;

			SetRect(&m_ThirdObjectTiles[x*OBJECTSIZEY + y].m_rcTile,
				((WINSIZEX / 2 + 350) - img_objectTiles[2]->getFrameWidth()) + (y* OBJ_TILESIZE),
				210 + (x*img_objectTiles[2]->getFrameWidth()),
				((WINSIZEX / 2 + 350) - img_objectTiles[2]->getFrameWidth()) + (y* OBJ_TILESIZE + OBJ_TILESIZE),
				210 + (x * img_objectTiles[2]->getFrameWidth()) + img_objectTiles[2]->getFrameWidth());
		}
	}
}

//======================================================================================
//			 타일별 마우스 충돌일어나는 setMap 하위 함수
//======================================================================================
void mapTool::setOnceTile()
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
			if (PtInRect(&m_onceTile[0].m_rc, m_ptMouse))
			{
				m_onceTile[0].m_x = m_currentTile.x;
				m_onceTile[0].m_backGroun = m_backGroundSelect(m_currentTile.x);
				m_onceTile[0].m_img = m_DungeonTile[m_onceTile[0].m_backGroun];
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
			if (PtInRect(&m_onceTile[1].m_rc, m_ptMouse))
			{
				m_onceTile[1].m_x = m_currentTile.x;
				m_onceTile[1].m_wall = m_wallSelect(m_currentTile.x);
				m_onceTile[1].m_img = m_WallTile[m_onceTile[1].m_wall];
				m_isWallChoice = false;
			}
			else m_isWallChoice = false;
			InvalidateRect(m_hWnd, NULL, false);
			break;
		}
	}
}

void mapTool::setTerrain()
{	
	int mouseX = m_ptMouse.x;
	int mouseY = m_ptMouse.y;

	POINT cameraMouse;
	cameraMouse = PointMake(mouseX + CAMERAMANAGER->getCameraXY().x, mouseY + CAMERAMANAGER->getCameraXY().y);

	// 오른쪽 타일을 선택 해줄때
	for (int i = 0; i < (TERRAINSIZEX * TERRAINSIZEY)-2; ++i)
	{
		if (PtInRect(&m_terrainTiles[i].m_rcTile, m_ptMouse))
		{
			m_currentTerrain.x = m_terrainTiles[i].m_terrainFrameX;
			m_currentTerrain.y = m_terrainTiles[i].m_terrainFrameY;
			break;
		}
	}
	// 왼쪽 타일
	for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
	{
		if (PtInRect(&m_DrawImage, cameraMouse))
		{
			if (PtInRect(&m_tiles[i].m_rc, cameraMouse))
			{
				m_tiles[i].m_terrainFrameX = m_currentTerrain.x;
				m_tiles[i].m_terrainFrameY = m_currentTerrain.y;

				m_tiles[i].m_terrain = m_terrainSelect(m_tiles[i].m_terrainFrameX, m_tiles[i].m_terrainFrameY);

				InvalidateRect(m_hWnd, NULL, false);
				break;
			}
		}
	}
}

void mapTool::setObject(tagSampleTile _tagSample[], int _objCount, tagTile _tagTile[], int _objSelectX, int _objSelectY)
{
	int mouseX = m_ptMouse.x;
	int mouseY = m_ptMouse.y;

	POINT cameraMouse;
	cameraMouse = PointMake(mouseX + CAMERAMANAGER->getCameraXY().x, mouseY + CAMERAMANAGER->getCameraXY().y);

	// 오른쪽 타일을 선택할때
	for (int i = 0; i < OBJECTSIZEX * OBJECTSIZEY; ++i)
	{
		if (PtInRect(&_tagSample[i].m_rcTile, m_ptMouse))
		{
			m_currentObj.x = _tagSample[i].m_objFrameX;
			m_currentObj.y = _tagSample[i].m_objFrameY;
			break;
		}
	}
	// 왼쪽 타일
	for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
	{
		if (PtInRect(&m_DrawImage, cameraMouse))
		{
			if (PtInRect(&_tagTile[i].m_rc, cameraMouse))
			{
				_tagTile[i].m_objFrameX[_objCount] = m_currentObj.x;
				_tagTile[i].m_objFrameY[_objCount] = m_currentObj.y;

				_tagTile[i].m_obj = m_objSelect(_objSelectX, _objSelectY);

				break;
			}
		}
	}
}

void mapTool::setUi()
{
	if (PtInRect(&m_nextPageImg.m_rc, m_ptMouse))
	{
		if (m_mapToolBookCount == 4)
			m_mapToolBookCount = 0;
		else
			m_mapToolBookCount++;
	}

	if (PtInRect(&m_beforePageImg.m_rc, m_ptMouse))
	{
		if (m_mapToolBookCount == 0)
			m_mapToolBookCount = 4;
		else
			m_mapToolBookCount--;
	}

	if (PtInRect(&m_saveButton.m_rc, m_ptMouse))
	{
		save();
	}
	if (PtInRect(&m_loadButton.m_rc, m_ptMouse))
	{
		load();
	}
}

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
	img_terrainTiles->render(CAMERAMANAGER->getCameraDC(), m_terrainTiles[0].m_rcTile.left, m_terrainTiles[0].m_rcTile.top);
}

void mapTool::FirObjectMenuRender()
{
	img_objectTiles[0]->render(CAMERAMANAGER->getCameraDC(), m_objectTiles[0].m_rcTile.left, m_objectTiles[0].m_rcTile.top);
}

void mapTool::SecObjectMenuRender()
{
	img_objectTiles[1]->render(CAMERAMANAGER->getCameraDC(), m_SecObjectTiles[0].m_rcTile.left, m_SecObjectTiles[0].m_rcTile.top);
}

void mapTool::ThirObjectMenuRender()
{
	img_objectTiles[2]->render(CAMERAMANAGER->getCameraDC(), m_ThirdObjectTiles[0].m_rcTile.left, m_ThirdObjectTiles[0].m_rcTile.top);
}

//타일맵 메뉴 타일별 랜더 함수 처리 끝


//======================================================================================
//			 타일맵 타일별 이미지 랜더 함수()
//======================================================================================

void mapTool::onceTileRender()
{
	if (m_onceTile[0].m_backGroun != BR_NULL)
	{
		m_onceTile[0].m_img->render(getMemDC(), 0, 0);
	}

	if (m_onceTile[1].m_wall != WA_NULL)
	{
		m_onceTile[1].m_img->render(getMemDC(), 0, 0);
	}
}

void mapTool::terrainTileRender()
{
	for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
	{
		if (m_tiles[i].m_terrain == TR_ACID)
		{
		img_terrainTiles->frameRender(getMemDC(), m_tiles[i].m_rc.left, m_tiles[i].m_rc.top,
			m_tiles[i].m_terrainFrameX, m_tiles[i].m_terrainFrameY);
		}
	}
}

void mapTool::objectTileRender()
{
	for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
	{
		if (m_tiles[i].m_obj != OBJ_NULL )
		{
			img_objectTiles[0]->frameRender(getMemDC(), m_tiles[i].m_rc.left, m_tiles[i].m_rc.top,
				m_tiles[i].m_objFrameX[0], m_tiles[i].m_objFrameY[0]);
		}

	}
}
void mapTool::SecobjectTileRender()
{
	for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
	{
		if (m_tiles[i].m_obj != OBJ_NULL )
		{
			img_objectTiles[1]->frameRender(getMemDC(), m_tiles[i].m_rc.left, m_tiles[i].m_rc.top,
				m_tiles[i].m_objFrameX[1], m_tiles[i].m_objFrameY[1]);
		}
	}
}
void mapTool::ThirobjectTileRender()
{
	for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
	{
		if (m_tiles[i].m_obj != OBJ_NULL)
		{
			img_objectTiles[2]->frameRender(getMemDC(), m_tiles[i].m_rc.left, m_tiles[i].m_rc.top,
				m_tiles[i].m_objFrameX[2], m_tiles[i].m_objFrameY[2]);
		}
	}
}
//타일맵 타일별 이미지 랜더 함수 끝



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
	if (frameX == 10 && frameY == 10)
		return TR_NULL;

	return TR_ACID;
}

OBJECT mapTool::m_objSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0)
		return OBJ_GO;
	else if (frameX == 1 && frameY == 1)
		return OBJ_TREE;
	else if (frameX == 2 && frameY == 2)
		return OBJ_DONGO;

}
// 타일별 이미지 SELECT 하는 함수 끝

//======================================================================================
//			ui 버튼 렉트 위치()
//======================================================================================

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

	// save , load 버튼 위치 설정 
	SetRect(&m_saveButton.m_rc,
		WINSIZEX/2 + 240,
		WINSIZEY - 112,
		(WINSIZEX / 2 + 240) + m_saveButton.m_img->getWidth(),
		(WINSIZEY - 112) + m_saveButton.m_img->getHeight());

	SetRect(&m_loadButton.m_rc,
		WINSIZEX - 200,
		WINSIZEY - 112,
		(WINSIZEX - 200) + m_loadButton.m_img->getWidth(),
		(WINSIZEY - 112) + m_loadButton.m_img->getHeight());
}


