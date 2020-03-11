#pragma once

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

//비트연산을 하기 위해
#define ATTR_UNMOVEABLE 0x00000001
#define ATTR_POSTION	0x00000002
#define ATTR_ACID		0x00000003

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
	TR_ACID, TR_FALL, TR_START, TR_END, TR_NULL,
};

// 오브젝트( EX: 지형위쪽에 배치. 움직이거나 부서지나 하는 녀석 등등 변화를 줄 수 있는 물체 )
enum OBJECT
{
	//  보물 상자    ,  나  무   , 못지나가는 오브젝트,	던전문	     ,   밟을 수 있는,
	OBJ_TREASUREBOX, OBJ_TREE, OBJ_DONGO, OBJ_DUNGENONDOOR, OBJ_GO, OBJ_NULL
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


enum GAMEMENU
{
	GAME, MAPTOOL, END, ME_NULL
};

enum MAPTOOLKIND
{
	ONCETILE , TERRAINTILE , FIROBJECTTILE , SECOBJECTTILE , THIRDOBJECTTILE
};

struct tagOBJAttribute
{
	int strengh;		//내구도
};
