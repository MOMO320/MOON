#pragma once
#include "gameNode.h"



class dungeonMapManager : public gameNode
{
public:
	dungeonMapManager();
	~dungeonMapManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addOnceLoad(const char*_fileName ,tagOnceTile  _OncetileName[2],  int _fileSize);
	void addLoad(const char* _fileName , tagTile _tileName[BACKTILEX * BACKTILEY], int _pos[] , int _sizeX , int _sizeY, DWORD _attribute[], int _startPos , int _endPos);

	void mapOnceRender(tagOnceTile _OncetileName[]);
	void mapTerrainRender(tagTile _tileName[]);
	void mapObjRender(image* m_img, tagTile _tileName[], int m_tagTileNum);

public:
	map<string, tagTile> map_dungeonTile;
	map<string, tagOnceTile> map_dungeonOnceTile;

	image*			 img_mapToolTile[4];
	image*			 img_groundTiles[3];
	image*			 img_wallTiles[2];

private:
	//tagCurrentTile			 m_currentTile;
	//vector<tagTile>		     m_map;
	//vector<tagOnceTile>		 m_onceMap[2];
	//tagOBJAttribute		     m_OBJattribute[BACKTILEX * BACKTILEY];
	//DWORD				     m_attribute[BACKTILEX * BACKTILEY];
	//int					     m_pos[2];




};

