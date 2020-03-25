#include "stdafx.h"
#include "bazookaBall.h"
#include "gameTypes.h"

bazookaBall::bazookaBall()
{
}

bazookaBall::~bazookaBall()
{
}

HRESULT bazookaBall::init()
{
	m_bazookaBall.m_speed = 300.0f;

	m_bazookaBall.m_img = IMAGEMANAGER->findImage("bazookaObject");
	m_bazookaBall.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_object_boom");

	return S_OK;
}

void bazookaBall::release()
{
	IMAGEMANAGER->deleteAll();
	ANIMATIONMANAGER->deleteALL();
}

void bazookaBall::update(RECT _enemyRc, bool _isConnect)
{
	m_bazookaBall.m_mainRc = _enemyRc;

	if (_isConnect && !m_isOnceAni)
	{
	
	}
	if (m_bazookaBall.m_ani->getPlayIndex() == 1)
	{
		m_isOnceAni = false;
	}
}

void bazookaBall::render(bool _isConnect)
{
	if (_isConnect == false)
	{
		m_bazookaBall.m_img = IMAGEMANAGER->findImage("bazookaObject");
		m_bazookaBall.m_img->render(getMemDC(), m_bazookaBall.m_mainRc.left -20, m_bazookaBall.m_mainRc.top);
		m_isOnceAni = false;
	}

	if (_isConnect == true && !m_isOnceAni)
	{
		m_bazookaBall.m_img = IMAGEMANAGER->findImage("bazookaObjectFrame");
		m_bazookaBall.m_ani = ANIMATIONMANAGER->findAnimation("bazooka_object_boom");
		m_bazookaBall.m_ani->start();
		m_isOnceAni = true;
	}

   if(_isConnect == true)
		m_bazookaBall.m_img->aniRender(getMemDC(), m_bazookaBall.m_mainRc.left -20, m_bazookaBall.m_mainRc.top, m_bazookaBall.m_ani);

	if (KEYMANAGER->isToggleKey(VK_F1)) {}
		
}
