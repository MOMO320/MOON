#pragma once
#include "gameNode.h"

#define OBJ_TILESIZE 80		// 오브젝트 타일 사이즈

#define GR_TILESIZEX 1280	// 그라운드 타일 사이즈 x
#define GR_TILESIZEY 720	// 그라운드 타일 사이즈 y

#define BACKTILEX 20	//왼쪽화면 타일 사이즈 X
#define BACKTILEY 20	//왼쪽화면 타일 사이즈 Y

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
	TR_NULL, TR_ACID, TR_FALL, TR_START, TR_END
};

// 오브젝트( EX: 지형위쪽에 배치. 움직이거나 부서지나 하는 녀석 등등 변화를 줄 수 있는 물체 )
enum OBJECT
{
	// 없음  , 보물 상자    ,  나  무   ,    주머니	     ,   	던전문		,  온천
	OBJ_NULL, OBJ_TREASUREBOX, OBJ_TREE, OBJ_POCKET, OBJ_DUNGENONDOOR, OBJ_HOTSPRING
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



struct tagTile
{
	TERRAIN m_terrain;
	OBJECT	m_obj;
	RECT	m_rc;

	int     m_terrainFrameX;
	int     m_terrainFrameY;
	int     m_objFrameX;
	int     m_objFrameY;
};

// 이미지 타일 구조체
struct tagSampleTile
{
	RECT m_rcTile;
	int	 m_terrainX;
	int  m_terrainY;
	int  m_terrainFrameX;
	int  m_terrainFrameY;
};

struct tagCurrentTile
{
	int x;
	int y;
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

	void save();
	void load();

	TERRAIN		m_terrainSelect(int frameX, int frameY);
	OBJECT		m_objSelect(int frameX, int frameY);
	BACKGROUND 	m_backGroundSelect(int imageX);
	WALL		m_wallSelect(int imageX);

private:
	void onceTileRender();			// 한번에 까는 타일 랜더 ( 바닥, 벽 )
	void terrainTileRender();		// 지형 타일 랜더
	void objectTileRender();		// 오브젝트 타일 랜더

	void OnceTileIconRange();		// 한번에 그려주는 타일 아이콘 정렬(mapToolSetUp)에 들어갈거

private:
	tagCurrentTile  m_currentTile;	//현재 지목된 타일
	tagTile			m_tiles[BACKTILEX * BACKTILEY];
	tagSampleTile	m_groundTiles[GROUNDTILEX];  // view ground 타일
	tagSampleTile	m_wallTiles[WALLTILEX];		 // view 
	tagOnceTile		GR_OnceTile; // 바닥 && 벽
	tagOnceTile		WA_OnceTile;

	// 아이콘 타일
	image* IconGround[3];
	image* IconWall[2];


	// 깔아주는 타일
	image* m_DungeonTile[3];
	image* m_WallTile[2];

	// toolmenu에서 선택했느냐 
	bool m_isGroundChoice;
	bool m_isWallChoice;

	// mapTool제목
	std::string subject[3] = { "바닥", "벽", " 오브젝트" };
};

