#pragma once
#include "enemies.h"
#include "objectManager.h"
#include "dungeonMap.h"
#define	MUSHROOMSPEED 10
#define PI 3.141592

class mushRoom : public enemies
{
public:
	mushRoom();
	~mushRoom();

	HRESULT init(int x, int y) override;
	void release() override;
	void update() override;
	void render()  override;
	void render(PLAYERDIRECTION _direct, RECT _rc) override;
	void update(RECT rc , dungeonMap * map);
	void render(dungeonMap * map);

	void enemySetRect(int _x, int _y) override;
	void enemyDirect(RECT rc);
	
	// ¾Þ±Û ÀÛ¾÷
	void Move(RECT rc, dungeonMap * map);
	void angleFistMoveDirect();

	void setRect(RECT _rc) override { m_mushRoom._rc = _rc; }
	enemy getEnemyInfo() override { return m_null; }
	AngleEnemy getAngleEnemy() {return m_mushRoom;}

private:
	objectManager *	m_objManager;
	enemy			m_null;
	
	AngleEnemy		m_mushRoom;
	RECT			rcCollision;
	RECT			angleRect;
	RECT			beforeRect;
	ENEMYDIRECTION	enemyBeforeDirection = ENEMY_UP;

	RECT			m_wall[4];
	float			m_x, m_y;
	int				m_tileX, m_tileY;
	bool			m_isDeath = false;

	bool			m_isOnceAni = false;
	bool			m_isTwoAni = false;
	bool			m_isFight = false;

	bool			m_onceAngle = false;
		
};

