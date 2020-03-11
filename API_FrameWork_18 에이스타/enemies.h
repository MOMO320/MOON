#pragma once
#include "gameNode.h"

struct enemy
{
	RECT		_rc;
	RECT		_fightColli;

	string		name;
	int			attack;
	int			hp;
	int			speed;
};

class enemies : public gameNode
{
public:
	enemies();
	~enemies();

	HRESULT init();
	void release();
	void update();
	void render();

	void setRect(RECT _rc) { m_enemy1._rc = _rc; }
	enemy getEnemyInfo() { return m_enemy1; }
	enemy m_enemy1;

private:
	/*void enemyInit(enemy _enemy ,int _left, int _top, int _right, int _bottom , string _name, int _attack , int _hp );*/

private:



};

