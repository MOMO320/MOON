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
	// character �⺻ ����
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
// ĳ���� ��ġ�� 1/2 ���� RECT ����
void player::setCharacPosition(RECT rc)
{
	_rc = rc;
	m_x = _rc.left + (_rc.right - _rc.left) / 2;
	m_y = _rc.top + (_rc.bottom - _rc.top) / 2;
}

void player::characterMove()
{
	RECT rcCollision;
	int tileIndex[2];	// �˻�� Ÿ��

	rcCollision = _rc;	// ������ �浹�� RECT

	//Ÿ�ӸŴ����� �̿��� ��� elpasedTime�� �׻�(0.0166667011)�̴�.
	float elpasedTime = TIMEMANAGER->getElapsedTime(); 
	//�׷��� moveSpeed�� ��� �� 1.6666 ������ �ӵ��� ���´�.)
	float moveSpeed = elpasedTime * m_speed; 

	// ĳ������ ���⿡ ���� �̵�
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
		// Ÿ���� �Ӽ��� �������� ���ϴ� ���̸�...
		if ((m_dunMap1->getAttribute()[tileIndex[i]] == ATTR_UNMOVEABLE) &&
			IntersectRect(&rc, &m_dunMap1->getMap()[tileIndex[i]].m_rc, &rcCollision))
		{
			//�����̷� �Ҷ� �� �� ���� �����̸� ��ũ�� �������� ��������
			// ex) �÷��̾ �������� ���� ���������� �� �� ������
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
		//���⿡ �꼺�� ������ player�� ü���� �������� ȿ�� �־�� ��. 
		// !! ���� �� ���� !!
	} // end of for
	// ���� ����������
	rcCollision = RectMakeCenter(m_x, m_y, 60, 60);
	_rc = rcCollision;
}




