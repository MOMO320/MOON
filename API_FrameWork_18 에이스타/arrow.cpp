#include "stdafx.h"
#include "arrow.h"
#include "gameTypes.h"

arrow::arrow() 
{
}

arrow::~arrow()
{

}

HRESULT arrow::init(RECT _rc)
{
	m_arrow.m_speed = 300.0f;

	m_arrow.m_img	 = IMAGEMANAGER->findImage("ARLeft");
	m_arrow.m_aniImg = IMAGEMANAGER->findImage("arrowLeft");
	m_arrow.m_ani	 = ANIMATIONMANAGER->findAnimation("Arrow_Left");
	
	return S_OK;
}

void arrow::release()
{
	IMAGEMANAGER->deleteAll();
	ANIMATIONMANAGER->deleteALL();
}

void arrow::update(RECT _rc , PLAYERDIRECTION _direct)
{
	m_arrow.m_rc = _rc;
	m_arrow.m_rc.left + 15;
	m_arrow.m_rc.top + 30;

	switch (_direct)
	{
	case PLAYER_LEFT:
		m_arrow.m_img = IMAGEMANAGER->findImage("ARLeft");
		m_arrow.m_aniImg = IMAGEMANAGER->findImage("arrowLeft");
		m_arrow.m_ani = ANIMATIONMANAGER->findAnimation("Arrow_Left");
		break;
	
	case PLAYER_RIGHT:
		m_arrow.m_img = IMAGEMANAGER->findImage("ARRight");
		m_arrow.m_aniImg = IMAGEMANAGER->findImage("arrowRight");
		m_arrow.m_ani = ANIMATIONMANAGER->findAnimation("Arrow_Right");
		break;
	
	case PLAYER_UP:
		m_arrow.m_img = IMAGEMANAGER->findImage("arrowOnceUp");
		m_arrow.m_aniImg = IMAGEMANAGER->findImage("upArrowMan");
    	m_arrow.m_ani = ANIMATIONMANAGER->findAnimation("Arrow_Up");
		break;
	
	case PLAYER_DOWN:
		m_arrow.m_img = IMAGEMANAGER->findImage("arrowOnceDown");
		m_arrow.m_aniImg = IMAGEMANAGER->findImage("downArrowMan");
		m_arrow.m_ani = ANIMATIONMANAGER->findAnimation("Arrow_Down");
		break;
	}

}

void arrow::render(WEAPONEANI _weapone )
{
	if (_weapone == BOW)
	{
	    m_arrow.m_img->render(getMemDC(), m_arrow.m_mainRc.left  , m_arrow.m_mainRc.top);
	}
	if(KEYMANAGER->isToggleKey(VK_F1))
	Rectangle(getMemDC(), m_arrow.m_mainRc.left, m_arrow.m_mainRc.top, m_arrow.m_mainRc.right, m_arrow.m_mainRc.bottom);
}

