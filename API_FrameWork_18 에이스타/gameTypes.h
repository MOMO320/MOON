#pragma once

#define OBJ_TILESIZE 80		// ������Ʈ Ÿ�� ������

#define GR_TILESIZEX 1280	// �׶��� Ÿ�� ������ x
#define GR_TILESIZEY 720	// �׶��� Ÿ�� ������ y

#define BACKTILEX 40	//����ȭ�� Ÿ�� ������ X
#define BACKTILEY 40	//����ȭ�� Ÿ�� ������ Y

#define TERRAINSIZEX 2	// �ͷ��� �̹��� ������ X
#define TERRAINSIZEY 4  // �ͷ��� �̹��� ������ Y

#define OBJECTSIZEX 4   // ������Ʈ �̹��� ������ X
#define OBJECTSIZEY 4	// ������Ʈ �̹��� ������ Y

#define SAVEFILESIZE 5	// ���̺� ����

#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//ȭ�� ������ �̹��� Ÿ�� ����
#define GROUNDTILEX 3
#define WALLTILEX   2

//��Ʈ������ �ϱ� ����
#define ATTR_UNMOVEABLE 0x00000001
#define ATTR_POSTION	0x00000002
#define ATTR_ACID		0x00000003

// ���� �ٴ�
enum BACKGROUND
{	//  ����1  , ���� 2 ,���� ��  , ������ 
	BR_ROOM1, BR_ROOM2, BR_BOSSROOM, BR_NULL
};

// ���� ��Ÿ��
enum WALL
{
	WA_WALL1, WA_WALL2, WA_NULL
};

// ����(ex. ���� �� ���带 ���� �ϰų� �̵��� �� ���� �������)
enum TERRAIN
{
	// ������ , �꼺   ,   �������� , ����������ġ , ���� ������ ��ġ
	TR_ACID, TR_FALL, TR_START, TR_END, TR_NULL,
};

// ������Ʈ( EX: �������ʿ� ��ġ. �����̰ų� �μ����� �ϴ� �༮ ��� ��ȭ�� �� �� �ִ� ��ü )
enum OBJECT
{
	//  ���� ����    ,  ��  ��   , ���������� ������Ʈ,	������	     ,   ���� �� �ִ�,
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
// Ÿ�� ����ü
struct tagOnceTile
{
	BACKGROUND	m_backGroun;
	WALL		m_wall;
	RECT		m_rc;
	image*      m_img;

	int			m_x;
};

// ���ʿ� Ÿ�� ����ü
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

// �̹��� Ÿ�� ����ü
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
	int strengh;		//������
};

struct THROWOBJECTINFO // object�浹ó��
{
	float		m_speed;	// ���󰡴� ���ǵ�
	int			m_damage;	// ���ݷ�
	int			m_x;		//	x ��ġ
	int			m_y;		//  y ��ġ

	POINT		center;
	float		angle;
	float		radius;
	float		gravity;


	bool		m_isFire;	//�߽�

	RECT		m_mainRc;	// ȭ���� ���� ��ġ
	RECT		m_rc;		// rect 
	image*		m_img;		// �̹���
	image*      m_aniImg;	// �ִϸ��̼� �̹���
	animation * m_ani;		// �ִϸ��̼�

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
