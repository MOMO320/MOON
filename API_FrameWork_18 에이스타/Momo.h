#pragma once
#include "enemies.h"
#include "dungeonMap.h"
#include "momoBall.h"
#define MOMOSPEED 5
#define MOMOBALLSPEED 5


class Momo : public enemies
{
public:
	Momo();
	~Momo();

	HRESULT init(int x, int y) override;
	void release() override;
	void update() override;
	void update(RECT _rc, Direction _astarDirect, int _currentPath, int _firstPath , dungeonMap * _dunMap);
	void render()  override;
	void render(PLAYERDIRECTION _direct, RECT _rc) override;
	
	void enemySetRect(int _x, int _y) override;

	void setRect(RECT _rc) override { m_momo._rc = _rc; }
	enemy getEnemyInfo() override { return m_momo; }
	MOMOANI getCurrentMomoAni()  { return m_Ani; }
	//int getAttackCount() { return attackCount; }

	//======================//
	//    enemyball  함수   //
	//======================//
	void ballInit();
	void ballUpdate(dungeonMap * _dunMap);
	void momoBulletFire();
	void ballRender();
	void ballCollision(dungeonMap * _dunMap, momoBall * _momoBall);



	//======================//
	//     애니메이션 함수   //
	//======================//
	void animationStart();
	void animationCollect(Direction _astarDirect);
	void animationAction(Direction _astarDirect, int _currentPath, int _firstPath);
	
private:
	momoBall *		m_ball;
	momoBall *		m_ball2;
	momoBall *		m_ball3;

	ENEMYDIRECTION	m_direct;

	enemy			m_momo;
	MOMOANI			m_Ani;
	bool			m_isDeath = false;

	// 애니메이션 
	animation *		tempAni;
	bool			m_onceAni = false;
	
	// 시간
	float			time;
	float			addDeley = 0.05f;

	// 오브젝트 위치 잡아주기
	int m_x, m_y;
	RECT lastPathRect;
	RECT playerRect;
	ENEMYDIRECTION	m_momoBallDirect;
	bool isPlayerSet = false;
	bool isOnceRect = false;

	Direction objDirect;

	bool isPathOk = false;
	bool isOnce = false;



	
	

};

