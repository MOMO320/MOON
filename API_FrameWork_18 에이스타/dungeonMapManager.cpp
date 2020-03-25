#include "stdafx.h"
#include "dungeonMapManager.h"

dungeonMapManager::dungeonMapManager()
{
}

dungeonMapManager::~dungeonMapManager()
{
}

HRESULT dungeonMapManager::init()
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

	return S_OK;
}

void dungeonMapManager::release()
{
	IMAGEMANAGER->deleteAll();
}

void dungeonMapManager::update()
{
}

void dungeonMapManager::render()
{
}

void dungeonMapManager::addOnceLoad(const char* _fileName, tagOnceTile _OncetileName[2], int _fileSize)
{
	HANDLE file;
	DWORD read;
	int size;

	// 한번에 찍어내는 타일들
	file = CreateFile(_fileName, GENERIC_READ,1, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _OncetileName, sizeof(tagOnceTile) * (_fileSize), &read, NULL);
}

void dungeonMapManager::addLoad(const char* _fileName, tagTile  _tileName[BACKTILEX * BACKTILEY], int _pos[], int _sizeX, int _sizeY, DWORD _attribute[], int _startPos, int _endPos)
{
	HANDLE file;
	DWORD read;
	std::vector<tagTile*> temp;

	// 하나씩 찍어내는 타일들
	file = CreateFile(_fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tileName, sizeof(tagTile)* _sizeX * _sizeY, &read, NULL);

	_pos[0] = _startPos; // 플레이어 시작 좌표
	_pos[1] = _endPos;

	// 속성을 정의 하자
	memset(_attribute, 0, sizeof(DWORD)*_sizeX * _sizeY);

	for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
	{
		if (_tileName[i].m_obj == OBJ_DONGO)
			_attribute[i] |= ATTR_UNMOVEABLE;

		if (_tileName[i].m_obj == OBJ_TREE)
			_attribute[i] |= ATTR_UNMOVEABLE;

		if (_tileName[i].m_terrain == TR_ACID)
			_attribute[i] |= ATTR_ACID;
	}
	temp.push_back(&_tileName[BACKTILEX * BACKTILEY]);
}

//======================================================================================
//			 map 랜더 함수 모음 
//======================================================================================
void dungeonMapManager::mapOnceRender(tagOnceTile _OncetileName[])
{
	// 그라운드
	//for (int i = 0; i < 3; i++)
	//{
		_OncetileName[0].m_img = img_groundTiles[_OncetileName[0].m_backGroun];
		_OncetileName[0].m_img->render(getMemDC(),
		_OncetileName[0].m_rc.left,
		_OncetileName[0].m_rc.top);
	//}

	// 벽
	//for (int i = 0; i < 3; i++)
	//{
		_OncetileName[1].m_img = img_wallTiles[_OncetileName[1].m_wall];
		_OncetileName[1].m_img->render(getMemDC(),
		_OncetileName[1].m_rc.left,
		_OncetileName[1].m_rc.top);
	//}
}

void dungeonMapManager::mapTerrainRender(tagTile _tileName[])
{
	for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
	{
		if (_tileName[i].m_terrainFrameX == 10 && _tileName[i].m_terrainFrameY == 10)
			continue;
		img_mapToolTile[0]->frameRender(getMemDC(),
			_tileName[i].m_rc.left,
			_tileName[i].m_rc.top,
			_tileName[i].m_terrainFrameX,
			_tileName[i].m_terrainFrameY);
	}
}

void dungeonMapManager::mapObjRender(image * m_img, tagTile _tileName[] , int m_tagTileNum)
{
	for (int i = 0; i < BACKTILEX * BACKTILEY; i++)
	{
		if (_tileName[i].m_objFrameX[m_tagTileNum] == 10 && _tileName[i].m_objFrameY[m_tagTileNum] == 10)
			continue;

		m_img->frameRender(getMemDC(),
			_tileName[i].m_rc.left,
			_tileName[i].m_rc.top,
			_tileName[i].m_objFrameX[m_tagTileNum],
			_tileName[i].m_objFrameY[m_tagTileNum]);
	}
}
