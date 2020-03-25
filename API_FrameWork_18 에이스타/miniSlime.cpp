#include "stdafx.h"
#include "miniSlime.h"

miniSlime::miniSlime()
{
}



miniSlime::~miniSlime()
{
}

HRESULT miniSlime::init(int x, int y)
{
	m_miniSlime.m_img = IMAGEMANAGER->findImage("miniSlime");
	m_miniSlime.m_ani = ANIMATIONMANAGER->findAnimation("miniSlime_Ani");

	m_miniSlime.name = "미니슬라임";
	m_miniSlime.attack = 3;
	m_miniSlime.hp = 10;
	m_miniSlime.speed = SLIMESPEED;

	m_miniSlime.m_ani->start();

	enemySetRect(x, y);

	pastTime = 0;

	return S_OK;
}

void miniSlime::release()
{
	IMAGEMANAGER->deleteAll();
	ANIMATIONMANAGER->deleteALL();
}

void miniSlime::update()
{
	if (m_miniSlime.hp < 0)
	{
		m_isDeath = true;
		m_miniSlime.m_img = IMAGEMANAGER->findImage("miniSlimeDeath");
	}
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

void miniSlime::enemySetRect(int _x, int _y)
{
	SetRect(&m_miniSlime._fightColli, 300, 100,
		(WINSIZEX / 2) + 450, (WINSIZEY / 2) + 260);
	
	m_miniSlime._rc = RectMakeCenter(_x, _y, m_miniSlime.m_img->getFrameWidth(), m_miniSlime.m_img->getFrameHeight());
}



