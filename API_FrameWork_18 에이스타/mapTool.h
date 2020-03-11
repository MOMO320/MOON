#pragma once
#include "gameNode.h"

#define saveBoxX 300
#define saveBoxY 50
struct saveFile
{
	RECT rc;
	string name;
	int count;
};


class mapTool : public gameNode
{
public:
	mapTool();
	~mapTool();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;
	void debugRender();
	void mapToolMenuRender();

	void mapToolSetUp();
	void setMap();
	void setOnceTile();		// setMap안에들어갈것
	void setTerrain();		// setMap안에들어갈것
	void setObject(tagSampleTile _tagSample[],int _objCount, tagTile _tagTile[] , int _objSelectX ,int _objSelectY);		// setMap안에들어갈것(object) 형태들 담을함수

	void save();
	void load();

	TERRAIN		m_terrainSelect(int frameX, int frameY);
	OBJECT		m_objSelect(int frameX, int frameY);
	BACKGROUND 	m_backGroundSelect(int imageX);
	WALL		m_wallSelect(int imageX);

	int getMaptoolBookCount() { return m_mapToolBookCount; }
	vector<string> getTileMapName() { return vc_tileFileName; }
	vector<string> getOnceTileMapName() { return vc_onceTileFileName; }
	int m_mapToolBookCount;


private:

	void onceTileMenuRender();		// 한번에 까는 타일 메뉴 렌더
	void onceTileRender();			// 한번에 까는 타일 랜더 ( 바닥, 벽 )
	
	void terrainMenuRender();		// 지형 타일 메뉴 렌더
	void terrainTileRender();		// 지형 타일 랜더

	void FirObjectMenuRender();		// 오브젝트 메뉴 랜더
	void SecObjectMenuRender();		// 오브젝트 메뉴 랜더
	void ThirObjectMenuRender();	// 오브젝트 메뉴 랜더

	void objectTileRender();			
	void SecobjectTileRender();			
	void ThirobjectTileRender();			

	void OnceTileIconRange();		// 한번에 그려주는 타일 아이콘 정렬(mapToolSetUp)에 들어갈거
	void TerrainRange();			// 터레인 타일 메뉴에 정렬 해주는 함수
	void FirObjectRange();			// 오브젝트 타일 메뉴에 정렬 해주는 함수
	void SceObjectRange();			// 오브젝트 타일 메뉴에 정렬 해주는 함수
	void ThirObjectRange();			// 오브젝트 타일 메뉴에 정렬 해주는 함수
	
	void saveFileRange();			// save 파일 정렬

	void updateRect();				// 업데이트 되는 렉트위치

	void setUi();					// ui버튼 클릭 연산처리 
	

private:
	tagCurrentTile  m_currentTile;		//현재 지목된 타일
	tagCurrentTile	m_currentTerrain;	// 현재 지목된 terrain타일
	tagCurrentTile  m_currentObj;
	tagTile			m_tiles[BACKTILEX * BACKTILEY];
	tagSampleTile	m_groundTiles[GROUNDTILEX];  // view ground 타일
	tagSampleTile	m_wallTiles[WALLTILEX];		 // view 
	tagSampleTile	m_terrainTiles[TERRAINSIZEX * TERRAINSIZEY];
	tagSampleTile	m_objectTiles[OBJECTSIZEX * OBJECTSIZEY];
	tagSampleTile   m_SecObjectTiles[OBJECTSIZEX * OBJECTSIZEY];
	tagSampleTile   m_ThirdObjectTiles[OBJECTSIZEX * OBJECTSIZEY];
	
	tagOnceTile		GR_OnceTile; // 바닥 && 벽
	tagOnceTile		WA_OnceTile; // 바닥 && 벽

	tagOnceTile		m_onceTile[2] = { GR_OnceTile ,WA_OnceTile };	// 원스 타일을 배열로 담는다.

	RECT m_DrawImage;

	// 아이콘 타일
	image* IconGround[3];
	image* IconWall[2];
	image* img_terrainTiles;
	image* img_objectTiles[3];

	// 깔아주는 타일
	image* m_DungeonTile[3];
	image* m_WallTile[2];

	// toolmenu에서 선택했느냐 
	bool m_isGroundChoice;
	bool m_isWallChoice;

	//맵툴북 페이지 카운트
	imageButton	 m_nextPageImg;
	imageButton	 m_beforePageImg;
	imageButton	 m_saveButton;
	imageButton	 m_loadButton;

	// mapTool제목
	std::string subject[3] = { " [ 바닥 ] ", " [ 벽 ] ", " [ 오브젝트 ] " };
	std::string tileTypeName[6] = { " GROUND " , " TERRAIN " , "  OBJECT1 " ,"  OBJECT2 " , "  OBJECT3 " , "SAVE"};
	std::string saveLoad[2] = { "SAVE" , "load" };

	vector<string> vc_tileFileName;
	vector<string> vc_onceTileFileName;

	// 파일 save 
	HANDLE _map[2];
	DWORD write[2];
	DWORD read;
	saveFile m_saveFile[8];

	int m_saveFileNum;
};

