#pragma once
#include "enemies.h"
#include "aStar.h"
#include "progressBar.h"
#define FLEASPEED 5

class flea : public enemies
{
public:
	flea();
	~flea();

	HRESULT init(int x, int y) override;
	HRESULT init(int x, int y, dungeonMap * _dunMap , enemies * _enemy) ;
	void release() override;
	void update() override;
	void update(dungeonMap * _dunMap, RECT _playerRC, enemies * _enemy, int _speed, bool _isBool, RECT _playerAttack, int _attack);
	void render()  override;
	void render(PLAYERDIRECTION _direct ,RECT _rc) override;
	void render(enemies * _enemy);

	void enemySetRect(int _x, int _y) override;

	void setRect(RECT _rc) override { m_flea._rc = _rc; }
	enemy getEnemyInfo() override { return m_flea; }
	void collision(RECT _playerRc , int _playerAttack);
	enemy	m_flea;

private:
	progressBar * m_HpBar;
	aStar * m_aStar;
	

	bool	m_isDeath = false;

};

