#pragma once
#include "gameNode.h"
#include "dungeonMapManager.h"
#include "enemies.h"

#define BIGNUM	5000	// �ʱⰪ(F)
#define astarTileX 12
#define astarTileY 7
#define astarTileSize astarTileX * astarTileY


struct aStarTagTile 
{
	RECT rc;
	OBJECT obj;
	bool block;

	int node;

	int showState;

	int f, g, h;
};

class aStar : public gameNode
{
public:
	aStar();
	~aStar();

	HRESULT init(tagTile _map[], enemies* _enemy , int _x , int _y);
	void release();
	void update(tagTile _map[] ,RECT _playerRect, enemies* _enemy ,int _speed, bool _aniIndexUse);
	void render(enemies* _enemy);
	void enemyRender(enemies* _enemy);

	void Astar();
	void enemytileSet(enemies* _enemy);
	void playerTileSet(RECT _playerRect);
	void blockType();

	void rectMoveDirect(enemies* _enemy , bool _aniIndexUse); //pathList�� node�� ���� ��Ʈ�� �̵� ���� ����
	Direction getDirection() { return enemyDirection; } 
	vector<int> getPath() { return pathList; }
	int getFirstPath() { return fistPath; } //���� �̳ʹ̰� �����̴� Ÿ�� ��ȣ�� ���� �༮
	int getcurrentPath() { return currentPath; }

private:
	dungeonMapManager* m_dungeonMapManager;
	enemies* m_enemy;

	aStarTagTile m_astarTiles[astarTileSize];

	vector<int> openList;
	vector<int> closeList;
	vector<int> pathList;
	vector<int>::iterator iter;

	Select currentSelect;

	int startTile;
	int endTile;
	int currentTile;

	int exTile;
	
	int m_startX;
	int m_startY;

	int m_endX;
	int m_endY;

	bool isFind;
	bool noPath;
	bool startAstar;
	bool firstPath = false;
	bool firstCount = false;

	RECT temp[BACKTILEX*BACKTILEY];
	RECT enemyMoveRect; 
	int  moveX = 0;	// ���� ���� �̵��Ѱ�
	int  moveY = 0;	// ���� ���� �̵��Ѱ�
	int  toGoX = 0;
	int  toGoY = 0;
	int moveCount;
	
	// �ð� �Լ��� ���� ���� ����
	float deltaTime;
	float pastTime = 0.f;
	float addCharDeley = .001f;

	Direction enemyDirection;
	bool enemyMoveOk;
	int	 directionCount = 0;

	// pathCount �ٸ� Ŭ������ �Ѱ��ֱ�
	int fistPath;
	int currentPath;
};

