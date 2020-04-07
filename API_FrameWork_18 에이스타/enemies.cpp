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
	int tileIndex[2];	// �˻�� Ÿ��

	rcCollision = _enemy._rc;	// ������ �浹�� RECT

	_x = rcCollision.left;
	_y = rcCollision.top;

	RECT enemyRect;

	//Ÿ�ӸŴ����� �̿��� ��� elpasedTime�� �׻�(0.0166667011)�̴�.
	float elpasedTime = TIMEMANAGER->getElapsedTime();
	//�׷��� moveSpeed�� ��� �� 1.6666 ������ �ӵ��� ���´�.)
	float moveSpeed = elpasedTime * _speed;
	// ĳ������ ���⿡ ���� �̵�
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

	m_tileX = rcCollision.left / OBJ_TILESIZE; // Ȯ���غ�����
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
		// Ÿ���� �Ӽ��� �������� ���ϴ� ���̸�...
		if ((_dunMap->getAttribute()[tileIndex[i]] == ATTR_UNMOVEABLE) &&
			IntersectRect(&rc, &_dunMap->getMap()[tileIndex[i]].m_rc, &rcCollision))
		{
			//�����̷� �Ҷ� �� �� ���� �����̸� ��ũ�� �������� ��������
			// ex) �÷��̾ �������� ���� ���������� �� �� ������
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
		//���⿡ �꼺�� ������ player�� ü���� �������� ȿ�� �־�� ��. 
		// !! ���� �� ���� !!
	} // end of for
	// ���� ����������
	rcCollision = RectMake(_x, _y, _enemy.m_img->getFrameWidth()- 50, _enemy.m_img->getFrameHeight()- 50);
	_enemy._rc = rcCollision;
	setRect(_enemy._rc);
}
