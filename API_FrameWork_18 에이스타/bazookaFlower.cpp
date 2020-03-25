#include "stdafx.h"
#include "bazookaFlower.h"

bazookaFlower::bazookaFlower() : m_bazookaBall(new bazookaBall) , m_objManager(new objectManager)
{
}

bazookaFlower::~bazookaFlower()
{
	delete m_bazookaBall;
	delete m_objManager;
}

HRESULT bazookaFlower::init(int x, int y)
{
	m_bazooFlower.m_img = IMAGEMANAGER->findImage("bazookaFlower_left");
	m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_left_Move");

	m_bazooFlower.name = "바주카꽃";
	m_bazooFlower.attack = 10;
	m_bazooFlower.hp	 = 30;
	m_bazooFlower.speed = BAZOOKAFLOWERSPEED;

	m_bazooFlower.m_ani->start();

	pastTime = 0;
	
	m_direction = ENEMY_LEFT;

	m_aniType = ENEMY_IDEL;

	enemySetRect(x, y);

	m_x = m_bazooFlower._objectRc.left;
	m_y = m_bazooFlower._objectRc.top;

	m_bazookaBall->setBazookaBallX(m_x);
	m_bazookaBall->setBazookaBallY(m_y);


	m_bazookaBall->init();

	return S_OK;
}

void bazookaFlower::release()
{
	IMAGEMANAGER->deleteAll();
	ANIMATIONMANAGER->deleteALL();
}

void bazookaFlower::update()
{
}

void bazookaFlower::update(RECT _playerRc , dungeonMap * _dungMap , int _moveRangeX, int _moveRangeY , int _width, int _height)
{
	RECT temp;
	float time = TIMEMANAGER->getElapsedTime();
	directObjectSet(m_direction);
	
	//플레이어와 이동 범위
	m_bazooFlower._realCollRect = RectMakeCenter(m_bazooFlower._rc.left, m_bazooFlower._rc.top + (m_bazooFlower.m_img->getFrameHeight()/2), 400, 100);
	m_bazooFlower._fightColli = RectMakeCenter(m_bazooFlower._rc.left+ _moveRangeX, m_bazooFlower._rc.top+ _moveRangeY, _width, _height);
	
	m_bazookaBall->update(m_bazooFlower._objectRc , m_objManager->getisConnect());

	bazooFlowerAni(_playerRc);
	bazooFlowerMovetoPlayer(_playerRc, time, _dungMap);

	if (m_isConnect && m_bazookaBall->getBazookaBallInfo().m_ani->getPlayIndex() ==1)
	{
		m_isConnect = false;
		m_x = m_bazooFlower._objectRc.left;
		m_y = m_bazooFlower._objectRc.top;

		m_bazookaBall->setBazookaBallX(m_x);
		m_bazookaBall->setBazookaBallY(m_y);
		m_objManager->setisConnect(false);
	}
	if (m_aniType == ENEMY_RELOAD && m_attackCount <= 3 && m_isConnect)
	{
		m_x = m_bazooFlower._objectRc.left;
		m_y = m_bazooFlower._objectRc.top;

		m_bazookaBall->setBazookaBallX(m_x);
		m_bazookaBall->setBazookaBallY(m_y);
	}

	if (m_aniType == ENEMY_ATTACK && m_objManager->getisConnect() == false &&!m_isConnect)
	{
		m_pastTime += time;
		if (m_bazooFlower.m_ani->getPlayIndex() >= 3 && 0.5 < m_pastTime)
		{
			m_isAttackObject = true;
		}
	}

	if (m_isAttackObject || m_attackCount <= 3  && m_isConnect)
	{
		m_objManager->objectMove(m_bazookaBall->getBazookaBallInfo(), _dungMap, m_direction, 10);
		m_bazookaBall->setMainRect(m_objManager->getRcCollision());
		m_bazookaBall->setBazookaBallX(m_objManager->getX());
		m_bazookaBall->setBazookaBallY(m_objManager->getY());
	}

	if (m_objManager->getisConnect() == true || !m_isAttackObject)
	{
		m_isAttackObject = false;

		if (m_objManager->getisConnect() == true)
		{
			m_isConnect = true;
			m_conncetCount += 1;
		}
	}
}

void bazookaFlower::render()
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
	  colorRectangle(getMemDC(), m_bazooFlower._fightColli.left, m_bazooFlower._fightColli.top, 700, 100, 255, 0, 0);
	  colorRectangle(getMemDC(), m_bazooFlower._moveColli.left, m_bazooFlower._moveColli.top, 100, 500, 0, 255, 0);
	  AlphaRectangle(getMemDC(), m_bazooFlower._rc.left, m_bazooFlower._rc.top, m_bazooFlower._rc.right, m_bazooFlower._rc.bottom);
	  Rectangle(getMemDC(), m_bazookaBall->getBazookaBallInfo().m_mainRc.left, m_bazookaBall->getBazookaBallInfo().m_mainRc.top, m_bazookaBall->getBazookaBallInfo().m_mainRc.right, m_bazookaBall->getBazookaBallInfo().m_mainRc.bottom);
	  colorRectangle(getMemDC(), m_bazooFlower._realCollRect.left, m_bazooFlower._realCollRect.top, 400, 100, 0, 0, 255);
	}
}

void bazookaFlower::render(PLAYERDIRECTION _direct, RECT _rc)
{
	// 플레이어의 위치에 따른 애니메이션 처리
	
	if(_rc.right < m_bazooFlower._rc.right)
	{ /* 플레이어가 enemy 보다 왼쪽에 있다면 */
		if (_rc.top > m_bazooFlower._rc.top &&abs(m_bazooFlower._rc.right - _rc.right) < abs(m_bazooFlower._rc.top - _rc.top))
		{
			m_bazooFlower.m_img = IMAGEMANAGER->findImage("bazookaFlower_bottom");
			m_direction = ENEMY_DOWN;
		}
		else if (_rc.top < m_bazooFlower._rc.top && abs(m_bazooFlower._rc.right - _rc.right) < abs(m_bazooFlower._rc.top - _rc.top))
		{
			m_bazooFlower.m_img = IMAGEMANAGER->findImage("bazookaFlower_up");
			m_direction = ENEMY_UP;
		}
		else
		{
			m_bazooFlower.m_img = IMAGEMANAGER->findImage("bazookaFlower_left");
			m_direction = ENEMY_LEFT;
		}
	}
	if (m_bazooFlower._rc.left < _rc.left)
	{ /* 플레이어가 enemy 보다 오른쪽에 있다면 */
		if (_rc.top > m_bazooFlower._rc.top &&abs(m_bazooFlower._rc.left - _rc.left) < abs(m_bazooFlower._rc.top - _rc.top))
		{
			m_bazooFlower.m_img = IMAGEMANAGER->findImage("bazookaFlower_bottom");
			m_direction = ENEMY_DOWN;
		}
		else if (_rc.top < m_bazooFlower._rc.top && abs(m_bazooFlower._rc.left - _rc.left) < abs(m_bazooFlower._rc.top - _rc.top))
		{
			m_bazooFlower.m_img = IMAGEMANAGER->findImage("bazookaFlower_up");
			m_direction = ENEMY_UP;
		}
		else
		{
			m_bazooFlower.m_img = IMAGEMANAGER->findImage("bazookaFlower_right");
			m_direction = ENEMY_RIGHT;
		}
	}

	if (m_aniType == ENEMY_ATTACK || m_aniType == ENEMY_RELOAD)
	{
		m_bazookaBall->render(m_isConnect);
	}
	
	m_bazooFlower.m_img->aniRender(getMemDC(), m_bazooFlower._rc.left + 25, m_bazooFlower._rc.top -40, m_bazooFlower.m_ani);
	colorRectangle(getMemDC(), m_bazooFlower._objectRc.left, m_bazooFlower._objectRc.top, 20, 16, 255, 0, 0);
	
}

void bazookaFlower::enemySetRect(int _x, int _y)
{
	m_bazooFlower._rc = RectMakeCenter(_x, _y, m_bazooFlower.m_img->getFrameWidth(), m_bazooFlower.m_img->getFrameHeight());

	m_bazooFlower._moveColli = RectMakeCenter(_x, _y, 100, 500);
	m_bazooFlower._fightColli = RectMakeCenter(_x - 300, _y, 700, 100);
	//m_bazooFlower._objectRc = RectMakeCenter(_x-30, _y+20, 20, 16);

}

void bazookaFlower::readyAni(ENEMYDIRECTION _enemyDirct)
{
	switch (_enemyDirct)
	{
	case ENEMY_LEFT:
		m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_left_AttackReady");
		break;

	case ENEMY_DOWN:
		m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_Bottom_AttackReady");
		break;

	case ENEMY_UP:
		m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_Top_Attack");
		break;

	case ENEMY_RIGHT:
		m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_right_AttackReady");
		break;
	}
	m_bazooFlower.m_ani->start();
	m_aniType = ENEMY_READY;
}

void bazookaFlower::bazooFlowerMovetoPlayer(RECT _playerRc, float _time, dungeonMap * _dunMap)
{
	RECT temp;
	/* 플레어에 따른 적 이동 */
	if (m_isFight && !IntersectRect(&temp, &m_bazooFlower._fightColli, &_playerRc))
	{
		pastTime += _time;

		if (_playerRc.top - m_bazooFlower._rc.top <= 0)
		{
			if (addDeleyTime < pastTime)
			{
				//OffsetRect(&m_bazooFlower._rc, 0, -2);
				OffsetRect(&m_bazooFlower._objectRc, 0, -2);
				m_moveDirect = ENEMY_UP;
				enemyMove(m_bazooFlower, _dunMap, m_moveDirect, 200);
			}
		}

		if (_playerRc.top - m_bazooFlower._rc.top >= 0)
		{
			if (addDeleyTime < pastTime)
			{
				//OffsetRect(&m_bazooFlower._rc, 0, 2);
				OffsetRect(&m_bazooFlower._objectRc, 0, 2);
				m_moveDirect = ENEMY_DOWN;
				enemyMove(m_bazooFlower, _dunMap, m_moveDirect, 200);
			}
		}
	}
	if (getConnect() == true && m_direction == ENEMY_LEFT)
	{
		if (!IntersectRect(&temp, &m_bazooFlower._realCollRect, &_playerRc))
		{
			if (addDeleyTime < pastTime)
			{
				m_moveDirect = ENEMY_LEFT;
				enemyMove(m_bazooFlower, _dunMap, m_moveDirect, 200);
			}
		}
	}
}

void bazookaFlower::bazooFlowerAni(RECT _playerRc)
{
	RECT temp;
	
	if (tempDirect != m_direction) m_isFight = false;

	if (IntersectRect(&temp, &m_bazooFlower._fightColli, &_playerRc) && !m_isFight)
	{
		m_isFight = true;
		switch (m_direction)
		{
		case ENEMY_LEFT:
			m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_left_AttackReady");
			break;

		case ENEMY_DOWN:
			m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_Bottom_AttackReady");
			break;

		case ENEMY_UP:
			m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_Top_Attack");
			break;

		case ENEMY_RIGHT:
			m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_right_AttackReady");
			break;
		}
		tempDirect = m_direction;
		m_bazooFlower.m_ani->start();
		m_aniType = ENEMY_READY;
	}

	//if (m_aniType == ENEMY_READY) m_isFight = true;

	/* 공격모드로 들어가는 애니 */
	if (m_aniType == ENEMY_READY && m_isFight)
	{
		switch (m_direction)
		{
		case ENEMY_LEFT:
			if (m_bazooFlower.m_ani->getPlayIndex() == 11)
			{
				m_aniType = ENEMY_ATTACK;
				m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_left_Attack");
			}
			break;

		case ENEMY_DOWN:
			if (m_bazooFlower.m_ani->getPlayIndex() == 7)
			{
				m_aniType = ENEMY_ATTACK;
				m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_Bottom_Attack");
			}
			break;

		case ENEMY_RIGHT:
			if (m_bazooFlower.m_ani->getPlayIndex() == 11)
			{
				m_aniType = ENEMY_ATTACK;
				m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_right_Attack");
			}
			break;
		}
	}

	if (m_aniType == ENEMY_READY && !m_isAttackReady)
	{
		m_bazooFlower.m_ani->start();
		m_isAttackReady = true;
	}
	if (m_aniType == ENEMY_ATTACK && m_isAttackReady)
	{
		m_bazooFlower.m_ani->start();
		m_isAttackReady = false;
	}

	/* 공격모션 3번후 리로드 애니 */
	if (m_aniType == ENEMY_ATTACK && !m_isAttackReady)
	{
		switch (m_direction)
		{
		case ENEMY_LEFT:
			if (m_bazooFlower.m_ani->getPlayIndex() == 6 && m_attackCount < 3)
			{
				m_attackCount += 1;
				m_bazooFlower.m_ani->setPlayIndex(0);
			}
			if (m_attackCount == 3)
			{
				m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_left_Reload");
				m_attackCount = 0;
				m_aniType = ENEMY_RELOAD;
				m_bazooFlower.m_ani->start();
			}
			break;
		case ENEMY_DOWN:
			if (m_bazooFlower.m_ani->getPlayIndex() == 3 && m_attackCount < 4)
			{
				m_attackCount += 1;
				m_bazooFlower.m_ani->setPlayIndex(0);
			}
			else if (m_attackCount == 3)
			{
				m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_right_Reload");
				m_attackCount = 0;
				m_aniType = ENEMY_RELOAD;
				m_bazooFlower.m_ani->start();
			}
			break;

		case ENEMY_UP:
			break;

		case ENEMY_RIGHT:
			if (m_bazooFlower.m_ani->getPlayIndex() == 6 && m_attackCount < 3)
			{
				m_attackCount += 1;
				m_bazooFlower.m_ani->setPlayIndex(0);
			}
			else if (m_attackCount == 3)
			{
				m_bazooFlower.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_right_Reload");
				m_attackCount = 0;
				m_aniType = ENEMY_RELOAD;
				m_bazooFlower.m_ani->start();
			}
			break;
		}
	}

	if (m_aniType == ENEMY_RELOAD)
	{
		switch (m_direction)
		{
		case ENEMY_LEFT:
			if (m_bazooFlower.m_ani->getPlayIndex() == 11)
			{
				m_aniType = ENEMY_READY; m_isAttackReady = true;
				m_isAttackObject = false;
				readyAni(m_direction);
			}
			break;
		case ENEMY_DOWN:
			if (m_bazooFlower.m_ani->getPlayIndex() == 3)
			{
				m_aniType = ENEMY_READY;	m_isAttackReady = true;
				m_isAttackObject = false;
				readyAni(m_direction);
			}
			break;
		case ENEMY_UP:
			break;
		case ENEMY_RIGHT:
			if (m_bazooFlower.m_ani->getPlayIndex() == 11)
			{
				m_aniType = ENEMY_READY;  m_isAttackReady = false;
				m_isAttackObject = false;
				readyAni(m_direction);
			}
			break;
		}
	}
}

void bazookaFlower::directObjectSet(ENEMYDIRECTION _enemyDirct)
{
	switch (m_direction)
	{
	case ENEMY_LEFT:
		m_bazooFlower._objectRc = RectMakeCenter(m_bazooFlower._rc.left + 95, m_bazooFlower._rc.top + 55, 20, 16);
		break;
	case ENEMY_UP:
		break;
	case ENEMY_RIGHT:m_bazooFlower._objectRc = RectMakeCenter(m_bazooFlower._rc.right+15, m_bazooFlower._rc.top + 50, 20, 16);
		break;
	case ENEMY_DOWN:m_bazooFlower._objectRc = RectMakeCenter(m_bazooFlower._rc.left+92, m_bazooFlower._rc.top + 50, 20, 16);
		break;
	}
}
