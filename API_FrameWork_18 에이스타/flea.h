#pragma once
#include "enemies.h"
#define FLEASPEED 5

class flea : public enemies
{
public:
	flea();
	~flea();

	HRESULT init(int x, int y) override;
	void release() override;
	void update() override;
	void render()  override;
	void render(PLAYERDIRECTION _direct ,RECT _rc) override;

	void enemySetRect(int _x, int _y) override;

	void setRect(RECT _rc) override { m_flea._rc = _rc; }
	enemy getEnemyInfo() override { return m_flea; }

private:
	enemy	m_flea;
	bool	m_isDeath = false;

};

