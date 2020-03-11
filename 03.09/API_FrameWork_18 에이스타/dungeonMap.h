#pragma once
#include "gameNode.h"

class dungeonMap : public gameNode
{
public:
	dungeonMap();
	~dungeonMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void onceLoad();
	void load();

	DWORD*		getAttribute()	{ return m_attribute; }
	tagTile*	getMap()		{ return m_map; }
	int			getPosFirst()	{ return m_pos[0]; }
	int			getPosSecond()	{ return m_pos[1]; }


private:
	void mapOnceRender();
	void mapTerrainRender();
	void mapObjRender(image* m_img, int m_tagTileNum);
	

private:
	tagCurrentTile	 m_currentTile;
	tagTile			 m_map[BACKTILEX * BACKTILEY];
	tagOnceTile	     m_onceMap[2];
	tagOBJAttribute	 m_OBJattribute[BACKTILEX * BACKTILEY];
	DWORD			 m_attribute[BACKTILEX * BACKTILEY];
	int				 m_pos[2];

	image*			 img_mapToolTile[4];
	image*			 img_groundTiles[3];
	image*			 img_wallTiles[2];

};

