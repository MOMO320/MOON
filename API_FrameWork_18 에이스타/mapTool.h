#pragma once
#include "gameNode.h"

#define OBJ_TILESIZE 80		// 오브젝트 타일 사이즈

#define GR_TILESIZEX 1280	// 그라운드 타일 사이즈 x
#define GR_TILESIZEY 720	// 그라운드 타일 사이즈 y

#define BACKTILEX 40	//왼쪽화면 타일 사이즈 X
#define BACKTILEY 40	//왼쪽화면 타일 사이즈 Y

#define TERRAINSIZEX 2	// 터레인 이미지 사이즈 X
#define TERRAINSIZEY 4  // 터레인 이미지 사이즈 Y

#define OBJECTSIZEX 4   // 오브젝트 이미지 사이즈 X
#define OBJECTSIZEY 4	// 오브젝트 이미지 사이즈 Y

#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//화면 오른쪽 이미지 타일 갯수
#define GROUNDTILEX 3
#define WALLTILEX   2

// 던전 바닥
enum BACKGROUND
{	//  던전1  , 던전 2 ,보스 룸  , 없을떄 
	BR_ROOM1, BR_ROOM2, BR_BOSSROOM, BR_NULL
};

// 던전 울타리
enum WALL
{
	WA_WALL1, WA_WALL2, WA_NULL
};

// 지형(ex. 밟을 떄 사운드를 나게 하거나 이동할 수 없는 지역등등)
enum TERRAIN
{
	// 없을때 , 산성   ,   떨어질때 , 던전시작위치 , 던전 나갈때 위치
	 TR_ACID, TR_FALL, TR_START, TR_END ,TR_NULL,
};

// 오브젝트( EX: 지형위쪽에 배치. 움직이거나 부서지나 하는 녀석 등등 변화를 줄 수 있는 물체 )
enum OBJECT
{
	//  보물 상자    ,  나  무   , 못지나가는 오브젝트,	던전문	     ,   밟을 수 있는,
	 OBJ_TREASUREBOX, OBJ_TREE, OBJ_DONGO, OBJ_DUNGENONDOOR, OBJ_GO ,OBJ_NULL
};

// 타일 구조체
struct tagOnceTile
{
	BACKGROUND	m_backGroun;
	WALL		m_wall;
	RECT		m_rc;
	image*      m_img;

	int			m_x;
};

// 왼쪽에 타일 구조체
struct tagTile
{
	TERRAIN m_terrain;
	OBJECT	m_obj;
	RECT	m_rc;
	image*	m_image;

	int     m_terrainFrameX;
	int     m_terrainFrameY;
	int     m_objFrameX[3];
	int     m_objFrameY[3];

	

};

// 이미지 타일 구조체
struct tagSampleTile
{
	RECT m_rcTile;

	int	 m_terrainX;
	int  m_terrainY;
	int  m_terrainFrameX;
	int  m_terrainFrameY;

	int m_objFrameX;
	int m_objFrameY;
};

struct tagCurrentTile
{
	int x;
	int y;
};

struct imageButton
{
	image* m_img;
	RECT   m_rc;
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
	int		 m_mapToolBookCount;

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
	tagOnceTile		WA_OnceTile;

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

	// mapTool제목
	std::string subject[3] = { " [ 바닥 ] ", " [ 벽 ] ", " [ 오브젝트 ] " };
	std::string tileTypeName[5] = { " GROUND " , " TERRAIN " , "  OBJECT1 " ,"  OBJECT2 " , "  OBJECT3 " };
};

