#pragma once
#include "gameNode.h"

#define OBJ_TILESIZE 80		// ������Ʈ Ÿ�� ������

#define GR_TILESIZEX 1280	// �׶��� Ÿ�� ������ x
#define GR_TILESIZEY 720	// �׶��� Ÿ�� ������ y

#define BACKTILEX 20	//����ȭ�� Ÿ�� ������ X
#define BACKTILEY 20	//����ȭ�� Ÿ�� ������ Y

#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//ȭ�� ������ �̹��� Ÿ�� ����
#define GROUNDTILEX 3
#define WALLTILEX   2

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
	TR_NULL, TR_ACID, TR_FALL, TR_START, TR_END
};

// ������Ʈ( EX: �������ʿ� ��ġ. �����̰ų� �μ����� �ϴ� �༮ ��� ��ȭ�� �� �� �ִ� ��ü )
enum OBJECT
{
	// ����  , ���� ����    ,  ��  ��   ,    �ָӴ�	     ,   	������		,  ��õ
	OBJ_NULL, OBJ_TREASUREBOX, OBJ_TREE, OBJ_POCKET, OBJ_DUNGENONDOOR, OBJ_HOTSPRING
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

// �̹��� Ÿ�� ����ü
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
	void onceTileRender();			// �ѹ��� ��� Ÿ�� ���� ( �ٴ�, �� )
	void terrainTileRender();		// ���� Ÿ�� ����
	void objectTileRender();		// ������Ʈ Ÿ�� ����

	void OnceTileIconRange();		// �ѹ��� �׷��ִ� Ÿ�� ������ ����(mapToolSetUp)�� ����

private:
	tagCurrentTile  m_currentTile;	//���� ����� Ÿ��
	tagTile			m_tiles[BACKTILEX * BACKTILEY];
	tagSampleTile	m_groundTiles[GROUNDTILEX];  // view ground Ÿ��
	tagSampleTile	m_wallTiles[WALLTILEX];		 // view 
	tagOnceTile		GR_OnceTile; // �ٴ� && ��
	tagOnceTile		WA_OnceTile;

	// ������ Ÿ��
	image* IconGround[3];
	image* IconWall[2];


	// ����ִ� Ÿ��
	image* m_DungeonTile[3];
	image* m_WallTile[2];

	// toolmenu���� �����ߴ��� 
	bool m_isGroundChoice;
	bool m_isWallChoice;

	// mapTool����
	std::string subject[3] = { "�ٴ�", "��", " ������Ʈ" };
};

