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
	int strengh;		//������
};
