#pragma once
#include "gameNode.h"
#include "dungeonMapManager.h"
#include "enemies.h"

#define BIGNUM	5000	// 초기값(F)
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

	HRESULT init(tagTile _map[], enemies* _enemy , int _x , int _y);
	void release();
	void update(tagTile _map[] ,RECT _playerRect, enemies* _enemy ,int _speed);
	void render(enemies* _enemy);

	void Astar();
	void enemytileSet(enemies* _enemy);
	void playerTileSet(RECT _playerRect);
	void blockType();

	void rectMoveDirect(enemies* _enemy); //pathList의 node에 따른 렉트의 이동 방향 설정



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
	int  moveX = 0;	// 원점 말고 이동한값
	int  moveY = 0;	// 원점 말고 이동한값
	int  toGoX = 0;
	int  toGoY = 0;
	int moveCount;
	
	// 시간 함수를 쓰기 위한 변수
	float deltaTime;
	float pastTime = 0.f;
	float addCharDeley = .001f;

	Direction enemyDirection;
	bool enemyMoveOk;
	int	 directionCount = 0;

};

