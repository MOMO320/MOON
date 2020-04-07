#include "stdafx.h"
#include "enemies.h"
#include "gameTypes.h"

enemies::enemies()
{
}

enemies::~enemies()
{
}

void enemies::enemyMove(enemy _enemy, dungeonMap* _dunMap, ENEMYDIRECTION _enemyDirect ,int _speed)
{
	int tileIndex[2];	// 검사용 타일

	rcCollision = _enemy._rc;	// 가상의 충돌용 RECT

	_x = rcCollision.left;
	_y = rcCollision.top;

	RECT enemyRect;

	//타임매니저를 이용한 방법 elpasedTime은 항상(0.0166667011)이다.
	float elpasedTime = TIMEMANAGER->getElapsedTime();
	//그래서 moveSpeed는 계속 약 1.6666 정도의 속도가 나온다.)
	float moveSpeed = elpasedTime * _speed;
	// 캐릭터의 방향에 따른 이동
	switch (_enemyDirect)
	{
	case ENEMY_LEFT:
		_x -= moveSpeed;

		rcCollision = RectMake(_x, _y, _enemy.m_img->getFrameWidth() -50, _enemy.m_img->getFrameHeight() - 50);
		break;

	case ENEMY_UP:
		_y -= moveSpeed;
		rcCollision = RectMake(_x, _y, _enemy.m_img->getFrameWidth() - 50, _enemy.m_img->getFrameHeight() - 50);
		break;

	case ENEMY_RIGHT:
		_x += moveSpeed;
		rcCollision = RectMake(_x, _y, _enemy.m_img->getFrameWidth() + 50, _enemy.m_img->getFrameHeight() - 50);
		break;

	case ENEMY_DOWN:
		_y += moveSpeed;
		rcCollision = RectMake(_x, _y, _enemy.m_img->getFrameWidth() - 50, _enemy.m_img->getFrameHeight() - 50);
		break;

	default:
		break;
	}

	m_tileX = rcCollision.left / OBJ_TILESIZE; // 확인해봐야함
	m_tileY = rcCollision.top / OBJ_TILESIZE;

	switch (_enemyDirect)
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

	case PLAYER_DOWN:
		tileIndex[0] = (m_tileX + m_tileY * BACKTILEX) + BACKTILEX;
		tileIndex[1] = (m_tileX + 1 + m_tileY * BACKTILEX) + BACKTILEX;
		break;
	}

	for (int i = 0; i < 2; i++)
	{
		RECT rc;
		// 타일의 속성이 움직이지 못하는 곳이면...
		if ((_dunMap->getAttribute()[tileIndex[i]] == ATTR_UNMOVEABLE) &&
			IntersectRect(&rc, &_dunMap->getMap()[tileIndex[i]].m_rc, &rcCollision))
		{
			//움직이려 할때 갈 수 없는 지역이면 탱크의 움직임을 고정하자
			// ex) 플레이어가 왼쪽으로 갈때 왼쪽지역이 갈 수 없으면
			switch (_enemyDirect)
			{
			case PLAYER_LEFT:
				enemyRect.left = _dunMap->getMap()[tileIndex[i]].m_rc.right;
				enemyRect.right = enemyRect.left + _enemy.m_img->getFrameWidth();
				_x = enemyRect.left + (enemyRect.right - enemyRect.left) / 2;
				isObjectConnect = true;
				break;

			case PLAYER_RIGHT:
				enemyRect.right = _dunMap->getMap()[tileIndex[i]].m_rc.left;
				enemyRect.left = enemyRect.right - _enemy.m_img->getFrameWidth();
				_x = enemyRect.left + (enemyRect.right - enemyRect.left) / 2;
				isObjectConnect = true;
				break;

			case PLAYER_UP:
				enemyRect.top = _dunMap->getMap()[tileIndex[i]].m_rc.bottom;
				enemyRect.bottom = enemyRect.top + _enemy.m_img->getFrameHeight();
				_y = enemyRect.top + (enemyRect.bottom - enemyRect.top) / 2;
				isObjectConnect = true;
				break;

			case PLAYER_DOWN:
				enemyRect.bottom = _dunMap->getMap()[tileIndex[i]].m_rc.top;
				enemyRect.top = enemyRect.bottom - _enemy.m_img->getFrameHeight();
				_y = enemyRect.top + (enemyRect.bottom - enemyRect.top) / 2;
				isObjectConnect = true;
				break;
			}
			return;
		}
		//여기에 산성을 밟으면 player의 체력이 떨어지는 효과 넣어야 함. 
		// !! 아직 안 넣음 !!
	} // end of for
	// 이제 움직여주자
	rcCollision = RectMake(_x, _y, _enemy.m_img->getFrameWidth()- 50, _enemy.m_img->getFrameHeight()- 50);
	_enemy._rc = rcCollision;
	setRect(_enemy._rc);
}
