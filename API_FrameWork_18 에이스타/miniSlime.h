#pragma once
#include "enemies.h"
#define SLIMESPEED 8

class miniSlime	 : public enemies
{
public:
	miniSlime();
	~miniSlime();

	HRESULT init(int x, int y) override;
	void release() override;
	void update() override;
	void render()  override;
	void render(PLAYERDIRECTION _direct, RECT _rc) override;

	void enemySetRect(int _x, int _y) override;

	void setRect(RECT _rc) override { m_miniSlime._rc = _rc; }
	enemy getEnemyInfo() override { return m_miniSlime; };

private:
	enemy	m_miniSlime;
	bool	m_isDeath = false;
};

