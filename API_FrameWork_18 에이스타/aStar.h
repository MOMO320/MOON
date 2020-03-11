#pragma once
#include "gameNode.h"
#include "dungeonMapManager.h"
#include "enemies.h"

#define BIGNUM	5000	// �ʱⰪ(F)
#define astarTileX 12
#define astarTileY 7
#define astarTileSize astarTileX * astarTileY

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

	HRESULT init(tagTile _map[]);
	void release();
	void update(tagTile _map[] ,RECT _playerRect);
	void render();

	void Astar();
	void enemytileSet();
	void playerTileSet(RECT _playerRect);
	void blockType();

	void rectMoveDirect(); //pathList�� node�� ���� ��Ʈ�� �̵� ���� ����



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

	RECT temp[BACKTILEX*BACKTILEY];
	RECT enemyMoveRect; 
	int  moveX = 0;
	int  moveY = 0;
	int moveCount;
	

	Direction enemyDirection;
	bool enemyMoveOk;
};

