#include "stdafx.h"
#include "flea.h"

flea::flea() : m_aStar(new aStar) ,m_HpBar(new progressBar)
{
}

flea::~flea()
{
	delete m_aStar;
	delete m_HpBar;
}

HRESULT flea::init(int x, int y)
{
	return S_OK;
}

HRESULT flea::init(int x, int y ,dungeonMap * _dunMap, enemies * _enemy)
{
	m_flea.m_img = IMAGEMANAGER->findImage("flea");
	m_flea.m_ani = ANIMATIONMANAGER->findAnimation("flea_Ani");

	m_flea.name = "º­·è";
	m_flea.attack = 3;
	m_flea.hp = 15;
	m_flea.speed = FLEASPEED;

	m_flea.m_ani->start();

	m_aStar->init(_dunMap->getMap(), _enemy, x,y);
	enemySetRect(x, y);

	m_HpBar->init("images/progressBar.bmp", "images/progressBarBack1.bmp", m_flea._rc.left, m_flea._rc.top - 5, 30, 10/2);

	pastTime = 0;

	return S_OK;
}

void flea::release()
{
	IMAGEMANAGER->deleteAll();
	ANIMATIONMANAGER->deleteALL();
	m_aStar->release();
	m_HpBar->release();
}

void flea::update()
{
	if (m_flea.hp <= 0)
	{
		m_isDeath = true;
		m_flea.m_img = IMAGEMANAGER->findImage("fleaDeath");
	}
}

void flea::update(dungeonMap * _dunMap, RECT _playerRC, enemies * _enemy, int _speed, bool _isBool, RECT _playerAttack, int _attack)
{
	m_HpBar->update(m_flea._rc.left , m_flea._rc.top);
	m_aStar->update(_dunMap->getMap(), _playerRC, _enemy, _speed, _isBool);
	collision(_playerAttack, _attack);
}

void flea::render()
{
	float elapsedTime;

	elapsedTime = TIMEMANAGER->getElapsedTime();

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		RectangleMake(getMemDC(), m_flea._rc.left, m_flea._rc.top,
			m_flea.m_img->getFrameWidth(), m_flea.m_img->getFrameHeight());
	}
	m_flea.m_img->aniRender(getMemDC(), m_flea._rc.left, m_flea._rc.top, m_flea.m_ani);

	if (m_isDeath)
	{
		pastTime += elapsedTime;

		for (int i = 0; i <= 100; i)
		{
			if (addDeleyTime < pastTime)
			{
				m_flea.m_img->alphaRender(getMemDC(), m_flea._rc.left, m_flea._rc.top, i);
				i += 20;
			}
		}
	}
}

void flea::render(PLAYERDIRECTION _direct, RECT _rc)
{
}

void flea::render(enemies * _enemy)
{
	m_aStar->render(_enemy);
	m_HpBar->render(m_flea._rc.left ,m_flea._rc.top);
}

void flea::enemySetRect(int _x, int _y)
{
	SetRect(&m_flea._fightColli , 300,100,
		(WINSIZEX / 2) + 450, (WINSIZEY / 2) + 260);
	m_flea._rc = RectMakeCenter(_x, _y, m_flea.m_img->getFrameWidth(), m_flea.m_img->getFrameHeight());
}

void flea::collision(RECT _playerRc, int _playerAttack)
{
	RECT temp;
	if (IntersectRect(&temp, &_playerRc, &m_flea._rc))
	{
		m_flea.hp -= _playerAttack;
		m_HpBar->setGauge(m_flea.hp, 15);
	}
	
}
