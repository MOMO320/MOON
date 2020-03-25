#include "stdafx.h"
#include "player.h"

player::player() : m_arrow(new arrow) , m_objManager(new objectManager)
{ 
	m_player.m_playerDirect = PLAYER_DOWN;
	m_player.m_playerStatus = DUNGEON_PLAYER;
	m_player.m_aniStauts = IDLE;
	m_player.m_weaponAni = SWORD;

	m_player.m_playerInPlace = RectMakeCenter(WINSIZEX / 2 + 5, 360, WINSIZEX - 300, WINSIZEY / 2 + 180);

	m_player.m_speed = 300.0f;
	m_player.m_attack = 10;
	m_player.m_hp = 100;
	m_player.m_dev = 5;
	m_player.m_money = 1000;
}

player::~player()
{
	delete m_arrow;
	delete m_objManager;
}

HRESULT player::init()
{
	// character 기본 설정
	m_player.m_img[0] = IMAGEMANAGER->findImage("dungeonPlayer");  // DUNGEON_PLAYER
	m_player.m_img[1] = IMAGEMANAGER->findImage("swordPlayer");	 // SWORD_PLAYER
	m_player.m_img[2] = IMAGEMANAGER->findImage("bowPlayer");	 // BOW_PLAYER
	m_player.m_img[3] = IMAGEMANAGER->findImage("townPlayer");  // SPEAR_PALYER

	m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_downIdle");
	m_player.m_ani->start();

	// 화살 오브젝트
	m_arrow->init(m_player._rc);

	return S_OK;
}

void player::release()
{
	IMAGEMANAGER->deleteAll();
	ANIMATIONMANAGER->deleteALL();
}

void player::update(dungeonMap* _dungMap)
{
	//time = TIMEMANAGER->getElapsedTime();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && m_player._rc.left > m_player.m_playerInPlace.left && !m_isRoll&& m_player.m_aniStauts != DIE)
	{
		characterMove(_dungMap);
		m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_leftWalk");
		m_player.m_playerDirect = PLAYER_LEFT;
		m_player.m_aniStauts	= WALK;
	}
	if(KEYMANAGER->isOnceKeyUp(VK_LEFT) && !m_isRoll)
	{
		m_player.m_aniStauts = IDLE;
		m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_leftIdle");
		m_player.m_ani->start();
	}	

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_player._rc.right < m_player.m_playerInPlace.right && !m_isRoll&& m_player.m_aniStauts != DIE)
	{
		characterMove(_dungMap);
		m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_rightWalk");
		m_player.m_playerDirect = PLAYER_RIGHT;
		m_player.m_aniStauts	= WALK;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && !m_isRoll)
	{
		m_player.m_aniStauts = IDLE;
		m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_rightIdle");
		m_player.m_ani->start();
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && m_player._rc.top > m_player.m_playerInPlace.top && !m_isRoll&& m_player.m_aniStauts != DIE)
	{
		characterMove(_dungMap);
		m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_upWalk");
		m_player.m_playerDirect = PLAYER_UP;
		m_player.m_aniStauts	= WALK;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP) && !m_isRoll)
	{
		m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_upIdle");
		m_player.m_ani->start();
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && m_player._rc.bottom < m_player.m_playerInPlace.bottom && !m_isRoll&& m_player.m_aniStauts != DIE)
	{
		characterMove(_dungMap);
		m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_downWalk");
		m_player.m_playerDirect = PLAYER_DOWN;
		m_player.m_aniStauts = WALK;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && !m_isRoll)
	{
		m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_downIdle");
		m_player.m_ani->start();
	}

	//	   공 격 모 션    //
	if (KEYMANAGER->isStayKeyDown('A') && m_player.m_aniStauts != FIGHT && m_player.m_aniStauts != DIE)
	{
		m_player.m_aniStauts = FIGHT;
		if (m_player.m_weaponAni == BOW)
		{
			m_isBow = true;
			m_arrow->setArrowX(m_x);
			m_arrow->setArrowY(m_y);
			m_arrow->setMainRect(m_player._rc);
		}
	}
	if (m_player.m_aniStauts == FIGHT)
	{
		pastTime += time;
	}
	if (KEYMANAGER->isOnceKeyDown('Q')) //무기 바꾸는 키
	{
		m_weaponeChangeCount += 1;
		if(m_weaponeChangeCount == 1) m_player.m_weaponAni = BOW;
		if (m_weaponeChangeCount == 2)
		{
			m_player.m_weaponAni = SWORD;
			m_weaponeChangeCount = 0;
		}
	}

	//  롤 모 션   //
	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && !m_isRoll && m_player.m_aniStauts != DIE)
	{
		m_player.m_aniStauts = ROLL;
		m_isRoll = true;
	}
	//  다 이 모 션   //
	if (m_player.m_hp < 0 || KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		m_player.m_aniStauts = DIE;
		m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_die");
		m_player.m_ani->start();
	}

	//======================================================================================
	if (m_player.m_aniStauts == FIGHT)
	{
		m_arrow->update(m_player._rc, m_player.m_playerDirect);
	}

	animation(m_player.m_playerDirect, m_player.m_playerStatus, m_player.m_aniStauts, m_player.m_weaponAni , _dungMap);

}

void player::render()
{
	Rectangle(getMemDC(), m_player._rc.left, m_player._rc.top, m_player._rc.right, m_player._rc.bottom);
	
	//  화살 이미지 랜더 ( 애니메이션 )
	if (m_isBow && m_objManager->getisConnect() == false && !m_bowAlpha)
		m_arrow->render(m_player.m_weaponAni);

	if (m_objManager->getisConnect() == true)
	{
		if (!m_bowAniOnce)
		{
			m_arrow->getArrowInfo().m_ani->start();
			m_bowAniOnce = true;
		}
	 	m_arrow->getArrowInfo().m_aniImg->aniRender(getMemDC(), m_arrow->getArrowInfo().m_mainRc.left, m_arrow->getArrowInfo().m_mainRc.top - 5 , m_arrow->getArrowInfo().m_ani);	
	}
	if (m_arrow->getArrowInfo().m_ani->getPlayIndex() == 4)
	{
		m_arrow->getArrowInfo().m_ani->stop();

		for (int i = 100; i > 0; i -= 5)
		{
			m_arrow->getArrowInfo().m_img->alphaRender(getMemDC(), i);
		}
		m_objManager->setisConnect(false);
		m_bowAniOnce = false;
		m_bowAlpha = true;
	}
	//  화살 이미지 랜더 ( 애니메이션 )
	
	if(m_player.m_aniStauts == IDLE || m_player.m_aniStauts == WALK  || m_player.m_aniStauts == ROLL || m_player.m_aniStauts == DIE)
	m_player.m_img[0]->aniRender(getMemDC(), m_player._rc.left -50 , m_player._rc.top -50 , m_player.m_ani);

	if (m_player.m_aniStauts == FIGHT && m_player.m_weaponAni == SWORD)
	m_player.m_img[1]->aniRender(getMemDC(), m_player._rc.left -50 , m_player._rc.top - 50, m_player.m_ani);
	
	if (m_player.m_aniStauts == FIGHT && m_player.m_weaponAni == BOW)
	m_player.m_img[2]->aniRender(getMemDC(), m_player._rc.left - 50, m_player._rc.top - 50, m_player.m_ani);

	
}

void player::animation(PLAYERDIRECTION _Directtion, PLAYERSTATUS _status, ANISTATUS _aniStatus, WEAPONEANI _weapone , dungeonMap* _dungMap)
{
	switch (_aniStatus)
	{
	case WALK:
		switch (_Directtion)
		{
		case PLAYER_LEFT:
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))		m_player.m_ani->start();
			break;
		case PLAYER_UP:
			if (KEYMANAGER->isOnceKeyDown(VK_UP))		 m_player.m_ani->start();
			break;
		case PLAYER_RIGHT:
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))	 m_player.m_ani->start();
			break;
		case PLAYER_DOWN:
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))		 m_player.m_ani->start();
			break;
		}
		break;

	case FIGHT:
			switch (_weapone)
			{
			case SWORD:
				switch (_Directtion)
				{
				case PLAYER_LEFT:
					if (m_attackCombo == 0)
					{
						if (KEYMANAGER->isOnceKeyDown('A'))
						{
							m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_swordLeftCombo1");
							m_player.m_ani->start();
							m_isCombo = true;
						}
					    if (m_player.m_ani->getPlayIndex() == 5)
						{
							m_player.m_ani->stop();
							m_attackCombo += 1;
							m_player.m_aniStauts = WALK;
							m_isCombo = false;
							m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_leftIdle");
						}
					}
					else if (m_attackCombo == 1)
					{
						if (KEYMANAGER->isOnceKeyDown('A') )
						{
							if (m_attackCombo == 1)
							{
								m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_swordLeftCombo2");
								m_player.m_ani->start();
								pastTime = 0;
								m_isCombo = true;
							}
						}
						if (m_player.m_ani->getPlayIndex() == 4 && m_attackCombo == 1)
						{
							m_player.m_ani->stop();
							m_isCombo = false;
							m_attackCombo = 0;
							m_player.m_aniStauts = WALK;
							m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_leftIdle");
						}
					}
					break;
				case PLAYER_UP:
					if (m_attackCombo == 0)
					{
						if (KEYMANAGER->isOnceKeyDown('A'))
						{
							m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_swordUpCombo1");
							m_player.m_ani->start();
							m_isCombo = false;
						}
						if (m_player.m_ani->getPlayIndex() == 5)
						{
							m_player.m_ani->stop();
							m_attackCombo += 1;
							m_player.m_aniStauts = WALK;
							m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_upIdle");
						}
					}
					else if (m_attackCombo == 1)
					{
						if (KEYMANAGER->isOnceKeyDown('A'))
						{
							if (m_attackCombo == 1)
							{
								m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_swordUpCombo2");
								m_player.m_ani->start();
								pastTime = 0;
							}
						}
						if (m_player.m_ani->getPlayIndex() == 4 && m_attackCombo == 1)
						{
							m_player.m_ani->stop();
							m_attackCombo = 0;
							m_player.m_aniStauts = WALK;
							m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_upIdle");
						}
					}
					break;
				case PLAYER_RIGHT:
					if (m_attackCombo == 0)
					{
						if (KEYMANAGER->isOnceKeyDown('A') || m_isCombo)
						{
							m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_swordRightCombo1");
							m_player.m_ani->start();
							m_isCombo = false;
						}
						if (m_player.m_ani->getPlayIndex() == 5)
						{
							m_player.m_ani->stop();
							m_attackCombo += 1;
							m_player.m_aniStauts = WALK;
							m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_rightIdle");
						}
					}
					else if (m_attackCombo == 1)
					{
						if (KEYMANAGER->isOnceKeyDown('A'))
						{
							if (m_attackCombo == 1)
							{
								pastTime = 0;
								m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_swordRightCombo2");
								m_player.m_ani->start();
							}
						}
						if (m_player.m_ani->getPlayIndex() == 4 && m_attackCombo == 1)
						{
							m_player.m_ani->stop();
							m_attackCombo = 0;
							m_player.m_aniStauts = WALK;
							m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_rightIdle");
						}
					}
					break;
				case PLAYER_DOWN:
					if (m_attackCombo == 0)
					{
						if (KEYMANAGER->isOnceKeyDown('A'))
						{
							m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_swordDownCombo1");
							m_player.m_ani->start();
							m_isCombo = false;
						}
						if (m_player.m_ani->getPlayIndex() == 6)
						{
							m_player.m_ani->stop();
							m_attackCombo += 1;
							m_player.m_aniStauts = WALK;
							m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_downIdle");
						}
					}
					else if (m_attackCombo == 1)
					{
						if (KEYMANAGER->isOnceKeyDown('A'))
						{
							if (m_attackCombo == 1)
							{
								m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_swordDownCombo2");
								m_player.m_ani->start();
							}
						}
						if (m_player.m_ani->getPlayIndex() == 3 && m_attackCombo == 1)
						{
							m_player.m_ani->stop();
							m_attackCombo = 0;
							m_player.m_aniStauts = WALK;
							m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_downIdle");
						}
					}
					break;
				}
				break;
			case BOW:
				switch (m_player.m_playerDirect)
				{
				case PLAYER_LEFT:
					if (KEYMANAGER->isOnceKeyDown('A'))
					{
						m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_bowLeft");
						m_player.m_ani->start();
						m_bowAlpha = false;
					}
					if (m_player.m_ani->getPlayIndex() == 8)
					{
						m_player.m_ani->stop();
						m_player.m_aniStauts = WALK;
						m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_leftIdle");
					}
					if (m_objManager->getisConnect() == false)
					{
						m_objManager->objectMove(m_arrow->getArrowInfo(), _dungMap, m_player.m_playerDirect);
						m_arrow->setMainRect(m_objManager->getRcCollision());
						m_arrow->setArrowX(m_objManager->getX());
						m_arrow->setArrowY(m_objManager->getY());
					}
					break;
				case PLAYER_UP:
					if (KEYMANAGER->isOnceKeyDown('A'))
					{
						m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_bowUp");
						m_player.m_ani->start();
						m_bowAlpha = false;
					}
					if (m_player.m_ani->getPlayIndex() == 8)
					{
						m_player.m_ani->stop();
						m_player.m_aniStauts = WALK;
						m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_upIdle");
					}
					if (m_objManager->getisConnect() == false)
					{
						m_objManager->objectMove(m_arrow->getArrowInfo(), _dungMap, m_player.m_playerDirect);
						m_arrow->setMainRect(m_objManager->getRcCollision());
						m_arrow->setArrowX(m_objManager->getX());
						m_arrow->setArrowY(m_objManager->getY());
					}
					break;
				case PLAYER_RIGHT:
					if (KEYMANAGER->isOnceKeyDown('A'))
					{
						m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_bowRight");
						m_player.m_ani->start();
						m_bowAlpha = false;
					}
					if (m_player.m_ani->getPlayIndex() == 8)
					{
						m_player.m_ani->stop();
						m_player.m_aniStauts = WALK;
						m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_rightIdle");
					}
					if (m_objManager->getisConnect() == false)
					{
						m_objManager->objectMove(m_arrow->getArrowInfo(), _dungMap, m_player.m_playerDirect);
						m_arrow->setMainRect(m_objManager->getRcCollision());
						m_arrow->setArrowX(m_objManager->getX());
						m_arrow->setArrowY(m_objManager->getY());
					}
					break;
				case PLAYER_DOWN:
					if (KEYMANAGER->isOnceKeyDown('A'))
					{
						m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_bowDown");
						m_player.m_ani->start();
						m_bowAlpha = false;
					}
					if (m_player.m_ani->getPlayIndex() == 8)
					{
						m_player.m_ani->stop();
						m_player.m_aniStauts = WALK;
						m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_downIdle");
					}
					if (m_objManager->getisConnect() == false)
					{
						m_objManager->objectMove(m_arrow->getArrowInfo(), _dungMap, m_player.m_playerDirect);
						m_arrow->setMainRect(m_objManager->getRcCollision());
						m_arrow->setArrowX(m_objManager->getX());
						m_arrow->setArrowY(m_objManager->getY());
					}
					break;
				}
				break;
			case SPEAR:
				break;

			}
		break;

	case ROLL:
		switch (m_player.m_playerDirect)
		{
		case PLAYER_LEFT:
			if (m_isRoll)
			{
			    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			    {
			    	m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_leftRoll");
			    	m_player.m_ani->start();
			    }
			    if (m_player.m_ani->getPlayIndex() < 7)
			    {
					characterMove(_dungMap);
					OffsetRect(&m_player._rc, -2, 0);
			    }
			    else if (m_player.m_ani->getPlayIndex() == 7)
			    {
			    	m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_leftIdle");
			    	m_player.m_aniStauts = WALK;
					m_isRoll = false;
			    }
			}
			break;
		case PLAYER_UP:
			if (m_isRoll)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
				{
					m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_upRoll");
					m_player.m_ani->start();
				}
				if (m_player.m_ani->getPlayIndex() < 7)
				{
					characterMove(_dungMap);
					OffsetRect(&m_player._rc, 0, -2);
				}
				else if (m_player.m_ani->getPlayIndex() == 7)
				{
					m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_upIdle");
					m_player.m_aniStauts = WALK;
					m_isRoll = false;
				}
			}
			break;
		case PLAYER_RIGHT:
			if (m_isRoll)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
				{
					m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_rightRoll");
					m_player.m_ani->start();
				}
				if (m_player.m_ani->getPlayIndex() < 7)
				{
					characterMove(_dungMap);
					OffsetRect(&m_player._rc, 2, 0);
				}
				else if (m_player.m_ani->getPlayIndex() == 7)
				{
					m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_rightIdle");
					m_player.m_aniStauts = WALK;
					m_isRoll = false;
				}
			}
			break;
		case PLAYER_DOWN:
			if (m_isRoll)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
				{
					m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_downRoll");
					m_player.m_ani->start();
				}
				if (m_player.m_ani->getPlayIndex() < 7)
				{
					characterMove(_dungMap);
					OffsetRect(&m_player._rc, 0, 2);
				}
				else if (m_player.m_ani->getPlayIndex() == 7)
				{
					m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_downIdle");
					m_player.m_aniStauts = WALK;
					m_isRoll = false;
				}
			}
			break;
		}
		break;

	case DIE :
		if (m_player.m_ani->getPlayIndex() == 9)
		{
			m_player.m_ani->stop();
		}
		break;
	}
}

// 캐릭터 위치에 1/2 만한 RECT 생성
void player::setCharacPosition(RECT rc)
{
	int x , y;

	m_player._rc = rc;
	m_x = m_player._rc.left + (m_player._rc.right - m_player._rc.left) / 2;
	m_y = m_player._rc.top + (m_player._rc.bottom - m_player._rc.top) / 2;

}

void player::characterMove(dungeonMap* _dungMap)
{
	int tileIndex[2];	// 검사용 타일

 	rcCollision = m_player._rc;	// 가상의 충돌용 RECT

	//타임매니저를 이용한 방법 elpasedTime은 항상(0.0166667011)이다.
	float elpasedTime = TIMEMANAGER->getElapsedTime(); 
	//그래서 moveSpeed는 계속 약 1.6666 정도의 속도가 나온다.)
	float moveSpeed = elpasedTime * m_player.m_speed; 

	// 캐릭터의 방향에 따른 이동
	switch (m_player.m_playerDirect)
	{
	case PLAYER_LEFT:
		m_x -= moveSpeed;
		if (m_isRoll) m_x -= 2.0f;

		rcCollision = RectMakeCenter(m_x, m_y, 40, 40);
		break;

	case PLAYER_UP:
		m_y -= moveSpeed;
		if (m_isRoll) m_y -= 2.0f;
		rcCollision = RectMakeCenter(m_x, m_y, 40, 40);
		break;

	case PLAYER_RIGHT:
		m_x += moveSpeed;
		if (m_isRoll) m_x += 2.0f;
		rcCollision = RectMakeCenter(m_x, m_y, 40, 40);
		break;

	case PLAYER_DOWN :
		m_y += moveSpeed;
		if (m_isRoll) m_y += 2.0f;
		rcCollision = RectMakeCenter(m_x, m_y, 40, 40);
		break;

	default:
		break;
	}

	m_tileX = rcCollision.left / OBJ_TILESIZE;
	m_tileY = rcCollision.top / OBJ_TILESIZE;

	switch (m_player.m_playerDirect)
	{
		case  PLAYER_LEFT:
			tileIndex[0] = m_tileX + m_tileY * BACKTILEX;
			tileIndex[1] = m_tileX + (m_tileY + 1) * BACKTILEX;
			break;

		case PLAYER_RIGHT:
			tileIndex[0] = (m_tileX + m_tileY * BACKTILEX) + 1;
			tileIndex[1] = (m_tileX + (m_tileY + 1) * BACKTILEX) + 1;
			break;

		case PLAYER_UP:
			tileIndex[0] = m_tileX + m_tileY * BACKTILEX;
			tileIndex[1] = m_tileX + 1 + m_tileY * BACKTILEX;
			break;

		case PLAYER_DOWN :
			tileIndex[0] = (m_tileX + m_tileY * BACKTILEX) + BACKTILEX;
			tileIndex[1] = (m_tileX + 1 + m_tileY * BACKTILEX) + BACKTILEX;
			break;
	}

	for (int i = 0; i < 2; i++)
	{
		RECT rc;
		// 타일의 속성이 움직이지 못하는 곳이면...
		if ((_dungMap->getAttribute()[tileIndex[i]] == ATTR_UNMOVEABLE) &&
			IntersectRect(&rc, &_dungMap->getMap()[tileIndex[i]].m_rc, &rcCollision))
		{
			//움직이려 할때 갈 수 없는 지역이면 탱크의 움직임을 고정하자
			// ex) 플레이어가 왼쪽으로 갈때 왼쪽지역이 갈 수 없으면
			switch (m_player.m_playerDirect)
			{
			case PLAYER_LEFT:
				m_player._rc.left = _dungMap->getMap()[tileIndex[i]].m_rc.right;
				m_player._rc.right = m_player._rc.left + 60;
				m_x = m_player._rc.left + (m_player._rc.right - m_player._rc.left) / 2;
				break;

			case PLAYER_RIGHT:
				m_player._rc.right = _dungMap->getMap()[tileIndex[i]].m_rc.left;
				m_player._rc.left = m_player._rc.right - 60;
				m_x = m_player._rc.left + (m_player._rc.right - m_player._rc.left) / 2;
				break;

			case PLAYER_UP:
				m_player._rc.top = _dungMap->getMap()[tileIndex[i]].m_rc.bottom;
				m_player._rc.bottom  = m_player._rc.top + 60;
				m_y = m_player._rc.top + (m_player._rc.bottom - m_player._rc.top) / 2;
				break;

			case PLAYER_DOWN:
				m_player._rc.bottom = _dungMap->getMap()[tileIndex[i]].m_rc.top;
				m_player._rc.top = m_player._rc.bottom - 60;
				m_y = m_player._rc.top + (m_player._rc.bottom - m_player._rc.top) / 2;
				break;
			}
			return;
		}
		//여기에 산성을 밟으면 player의 체력이 떨어지는 효과 넣어야 함. 
		// !! 아직 안 넣음 !!
	} // end of for
	// 이제 움직여주자
	rcCollision = RectMakeCenter(m_x, m_y, 60, 60);
	m_player._rc = rcCollision;
}




