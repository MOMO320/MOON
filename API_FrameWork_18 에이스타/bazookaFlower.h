#pragma once
#include "enemies.h"
#include "objectManager.h"
#include "bazookaBall.h"


#define BAZOOKAFLOWERSPEED 3

enum ANITYPE
{
	ENEMY_IDEL , ENEMY_READY , ENEMY_ATTACK , ENEMY_RELOAD
};
class bazookaFlower : public enemies
{
public:
	bazookaFlower();
	~bazookaFlower();

	HRESULT init(int x, int y) override;
	void release() override;
	void update() override;
	void render()  override;
	void render(PLAYERDIRECTION _direct, RECT _rc);
	void update(RECT _playerRc , dungeonMap * _dungMap , int _moveRangeX , int _moveRangeY, int _width , int _height);

	void enemySetRect(int _x, int _y) override;

	void setRect(RECT _rc) override { m_bazooFlower._rc = _rc; }
	enemy getEnemyInfo() override { return m_bazooFlower; }
	void readyAni(ENEMYDIRECTION _enemyDirct);


private:
	void bazooFlowerMovetoPlayer(RECT _playerRc, float _time ,dungeonMap * _dunMap);
	void bazooFlowerAni(RECT _playerRc);
	void directObjectSet(ENEMYDIRECTION _enemyDirct);
	void moveRect();

private:
	bazookaBall * m_bazookaBall;
	objectManager * m_objManager;

	enemy m_bazooFlower;
	ENEMYDIRECTION m_direction;
	ENEMYDIRECTION m_moveDirect;
	ENEMYDIRECTION tempDirect = ENEMY_LEFT;
	ANITYPE	m_aniType;

	int   m_x = 0;
	int   m_y = 0;
	int   m_attackCount = 0;   // 3번하면 reload해줘야함
	int   m_conncetCount = 0;

	float m_pastTime =0.0f;
	bool  m_isDeath = false;
	bool  m_isObjectConnect = false;

	bool  m_isFight = false;
	bool  m_isAttackReady = false;
	bool  m_isAttackObject = false;
	bool  m_isConnect = false;
};

