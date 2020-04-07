#pragma once
#include "gameNode.h"
#include "dungeonMapManager.h"
#include "enemies.h"

#define BIGNUM	5000	// 초기값(F)
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

	void rectMoveDirect(enemies* _enemy , bool _aniIndexUse); //pathList의 node에 따른 렉트의 이동 방향 설정
	Direction getDirection() { return enemyDirection; } 
	vector<int> getPath() { return pathList; }
	int getFirstPath() { return fistPath; } //현재 이너미가 움직이는 타일 번호를 담은 녀석
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

	// pathCount 다른 클래스에 넘겨주기
	int fistPath;
	int currentPath;
};

