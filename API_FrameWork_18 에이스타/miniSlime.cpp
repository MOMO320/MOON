#include "stdafx.h"
#include "miniSlime.h"

miniSlime::miniSlime():m_aStar(new aStar), m_HpBar(new progressBar)
{
}


miniSlime::~miniSlime()
{
	delete m_aStar;
	delete m_HpBar;
}

HRESULT miniSlime::init(int x, int y)
{

	return S_OK;
}

HRESULT miniSlime::init(int x, int y, dungeonMap * _dunMap, enemies * _enemy)
{
	m_miniSlime.m_img = IMAGEMANAGER->findImage("miniSlime");
	m_miniSlime.m_ani = ANIMATIONMANAGER->findAnimation("miniSlime_Ani");

	m_miniSlime.name = "미니슬라임";
	m_miniSlime.attack = 3;
	m_miniSlime.hp = 10;
	m_miniSlime.speed = SLIMESPEED;

	m_miniSlime.m_ani->start();

	m_aStar->init(_dunMap->getMap(), _enemy, x, y);

	enemySetRect(x, y);
	m_HpBar->init("images/progressBar.bmp", "images/progressBarBack1.bmp", m_miniSlime._rc.left, m_miniSlime._rc.top - 5, 30, 10 / 2);

	pastTime = 0;

	return S_OK;
}

void miniSlime::release()
{
	IMAGEMANAGER->deleteAll();
	ANIMATIONMANAGER->deleteALL();
	m_aStar->release();
	m_HpBar->release();
}

void miniSlime::update()
{
	if (m_miniSlime.hp < 0)
	{
		m_isDeath = true;
		m_miniSlime.m_img = IMAGEMANAGER->findImage("miniSlimeDeath");
	}
}

void miniSlime::update(dungeonMap * _dunMap, RECT _playerRC, enemies * _enemy, int _speed, bool _isBool , RECT _playerAttack, int _attack)
{
	m_aStar->update(_dunMap->getMap(), _playerRC, _enemy, _speed, _isBool);
	m_HpBar->update(m_miniSlime._rc.left, m_miniSlime._rc.top);
	collision(_playerAttack, _attack);
}

void miniSlime::render()
{
	float elapsedTime;

	elapsedTime = TIMEMANAGER->getElapsedTime();

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		RectangleMake(getMemDC(), m_miniSlime._rc.left, m_miniSlime._rc.top, m_miniSlime.m_img->getFrameWidth(), m_miniSlime.m_img->getFrameHeight());
	}

	m_miniSlime.m_img->aniRender(getMemDC(), m_miniSlime._rc.left, m_miniSlime._rc.top, m_miniSlime.m_ani);
	
	if (m_isDeath)
	{
		pastTime += elapsedTime;
		
		for (int i = 0; i <= 100 ;i)
		{
		    if (addDeleyTime < pastTime)
		    {
				m_miniSlime.m_img->alphaRender(getMemDC(),m_miniSlime._rc.left,m_miniSlime._rc.top ,i);
				i += 20;
		    }
		}
	}
}

void miniSlime::render(PLAYERDIRECTION _direct ,RECT _rc)
{
}

void miniSlime::render(enemies * _enemy)
{
	m_aStar->render(_enemy);
	m_HpBar->render(m_miniSlime._rc.left, m_miniSlime._rc.top);
}

void miniSlime::enemySetRect(int _x, int _y)
{
	SetRect(&m_miniSlime._fightColli, 300, 100,
		(WINSIZEX / 2) + 450, (WINSIZEY / 2) + 260);
	
	m_miniSlime._rc = RectMakeCenter(_x, _y, m_miniSlime.m_img->getFrameWidth(), m_miniSlime.m_img->getFrameHeight());
}

void miniSlime::collision(RECT _playerRc, int _playerAttack)
{
	RECT temp;
	if (IntersectRect(&temp, &_playerRc, &m_miniSlime._rc))
	{
		m_miniSlime.hp -= _playerAttack;
		m_HpBar->setGauge(m_miniSlime.hp, 15);
	}
}



