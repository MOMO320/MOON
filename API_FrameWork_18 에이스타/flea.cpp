#include "stdafx.h"
#include "flea.h"

flea::flea()
{
}

flea::~flea()
{
}

HRESULT flea::init(int x, int y)
{
	m_flea.m_img = IMAGEMANAGER->findImage("flea");
	m_flea.m_ani = ANIMATIONMANAGER->findAnimation("flea_Ani");

	m_flea.name = "º­·è";
	m_flea.attack = 3;
	m_flea.hp = 15;
	m_flea.speed = FLEASPEED;

	m_flea.m_ani->start();

	enemySetRect(x, y);

	pastTime = 0;

	return S_OK;
}

void flea::release()
{
	IMAGEMANAGER->deleteAll();
	ANIMATIONMANAGER->deleteALL();
}

void flea::update()
{
	if (m_flea.hp < 0)
	{
		m_isDeath = true;
		m_flea.m_img = IMAGEMANAGER->findImage("fleaDeath");
	}
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

void flea::enemySetRect(int _x, int _y)
{
	SetRect(&m_flea._fightColli , 300,100,
		(WINSIZEX / 2) + 450, (WINSIZEY / 2) + 260);
	m_flea._rc = RectMakeCenter(_x, _y, m_flea.m_img->getFrameWidth(), m_flea.m_img->getFrameHeight());
}
