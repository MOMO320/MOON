#include "stdafx.h"
#include "fly.h"

fly::fly()
{
}

fly::~fly()
{
}

HRESULT fly::init(int x, int y)
{
	m_fly.m_img = IMAGEMANAGER->findImage("flyEnemy");
	m_fly.m_ani = ANIMATIONMANAGER->findAnimation("fly_Wait");

	tempAni = m_fly.m_ani; // 애니메이션 초기 설정 (비교 해줄 tempAni)

	m_fly.name		= "날파리";
	m_fly.attack	= 8;
	m_fly.hp		= 20;
	m_fly.speed = FLYSPEED;

	m_fly.m_ani->start();

	m_fly._rc = RectMakeCenter(x, y, 60,60);

	enemySetRect(x, y);
	
	pastTime = 0;
	m_flyAni = FLY_WAIT;

	v_enemy.push_back(m_fly);
	
	return S_OK;
}

void fly::release()
{
	IMAGEMANAGER->deleteAll();
	ANIMATIONMANAGER->deleteALL();
}

void fly::update()
{
	if (m_fly.hp <= 0)
	{
		m_isDeath = true;
		m_fly.m_img = IMAGEMANAGER->findImage("flyDeath");
	}
}

void fly::update(RECT _rc)
{
	time = TIMEMANAGER->getElapsedTime();

	if (_rc.left <= m_fly._rc.left)
	{
		m_playerDirect = PLAYER_LEFT;
	}
	else if (m_fly._rc.right <= _rc.right)
	{
		m_playerDirect = PLAYER_RIGHT;
	}

	FlyAttack(_rc);
	animationCollect(_rc);
	animationStart();
	enemySetRect(0, 0); // 0은 아무 의미없음 
}


void fly::render()
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		colorRectangle(getMemDC(), m_fly._objectRc.left, m_fly._objectRc.top, 40,40 , 0,255,0);
		AlphaRectangle(getMemDC(), m_fly._rc.left, m_fly._rc.top, m_fly._rc.right, m_fly._rc.bottom);
	}
	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		colorRectangle(getMemDC(), m_fly._fightColli.left, m_fly._fightColli.top, 800, 800,0,0,255);
		colorRectangle(getMemDC(), m_fly._realCollRect.left, m_fly._realCollRect.top, m_fly.m_img->getFrameWidth(), m_fly.m_img->getFrameHeight() , 255,0,0);
	}

	m_fly.m_img->aniRender(getMemDC(), m_fly._realCollRect.left+ 60, m_fly._realCollRect.top, m_fly.m_ani);
}

void fly::render(PLAYERDIRECTION _direct, RECT _rc)
{
}
//=======================================================================

//=======================//
//    애너미 공격 설정    //
//=======================//

void fly::FlyAttack(RECT _rc)
{
	RECT temp;

	pastTime += time;

	if (IntersectRect(&temp, &m_fly._fightColli, &_rc))
	{
		// 좌 우 방향 //
		if (m_fly._rc.left - _rc.left > FLYSPEED && !m_isDongo) // 플레이어가 왼쪽이라는 전제
		{
			if (m_fly._rc.top - (_rc.top - 60) > 10)	// 플레이어가 위쪽에 있단 전제
			{
				if (addDeley < pastTime)
				{
					pastTime = 0;
					OffsetRect(&m_fly._rc, -FLYSPEED, -FLYSPEED);
				}
			}
			if (_rc.bottom - m_fly._rc.bottom > 100)
			{
				if (addDeley < pastTime)
				{
					pastTime = 0;
					OffsetRect(&m_fly._rc, -FLYSPEED, FLYSPEED);
				}
			}
			if (addDeley < pastTime)
			{
				pastTime = 0;
				OffsetRect(&m_fly._rc, -FLYSPEED, 0);
			}
		}
		else if (m_playerDirect == PLAYER_LEFT && m_fly._rc.left - _rc.left <= 0) m_isDongo = true;

		if (_rc.right - m_fly._rc.right > FLYSPEED && !m_isDongo)
		{
			if (m_fly._rc.top - (_rc.top - 60) > 10)	// 플레이어가 위쪽에 있단 전제
			{
				if (addDeley < pastTime)
				{
					pastTime = 0;
					OffsetRect(&m_fly._rc, FLYSPEED, -FLYSPEED);
				}
			}
			if (_rc.bottom - m_fly._rc.bottom > 100)
			{
				if (addDeley < pastTime)
				{
					pastTime = 0;
					OffsetRect(&m_fly._rc, FLYSPEED, FLYSPEED);
				}
			}
			if (addDeley < pastTime)
			{
				pastTime = 0;
				OffsetRect(&m_fly._rc, FLYSPEED, 0);
			}
		}
	}
	else if (m_playerDirect == PLAYER_RIGHT && _rc.right - m_fly._rc.right <= 0) m_isDongo = true;

	//상하 처리
	if (m_fly._rc.top - (_rc.top - 60) > 10)	// 플레이어가 위쪽에 있단 전제
	{
		if (addDeley < pastTime)
		{
			pastTime = 0;
			OffsetRect(&m_fly._rc, 0, -FLYSPEED);
		}
	}
	if (_rc.bottom - m_fly._rc.bottom > 100)
	{
		if (addDeley < pastTime)
		{
			pastTime = 0;
			OffsetRect(&m_fly._rc, 0, FLYSPEED);
		}


		if (m_fly._rc.left - _rc.left > 10 || _rc.right - m_fly._rc.right > 10)
		{
			m_isDongo = false;
		}
	}
}



//=======================//
//    애니메이션 설정     //
//=======================//

void fly::animationStart()
{
	pastTime += time;

	if (tempAni != m_fly.m_ani)
	{
		m_fly.m_ani->start();
	}
}

void fly::animationCollect(RECT _rc)
{
	// 충돌처리후 애니메이션 처리
	RECT temp;
	tempAni = m_fly.m_ani;

	if (IntersectRect(&temp, &_rc, &m_fly._fightColli))
	{
		if (!m_onceAni) {  // moveReady 애니
			m_fly.m_ani = ANIMATIONMANAGER->findAnimation("fly_MoveReady");
			m_onceAni = true;
			m_flyAni = FLY_MOVEREADY;
		}

		if (m_fly.m_ani->getPlayIndex() == 2 && m_onceAni && m_flyAni == FLY_MOVEREADY)
		{	// move 애니
			m_fly.m_ani = ANIMATIONMANAGER->findAnimation("fly_Move");
			m_flyAni = FLY_MOVE;
		}

		if (IntersectRect(&temp, &m_fly._realCollRect, &_rc))
		{	// attack 애니
			m_fly.m_ani = ANIMATIONMANAGER->findAnimation("fly_Attack");
			m_flyAni = FLY_ATTACK;
		}
		if (!(IntersectRect(&temp, &m_fly._realCollRect, &_rc))&& m_flyAni == FLY_ATTACK)
		{
			m_onceAni = false;
		}
	}

	if (m_flyAni == FLY_ATTACK && m_fly.m_ani->getPlayIndex() == 13)
	{
		m_onceAni = false;
	}
	
}

//=======================//
//    렉트 기본 설정     //
//=======================//

void fly::enemySetRect(int _x, int _y)
{
	m_fly._fightColli = RectMakeCenter(m_fly._rc.left, m_fly._rc.top, 800, 800);
	m_fly._realCollRect = RectMakeCenter(m_fly._rc.left, m_fly._rc.top +50, 200, 200);
	
	if(m_flyAni != FLY_ATTACK)
	m_fly._objectRc = RectMakeCenter(m_fly._rc.left+ 30, m_fly._rc.top+ 30, 40, 40);

	if (m_flyAni == FLY_ATTACK)
	{
		if (addDeley < pastTime)
		{
			m_attackRectCount += 1;
			m_fly._objectRc = RectMakeCenter(m_fly._rc.left + 30, (m_fly._rc.top+ 30) + m_attackRectCount, 40, 40);
		}
		if (m_fly.m_ani->getPlayIndex() == 0)
		{
			m_attackRectCount = 0;
			m_fly._objectRc = RectMakeCenter(m_fly._rc.left + 30, m_fly._rc.top + 30, 40, 40);
		}
	}
}


