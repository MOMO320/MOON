#pragma once
#include "gameNode.h"
#include "dungeonMap.h"

struct enemy
{
	RECT		_rc;
	RECT		_fightColli;
	RECT		_moveColli;
	RECT		_objectRc;
	RECT		_realCollRect;

	image*		m_img;
	animation*	m_ani;

	MOMOANI		m_momoAni;

	string		name;
	int			attack;
	int			hp;
	int			speed;

	int			attackCount; // 모모 몬스터 어택 카운트
};

struct AngleEnemy
{
	RECT			_rc;
	RECT			_fightColli;

	POINT			center;
	POINT			cannonEnd;

	ENEMYDIRECTION	direct;

	image*		    m_img;
	animation*	    m_ani;

	float		x, y;

	string		name;
	int			attack;
	int			hp;
	int			speed;

	int			cannon;
	float		angle;
	float		radius;
	float		gravity;
};

class enemies : public gameNode
{
public:
	enemies();
	~enemies();

	virtual HRESULT init(int x, int y) = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void render(PLAYERDIRECTION _direct , RECT _rc) = 0;
	
	virtual void enemySetRect(int _x, int _y) = 0;

	virtual void setRect(RECT _rc) = 0;
	virtual enemy getEnemyInfo() = 0;
	//virtual enemy getVectEnemy() = 0;

	void enemyMove(enemy _enemy,dungeonMap* _dunMap ,ENEMYDIRECTION _enemyDirect, int _speed);
	bool getConnect() { return isObjectConnect; }

	//virtual void setRect(RECT _rc) { m_enemy1._rc = _rc; }
	//virtual enemy getEnemyInfo() { return m_enemy1; }

	//enemy m_enemy1;

protected :
	vector<enemy> v_enemy;

	float pastTime;
	float addDeleyTime = 0.5;
	dungeonMap * m_dunMap;
	RECT rcCollision;
	int m_tileX, m_tileY;
	float _x, _y;

	bool isObjectConnect = false;
	

private:
	


};

