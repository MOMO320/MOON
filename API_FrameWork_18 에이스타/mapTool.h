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
	vector<string> getTileMapName() { return vc_tileFileName; }
	vector<string> getOnceTileMapName() { return vc_onceTileFileName; }
	int m_mapToolBookCount;


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
	
	void saveFileRange();			// save ���� ����

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
	tagOnceTile		WA_OnceTile; // �ٴ� && ��

	tagOnceTile		m_onceTile[2] = { GR_OnceTile ,WA_OnceTile };	// ���� Ÿ���� �迭�� ��´�.

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
	imageButton	 m_saveButton;
	imageButton	 m_loadButton;

	// mapTool����
	std::string subject[3] = { " [ �ٴ� ] ", " [ �� ] ", " [ ������Ʈ ] " };
	std::string tileTypeName[6] = { " GROUND " , " TERRAIN " , "  OBJECT1 " ,"  OBJECT2 " , "  OBJECT3 " , "SAVE"};
	std::string saveLoad[2] = { "SAVE" , "load" };

	vector<string> vc_tileFileName;
	vector<string> vc_onceTileFileName;

	// ���� save 
	HANDLE _map[2];
	DWORD write[2];
	DWORD read;
	saveFile m_saveFile[8];

	int m_saveFileNum;
};

