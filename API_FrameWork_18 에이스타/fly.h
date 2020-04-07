#pragma once
#include "enemies.h"
#define  FLYSPEED 8

enum FLYANI
{
	FLY_WAIT , FLY_MOVEREADY , FLY_MOVE , FLY_ATTACK
};

class fly : public enemies
{
public :
	fly();
	~fly();

	HRESULT init(int x, int y) override;
	void release() override;
	void update() override;
	void render()  override;
	void render(PLAYERDIRECTION _direct, RECT _rc) override;
	
	void update(RECT _rc);

	void enemySetRect(int _x, int _y) override;

	void setRect(RECT _rc) override { m_fly._realCollRect = _rc; }
	enemy getEnemyInfo() override { return m_fly; }


	void animationStart();
	void animationCollect(RECT _rc);
	void FlyAttack(RECT _rc);
	
	std::vector<std::shared_ptr<enemy>> v_fly;

private:
	vector<enemy> v_flyMM;
	enemy m_fly;
	FLYANI m_flyAni;
	bool  m_isDeath = false;
	
	//�ִϸ��̼ǽ�
	animation * tempAni;
	bool		m_onceAni = false;
	int			m_attackRectCount = 0;

	//�÷��̾� ���� �ľ�
	bool m_isDongo = false;
	PLAYERDIRECTION m_playerDirect;

	// �ð� 
	float time;
	float addDeley = 0.08f;
	
};

