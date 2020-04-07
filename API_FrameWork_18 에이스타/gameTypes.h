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

#define SAVEFILESIZE 5	// 세이브 파일

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

enum MAPLOAD
{
	MAP1 , MAP2 , MAP3 , MAP4 , MAP5 , MAPNULL
};

// player
enum PLAYERDIRECTION
{
	PLAYER_LEFT,
	PLAYER_UP,
	PLAYER_RIGHT,
	PLAYER_DOWN
};

// enemy
enum ENEMYDIRECTION
{
	ENEMY_LEFT,
	ENEMY_UP,
	ENEMY_RIGHT,
	ENEMY_DOWN,
};

enum PLAYERSTATUS
{
	TOWN_PLAYER,
	DUNGEON_PLAYER,
};

enum ANISTATUS
{
	IDLE, WALK, ROLL, FIGHT, DIE
};
enum WEAPONEANI
{
	SWORD, BOW, SPEAR ,NONE
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

struct collisionWwall
{
	RECT rc;
	OBJECT obj; // obj_dongo;
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
	ONCETILE , TERRAINTILE , FIROBJECTTILE , SECOBJECTTILE , THIRDOBJECTTILE , SAVEMENU
};

struct tagOBJAttribute
{
	int strengh;		//내구도
};

struct THROWOBJECTINFO // object충돌처리
{
	float		m_speed;	// 날라가는 스피드
	int			m_damage;	// 공격력
	int			m_x;		//	x 위치
	int			m_y;		//  y 위치

	POINT		center;
	float		angle;
	float		radius;
	float		gravity;


	bool		m_isFire;	//발싸

	RECT		m_mainRc;	// 화살이 나갈 위치
	RECT		m_rc;		// rect 
	image*		m_img;		// 이미지
	image*      m_aniImg;	// 애니메이션 이미지
	animation * m_ani;		// 애니메이션

};
enum Select
{
	SELECT_START,
	SELECT_END,
	SELECT_BLOCK
};
enum Direction
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFTUP,
	DIRECTION_RIGHTDOWN,
	DIRECTION_LEFTDOWN,
	DIRECTION_RIGHTUP
};

enum State
{
	STATE_NONE,
	STATE_OPEN,
	STATE_CLOSE,
	STATE_PATH
};

enum MOMOANI
{
	MOMO_MOVE, MOMO_ATTACKREADY, MOMO_ATTACK, MOMO_ATTACKEND
};

struct objectBullet
{
	image* bulletImage;
	animation * ani;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float radius;
	float angle;
	float speed;
	bool fire;
	int count;

	bool connect;
};

enum DOORSTATUS
{
	DOOR_NULL, DOOR_OPEN, DOOR_CLOSE, DOOR_INTO, DOOR_KEEP
};
struct DungeonDoor
{
	image*		img;
	image*		Zimg;
	animation * ani;
	animation * Zani;
	RECT 		inToRect;
	RECT		imgRect;
	DOORSTATUS status;
};

struct itemInfo
{
	string	name;
	RECT	rc;
	image*  img;
	int		price;
	int		sellPrice;
	int		healHp;
};
