#pragma once
#include "gameNode.h"

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
	 TR_ACID, TR_FALL, TR_START, TR_END ,TR_NULL,
};

// ������Ʈ( EX: �������ʿ� ��ġ. �����̰ų� �μ����� �ϴ� �༮ ��� ��ȭ�� �� �� �ִ� ��ü )
enum OBJECT
{
	//  ���� ����    ,  ��  ��   , ���������� ������Ʈ,	������	     ,   ���� �� �ִ�,
	 OBJ_TREASUREBOX, OBJ_TREE, OBJ_DONGO, OBJ_DUNGENONDOOR, OBJ_GO ,OBJ_NULL
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
	void setOnceTile();		// setMap�ȿ�����
	void setTerrain();		// setMap�ȿ�����
	void setObject(tagSampleTile _tagSample[],int _objCount, tagTile _tagTile[] , int _objSelectX ,int _objSelectY);		// setMap�ȿ�����(object) ���µ� �����Լ�

	void save();
	void load();

	TERRAIN		m_terrainSelect(int frameX, int frameY);
	OBJECT		m_objSelect(int frameX, int frameY);
	BACKGROUND 	m_backGroundSelect(int imageX);
	WALL		m_wallSelect(int imageX);

	int getMaptoolBookCount() { return m_mapToolBookCount; }
	int		 m_mapToolBookCount;

private:

	void onceTileMenuRender();		// �ѹ��� ��� Ÿ�� �޴� ����
	void onceTileRender();			// �ѹ��� ��� Ÿ�� ���� ( �ٴ�, �� )
	
	void terrainMenuRender();		// ���� Ÿ�� �޴� ����
	void terrainTileRender();		// ���� Ÿ�� ����

	void FirObjectMenuRender();		// ������Ʈ �޴� ����
	void SecObjectMenuRender();		// ������Ʈ �޴� ����
	void ThirObjectMenuRender();	// ������Ʈ �޴� ����

	void objectTileRender();			
	void SecobjectTileRender();			
	void ThirobjectTileRender();			

	void OnceTileIconRange();		// �ѹ��� �׷��ִ� Ÿ�� ������ ����(mapToolSetUp)�� ����
	void TerrainRange();			// �ͷ��� Ÿ�� �޴��� ���� ���ִ� �Լ�
	void FirObjectRange();			// ������Ʈ Ÿ�� �޴��� ���� ���ִ� �Լ�
	void SceObjectRange();			// ������Ʈ Ÿ�� �޴��� ���� ���ִ� �Լ�
	void ThirObjectRange();			// ������Ʈ Ÿ�� �޴��� ���� ���ִ� �Լ�

	void updateRect();				// ������Ʈ �Ǵ� ��Ʈ��ġ

	void setUi();					// ui��ư Ŭ�� ����ó�� 
private:
	tagCurrentTile  m_currentTile;		//���� ����� Ÿ��
	tagCurrentTile	m_currentTerrain;	// ���� ����� terrainŸ��
	tagCurrentTile  m_currentObj;
	tagTile			m_tiles[BACKTILEX * BACKTILEY];
	tagSampleTile	m_groundTiles[GROUNDTILEX];  // view ground Ÿ��
	tagSampleTile	m_wallTiles[WALLTILEX];		 // view 
	tagSampleTile	m_terrainTiles[TERRAINSIZEX * TERRAINSIZEY];
	tagSampleTile	m_objectTiles[OBJECTSIZEX * OBJECTSIZEY];
	tagSampleTile   m_SecObjectTiles[OBJECTSIZEX * OBJECTSIZEY];
	tagSampleTile   m_ThirdObjectTiles[OBJECTSIZEX * OBJECTSIZEY];
	
	tagOnceTile		GR_OnceTile; // �ٴ� && ��
	tagOnceTile		WA_OnceTile;

	RECT m_DrawImage;

	// ������ Ÿ��
	image* IconGround[3];
	image* IconWall[2];
	image* img_terrainTiles;
	image* img_objectTiles[3];

	// ����ִ� Ÿ��
	image* m_DungeonTile[3];
	image* m_WallTile[2];

	// toolmenu���� �����ߴ��� 
	bool m_isGroundChoice;
	bool m_isWallChoice;

	//������ ������ ī��Ʈ

	imageButton	 m_nextPageImg;
	imageButton	 m_beforePageImg;

	// mapTool����
	std::string subject[3] = { " [ �ٴ� ] ", " [ �� ] ", " [ ������Ʈ ] " };
	std::string tileTypeName[5] = { " GROUND " , " TERRAIN " , "  OBJECT1 " ,"  OBJECT2 " , "  OBJECT3 " };
};

