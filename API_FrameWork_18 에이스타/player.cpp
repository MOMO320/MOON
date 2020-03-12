#include "stdafx.h"
#include "player.h"

player::player()
	:m_playerInPlace(RectMakeCenter(WINSIZEX / 2 + 5, 360, WINSIZEX - 300, WINSIZEY / 2 + 180))
{
}

player::~player()
{
}

HRESULT player::init()
{
	// character 기본 설정
	m_playerDirect = PLAYER_UP;
	m_speed = 300.0f;
	return S_OK;
}

void player::release()
{

}

void player::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > m_playerInPlace.left)
	{
		characterMove();
		m_playerDirect = PLAYER_LEFT;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < m_playerInPlace.right)
	{
		characterMove();
		m_playerDirect = PLAYER_RIGHT;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > m_playerInPlace.top)
	{
		characterMove();
		m_playerDirect = PLAYER_UP;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < m_playerInPlace.bottom)
	{
		characterMove();
		m_playerDirect = PLAYER_DOWN;
	}
}

void player::render()
{
	//AlphaRectangle(getMemDC(), m_playerInPlace.left, m_playerInPlace.top, m_playerInPlace.right, m_playerInPlace.bottom);
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}
// 캐릭터 위치에 1/2 만한 RECT 생성
void player::setCharacPosition(RECT rc)
{
	_rc = rc;
	m_x = _rc.left + (_rc.right - _rc.left) / 2;
	m_y = _rc.top + (_rc.bottom - _rc.top) / 2;
}

void player::characterMove()
{
	RECT rcCollision;
	int tileIndex[2];	// 검사용 타일

	rcCollision = _rc;	// 가상의 충돌용 RECT

	//타임매니저를 이용한 방법 elpasedTime은 항상(0.0166667011)이다.
	float elpasedTime = TIMEMANAGER->getElapsedTime(); 
	//그래서 moveSpeed는 계속 약 1.6666 정도의 속도가 나온다.)
	float moveSpeed = elpasedTime * m_speed; 

	// 캐릭터의 방향에 따른 이동
	switch (m_playerDirect)
	{
	case PLAYER_LEFT:
		m_x -= moveSpeed;
		rcCollision = RectMakeCenter(m_x, m_y, 60, 60);
		break;

	case PLAYER_UP:
		m_y -= moveSpeed;
		rcCollision = RectMakeCenter(m_x, m_y, 60, 60);
		break;

	case PLAYER_RIGHT:
		m_x += moveSpeed;
		rcCollision = RectMakeCenter(m_x, m_y, 60, 60);
		break;

	case PLAYER_DOWN :
		m_y += moveSpeed;
		rcCollision = RectMakeCenter(m_x, m_y, 60, 60);
		break;

	default:
		break;
	}

	m_tileX = rcCollision.left / OBJ_TILESIZE;
	m_tileY = rcCollision.top / OBJ_TILESIZE;

	switch (m_playerDirect)
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
		if ((m_dunMap1->getAttribute()[tileIndex[i]] == ATTR_UNMOVEABLE) &&
			IntersectRect(&rc, &m_dunMap1->getMap()[tileIndex[i]].m_rc, &rcCollision))
		{
			//움직이려 할때 갈 수 없는 지역이면 탱크의 움직임을 고정하자
			// ex) 플레이어가 왼쪽으로 갈때 왼쪽지역이 갈 수 없으면
			switch (m_playerDirect)
			{
			case PLAYER_LEFT:
				_rc.left = m_dunMap1->getMap()[tileIndex[i]].m_rc.right;
				_rc.right = _rc.left + 60;
				m_x = _rc.left + (_rc.right - _rc.left) / 2;
				break;

			case PLAYER_RIGHT:
				_rc.right = m_dunMap1->getMap()[tileIndex[i]].m_rc.left;
				_rc.left = _rc.right - 60;
				m_x = _rc.left + (_rc.right - _rc.left) / 2;
				break;

			case PLAYER_UP:
				_rc.top = m_dunMap1->getMap()[tileIndex[i]].m_rc.bottom;
				_rc.bottom  = _rc.top + 60;
				m_y = _rc.top + (_rc.bottom - rc.top) / 2;
				break;

			case PLAYER_DOWN:
				_rc.bottom = m_dunMap1->getMap()[tileIndex[i]].m_rc.top;
				_rc.top = _rc.bottom - 60;
				m_y = _rc.top + (_rc.bottom - _rc.top) / 2;
				break;
			}
			return;
		}
		//여기에 산성을 밟으면 player의 체력이 떨어지는 효과 넣어야 함. 
		// !! 아직 안 넣음 !!
	} // end of for
	// 이제 움직여주자
	rcCollision = RectMakeCenter(m_x, m_y, 60, 60);
	_rc = rcCollision;
}




