#include "stdafx.h"
#include "mushRoom.h"

mushRoom::mushRoom() : m_objManager(new objectManager)
{
}

mushRoom::~mushRoom()
{
	delete m_objManager;
}

HRESULT mushRoom::init(int x, int y)
{
	m_mushRoom.m_img = IMAGEMANAGER->findImage("mushRoom");
	m_mushRoom.m_ani = ANIMATIONMANAGER->findAnimation("mushRoom_wait");

	m_mushRoom.name		= "버섯";
	m_mushRoom.attack	= 8;
	m_mushRoom.hp		= 25;
	m_mushRoom.speed = MUSHROOMSPEED;

	m_mushRoom.angle = PI / 2;  // 90도

	m_mushRoom.center.x = x;
	m_mushRoom.center.y = y;

	m_mushRoom.radius = 30.0f;
	m_mushRoom.gravity = 0.0f;

	m_mushRoom.m_ani->start();
	
	m_mushRoom.direct = ENEMY_UP;

	enemySetRect(x, y);

	m_x = m_mushRoom._rc.left;
	m_y = m_mushRoom._rc.top;
	
	m_mushRoom.x = m_mushRoom._rc.left;
	m_mushRoom.y = m_mushRoom._rc.top;

	pastTime = 0;

	m_wall[0] = RectMake(150, 70, 80, WINSIZEY - 140);
	m_wall[1] = RectMake(230, 150, 80, WINSIZEY - 300);
	m_wall[2] = RectMake(WINSIZEX - 230, 70, 80, WINSIZEY - 140);
	m_wall[3] = RectMake(WINSIZEX - 310, 150, 80, WINSIZEY - 300);

	return S_OK;
}

void mushRoom::release()
{
	ANIMATIONMANAGER->deleteALL();
	IMAGEMANAGER->deleteAll();
}

void mushRoom::update()
{
}

void mushRoom::render()
{
	


}
void mushRoom::update(RECT rc, dungeonMap * map)
{
	RECT temp;

	// 이동에 따른 애니메이션 변경 값
	if (IntersectRect(&temp, &rc, &m_mushRoom._fightColli) && !m_isOnceAni)
	{
		m_mushRoom.m_ani = ANIMATIONMANAGER->findAnimation("mushRoom_Move1");
		m_mushRoom.m_ani->start();
		m_isOnceAni = true;
		m_isFight = true;
	}
	if (m_mushRoom.m_ani->getPlayIndex() == 16 && m_isOnceAni)
	{
		m_mushRoom.m_ani = ANIMATIONMANAGER->findAnimation("mushRoom_Move2");
		m_mushRoom.m_ani->start();
		m_isTwoAni = true;
	}
	if (m_mushRoom.m_ani->getPlayIndex() == 11 && m_isTwoAni)
	{
		m_isTwoAni = false;
		m_isOnceAni = false;
	}
	//==========================================================================//

	if (m_isFight && !m_onceAngle)
	{
		/* angle 잡아주기   Enemy - player */
		m_mushRoom.angle = (m_mushRoom._rc.left - rc.left) * 0.05;
		m_mushRoom.x = cosf(m_mushRoom.angle) * (m_mushRoom.m_img->getFrameWidth()) + m_mushRoom.center.x;
		m_mushRoom.y = -sinf(m_mushRoom.angle) * (m_mushRoom.m_img->getFrameHeight()) + m_mushRoom.center.y;
		m_onceAngle = true;
		enemyDirect(rc);
	}
	if (m_onceAngle)
	{
		Move(rc, map);
	}
	
	
}

void mushRoom::render(dungeonMap * map)
{
	printText(getMemDC(), std::to_string(m_mushRoom.angle).c_str(), "고딕", WINSIZEX / 2, WINSIZEY / 2, 30, RGB(255, 255, 255), false, true);
	printText(getMemDC(), std::to_string(angleRect.left).c_str(), "고딕", WINSIZEX / 2, 200 + 50, 30, RGB(255, 255, 255), false, true);
	printText(getMemDC(), std::to_string(angleRect.top).c_str(), "고딕", WINSIZEX / 2, 200 + 100, 30, RGB(255, 255, 255), false, true);
	m_mushRoom.m_img->aniRender(getMemDC(), m_mushRoom.x, m_mushRoom.y, m_mushRoom.m_ani);
	
	AlphaRectangle(getMemDC(), m_mushRoom.x, m_mushRoom.y, m_mushRoom.x + m_mushRoom.m_img->getFrameWidth(), m_mushRoom.y + m_mushRoom.m_img->getFrameHeight());
	AlphaRectangle(getMemDC(), m_mushRoom._fightColli.left, m_mushRoom._fightColli.top, m_mushRoom._fightColli.right, m_mushRoom._fightColli.bottom);

	for (int i = 0; i < BACKTILEX*BACKTILEY; i++)
	{
		if (map->getMap()[i].m_obj != OBJ_DONGO) continue;
		if (map->getMap()[i].m_obj == OBJ_DONGO || map->getMap()[i].m_obj == OBJ_TREE)
		{
		//colorRectangle(getMemDC() ,map->getMap()[i].m_rc.left, map->getMap()[i].m_rc.top,80,80,100,255,100);
		printText(getMemDC(), std::to_string(i).c_str(), "고딕", map->getMap()[i].m_rc.left, map->getMap()[i].m_rc.top, 30, RGB(255, 255, 255), false, true);
		}
	}
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
	for(int i = 0 ; i < 4; i++)
	Rectangle(getMemDC(), m_wall[i].left, m_wall[i].top, m_wall[i].right, m_wall[i].bottom);
	}

}

void mushRoom::render(PLAYERDIRECTION _direct, RECT _rc)
{	
}

void mushRoom::enemySetRect(int _x, int _y)
{
	m_mushRoom._rc = RectMakeCenter(_x, _y, m_mushRoom.m_img->getFrameWidth(), m_mushRoom.m_img->getFrameHeight());
	m_mushRoom._fightColli = RectMake(m_mushRoom._rc.left-200 , 100 , 400,400);
}

void mushRoom::enemyDirect(RECT rc)
{
	/* 플레이어 위치 잡기 */
	if (rc.left < m_mushRoom._rc.left)
	{	// 왼쪽
		m_mushRoom.direct = ENEMY_LEFT;
	}
	if (rc.right > m_mushRoom._rc.right)
	{
		m_mushRoom.direct = ENEMY_RIGHT;
	}
	if (rc.top < m_mushRoom._rc.top)
	{
		m_mushRoom.direct = ENEMY_UP;
	}
	if (rc.bottom > m_mushRoom._rc.bottom)
	{
		m_mushRoom.direct = ENEMY_DOWN;
	}
}


void mushRoom::Move(RECT rc, dungeonMap * map)
{
	m_mushRoom.x += cosf(m_mushRoom.angle)* m_mushRoom.speed;
	m_mushRoom.y += -sinf(m_mushRoom.angle)* m_mushRoom.speed;

	angleRect = RectMakeCenter(m_mushRoom.x, m_mushRoom.y, m_mushRoom.m_img->getFrameWidth(), m_mushRoom.m_img->getFrameHeight());

	int tileIndex[2];	// 검사용 타일

	rcCollision = angleRect;	// 가상의 충돌용 RECT

	// 사각변에 따른충돌처리(튕김처리)
	/* 왼쪽 */
	if (m_mushRoom.x - m_mushRoom.m_img->getFrameWidth() < m_wall[1].right -80)
	{
		m_mushRoom.angle = PI - m_mushRoom.angle;
	}
	if (m_mushRoom.x - m_mushRoom.m_img->getFrameWidth() < m_wall[0].right -80)
	{
		m_mushRoom.angle = PI - m_mushRoom.angle;
	}

	/* 오른쪽 */
	if (m_mushRoom.x + m_mushRoom.m_img->getFrameWidth() > m_wall[2].left)
	{
		m_mushRoom.angle = PI - m_mushRoom.angle;
	}
	 if (m_mushRoom.x + m_mushRoom.m_img->getFrameWidth() > m_wall[3].left)
	{
		m_mushRoom.angle = PI - m_mushRoom.angle;
	}
	/* 위쪽 */
	if (m_mushRoom.y - m_mushRoom.m_img->getFrameHeight() < 40)
	{
		m_mushRoom.angle = 2 * PI - m_mushRoom.angle;
	}
	/* 아래쪽 */
	if (m_mushRoom.y + m_mushRoom.m_img->getFrameHeight() > WINSIZEY - 80)
	{
		m_mushRoom.angle = 2 * PI - m_mushRoom.angle;
	}

	//m_tileX = rcCollision.left / m_mushRoom.m_img->getFrameHeight();
	//m_tileY = rcCollision.top / m_mushRoom.m_img->getFrameWidth();

	//angleFistMoveDirect();

	//switch (enemyBeforeDirection)
	//{
	//case ENEMY_LEFT:
	//	tileIndex[0] = m_tileX + m_tileY * BACKTILEX;
	//	tileIndex[1] = m_tileX + (m_tileY + 1) * BACKTILEX;
	//	break;

	//case ENEMY_RIGHT:
	//	tileIndex[0] = (m_tileX + m_tileY * BACKTILEX) + 1;
	//	tileIndex[1] = (m_tileX + (m_tileY + 1) * BACKTILEX) + 1;
	//	break;

	//case ENEMY_DOWN:
	//	tileIndex[0] = m_tileX + m_tileY * BACKTILEX;
	//	tileIndex[1] = m_tileX + 1 + m_tileY * BACKTILEX;
	//	break;

	//case ENEMY_UP:
	//	tileIndex[0] = (m_tileX + m_tileY * BACKTILEX) + BACKTILEX;
	//	tileIndex[1] = (m_tileX + 1 + m_tileY * BACKTILEX) + BACKTILEX;
	//	break;
	//}

	//for (int i = 0; i < 2; i++)
	//{
	//	RECT temp;
	//	
	//	// 타일의 속성이 움직이지 못하는 곳이면...
	//	if ((map->getAttribute()[tileIndex[i]] == ATTR_UNMOVEABLE) &&
	//		IntersectRect(&temp, &map->getMap()[tileIndex[i]].m_rc, &rcCollision))
	//	{
	//		if (map->getAttribute()[tileIndex[i]] != ATTR_UNMOVEABLE) continue;
	//		beforeRect = rcCollision;
	//		//tileAngleDirect(map->getMap()[tileIndex[i]].m_rc, rcCollision);
	//		//움직이려 할때 갈 수 없는 지역이면 탱크의 움직임을 고정하자
	//		// ex) 플레이어가 왼쪽으로 갈때 왼쪽지역이 갈 수 없으면
	//		switch (enemyBeforeDirection)
	//		{
	//		case ENEMY_LEFT:
	//			m_mushRoom._rc.left = map->getMap()[tileIndex[i]].m_rc.right;
	//			m_mushRoom._rc.right = m_mushRoom._rc.left + 66;
	//			m_x = m_mushRoom._rc.left + (m_mushRoom._rc.right - m_mushRoom._rc.left) / 2;
	//			m_mushRoom.angle = PI - m_mushRoom.angle;
	//			break;

	//		case ENEMY_RIGHT:
	//			m_mushRoom._rc.right = map->getMap()[tileIndex[i]].m_rc.left;
	//			m_mushRoom._rc.left = m_mushRoom._rc.right - 66;
	//			m_x = m_mushRoom._rc.left + (m_mushRoom._rc.right - m_mushRoom._rc.left) / 2;
	//			m_mushRoom.angle = PI - m_mushRoom.angle;
	//			break;

	//		case ENEMY_UP:
	//			m_mushRoom._rc.top = map->getMap()[tileIndex[i]].m_rc.bottom;
	//			m_mushRoom._rc.bottom = m_mushRoom._rc.top + 72;
	//			m_y = m_mushRoom._rc.top + (m_mushRoom._rc.bottom - m_mushRoom._rc.top) / 2;
	//			m_mushRoom.angle = 2 * PI - m_mushRoom.angle;
	//			break;

	//		case ENEMY_DOWN:
	//			m_mushRoom._rc.bottom = map->getMap()[tileIndex[i]].m_rc.top;
	//			m_mushRoom._rc.top = m_mushRoom._rc.bottom - 72;
	//			m_y = m_mushRoom._rc.top + (m_mushRoom._rc.bottom - m_mushRoom._rc.top) / 2;
	//			m_mushRoom.angle = 2 * PI - m_mushRoom.angle;
	//			break;

	//			return;
	//		}
	//		//여기에 산성을 밟으면 player의 체력이 떨어지는 효과 넣어야 함. 
	//		// !! 아직 안 넣음 !!
	//	} // end of for
	//	// 이제 움직여주자
	//	rcCollision = RectMakeCenter(m_x, m_y, 66, 72);
	//	m_mushRoom._rc = rcCollision;
	//}
}
void mushRoom::angleFistMoveDirect()
{
	// 한바퀴z
	if ( m_mushRoom.angle >= 0.41f && m_mushRoom.angle <= 2.5f)
	{
		enemyBeforeDirection = ENEMY_UP;
	}
	if (4.0f >= m_mushRoom.angle && m_mushRoom.angle >= 2.51f)
	{
		enemyBeforeDirection = ENEMY_RIGHT;
	}
	if (5.7f >= m_mushRoom.angle && m_mushRoom.angle >= 4.01f)
	{
		enemyBeforeDirection = ENEMY_DOWN;
	}
	if (7.0f>= m_mushRoom.angle && m_mushRoom.angle >= 5.71f)
	{
		enemyBeforeDirection = ENEMY_LEFT;  
	}

	//플러스 두바퀴
	if (m_mushRoom.angle >= 7.01f && m_mushRoom.angle <= 8.90f)
	{
		enemyBeforeDirection = ENEMY_UP;
	}
	if (10.3f >= m_mushRoom.angle && m_mushRoom.angle >= 8.91f)
	{
		enemyBeforeDirection = ENEMY_RIGHT;
	}
	if (11.9f >= m_mushRoom.angle && m_mushRoom.angle >= 10.31f)
	{
		enemyBeforeDirection = ENEMY_DOWN;
	}
	if (13.2f >= m_mushRoom.angle && m_mushRoom.angle >= 11.91f)
	{
		enemyBeforeDirection = ENEMY_LEFT;
	}

	//플러스 세바퀴
	if (m_mushRoom.angle >= 13.21f && m_mushRoom.angle <= 15.5f)
	{
		enemyBeforeDirection = ENEMY_UP;
	}
	if (16.19f >= m_mushRoom.angle && m_mushRoom.angle >= 15.51f)
	{
		enemyBeforeDirection = ENEMY_RIGHT;
	}
	if (18.59f >= m_mushRoom.angle && m_mushRoom.angle >= 16.2f)
	{
		enemyBeforeDirection = ENEMY_DOWN;
	}
	if (19.9f >= m_mushRoom.angle && m_mushRoom.angle >= 18.36f)
	{
		enemyBeforeDirection = ENEMY_LEFT;
	}
	
	//플러스 네바퀴
	if (m_mushRoom.angle >= 21.3f && m_mushRoom.angle <= 19.91f)
	{
		enemyBeforeDirection = ENEMY_UP;
	}
	if (25.8f >= m_mushRoom.angle && m_mushRoom.angle >= 24.51f)
	{	//현재 수정
		enemyBeforeDirection = ENEMY_RIGHT;
	}
	if (24.5f >= m_mushRoom.angle && m_mushRoom.angle >= 22.4f)
	{
		enemyBeforeDirection = ENEMY_DOWN;
	}
	if (22.39f >= m_mushRoom.angle && m_mushRoom.angle >= 21.31f)
	{//현재 수정
		enemyBeforeDirection = ENEMY_LEFT;
	}
	if (m_mushRoom.angle >= 25.81f && m_mushRoom.angle <= 27.7f)
	{
		enemyBeforeDirection = ENEMY_UP;
	}
	if (m_mushRoom.angle >= 27.71f && m_mushRoom.angle <= 28.7f)
	{
		enemyBeforeDirection = ENEMY_LEFT;
	}
	if (30.7f >= m_mushRoom.angle && m_mushRoom.angle >= 28.71f)
	{
		enemyBeforeDirection = ENEMY_DOWN;
	}
	if (31.89f >= m_mushRoom.angle && m_mushRoom.angle >= 30.71f)
	{	//현재 수정
		enemyBeforeDirection = ENEMY_RIGHT;
	}
	if (m_mushRoom.angle >= 31.9f && m_mushRoom.angle <= 34.f)
	{
		enemyBeforeDirection = ENEMY_UP;
	}
	if (m_mushRoom.angle >= 34.1f && m_mushRoom.angle <= 35.4f)
	{
		enemyBeforeDirection = ENEMY_LEFT;
	}
	if (37.0f >= m_mushRoom.angle && m_mushRoom.angle >= 35.41f)
	{
		enemyBeforeDirection = ENEMY_DOWN;
	}
	if (38.3f >= m_mushRoom.angle && m_mushRoom.angle >= 37.1f)
	{	//현재 수정
		enemyBeforeDirection = ENEMY_RIGHT;
	}
	if (m_mushRoom.angle >= 40.1f && m_mushRoom.angle <= 38.31f)
	{
		enemyBeforeDirection = ENEMY_UP;
	}

	// 마이너스 한바퀴
	if (m_mushRoom.angle >= -5.8f && m_mushRoom.angle <= -3.91f)
	{
		enemyBeforeDirection = ENEMY_UP;
	}
	if (-0.681f >= m_mushRoom.angle && m_mushRoom.angle >= -2.7f)
	{
		enemyBeforeDirection = ENEMY_DOWN;
	}
	if (-2.69f >= m_mushRoom.angle && m_mushRoom.angle >= -3.7f)
	{
		enemyBeforeDirection = ENEMY_LEFT;
	}
	if (0.4f >= m_mushRoom.angle && m_mushRoom.angle >= -0.68f)
	{
		enemyBeforeDirection = ENEMY_RIGHT;
	}
	// 마이너스 두바퀴
	if (m_mushRoom.angle >= -5.5f && m_mushRoom.angle <= -3.71f)
	{
		enemyBeforeDirection = ENEMY_UP;
	} 
	if ( -6.91f >= m_mushRoom.angle && m_mushRoom.angle >= -8.49f)
	{
		enemyBeforeDirection = ENEMY_DOWN;
	}
	if (m_mushRoom.angle >= -9.95f && m_mushRoom.angle <= -8.5f )
	{
		enemyBeforeDirection = ENEMY_LEFT;
	}
	if (-5.51f >= m_mushRoom.angle && m_mushRoom.angle >= -6.9f)
	{
		enemyBeforeDirection = ENEMY_RIGHT;
	}
	// 마이너스 세바퀴
	if (m_mushRoom.angle >= -11.99f && m_mushRoom.angle <= -9.96f)
	{
		enemyBeforeDirection = ENEMY_UP;
	}
	if (-13.51f >= m_mushRoom.angle && m_mushRoom.angle >= -15.0f)
	{
		enemyBeforeDirection = ENEMY_DOWN;
	}
	if (m_mushRoom.angle >= -16.21f && m_mushRoom.angle <=  -15.01f)
	{
		enemyBeforeDirection = ENEMY_LEFT;
	}
	if (-12.00f >= m_mushRoom.angle && m_mushRoom.angle >= -13.5f)
	{
		enemyBeforeDirection = ENEMY_RIGHT;
	}
	// 마이너스 네바퀴
	if (m_mushRoom.angle >= -18.1f && m_mushRoom.angle <= -16.22f )
	{  
		enemyBeforeDirection = ENEMY_UP;
	}
	if (-19.35f >= m_mushRoom.angle && m_mushRoom.angle >= -21.1f)
	{
		enemyBeforeDirection = ENEMY_DOWN;
	}
	if (-21.2f >= m_mushRoom.angle && m_mushRoom.angle >= -22.6f)
	{
		enemyBeforeDirection = ENEMY_LEFT;
	}
	if (m_mushRoom.angle >= -19.349f && m_mushRoom.angle <= -18.11f)
	{
		enemyBeforeDirection = ENEMY_RIGHT;
	}
	if (m_mushRoom.angle >= -24.4f  && m_mushRoom.angle <= -22.61f)
	{
		enemyBeforeDirection = ENEMY_UP;
	}
	if (m_mushRoom.angle >= -25.7f  && m_mushRoom.angle <= -24.41f)
	{
		enemyBeforeDirection = ENEMY_RIGHT;
	}
	if (m_mushRoom.angle >= -27.8f  && m_mushRoom.angle <= -25.71f)
	{
		enemyBeforeDirection = ENEMY_DOWN;
	}

}

