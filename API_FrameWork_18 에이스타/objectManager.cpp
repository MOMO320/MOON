#include "stdafx.h"
#include "objectManager.h"
#include "gameTypes.h"

objectManager::objectManager()
{
}

objectManager::~objectManager()
{
}

HRESULT objectManager::init()
{
	m_isConnect = false;
	return S_OK;
}

void objectManager::release()
{
}

void objectManager::update(THROWOBJECTINFO _object, RECT _rc)
{
	_object.m_rc = _rc;
	_object.m_x  = _rc.left;
	_object.m_y  = _rc.top;
}

void objectManager::update(RECT _playerRc, RECT _enemyRc, int _objectSpeed)
{
	if (_playerRc.left <= _enemyRc.left)
	{
		_playerDirect = PLAYER_LEFT;
	}
	else if (_enemyRc.right <= _playerRc.right)
	{
		_playerDirect = PLAYER_RIGHT;
	}
}

void objectManager::render()
{
}
void objectManager::setObjPosition(THROWOBJECTINFO _object, RECT _rc)
{
	_object.m_x = _rc.left + (_rc.right - _rc.left) / 2;
	_object.m_y = _rc.top + (_rc.bottom - _rc.top) / 2;

	SetRect(&_object.m_rc, _object.m_x, _object.m_y,
		_object.m_x + _object.m_img->getWidth(),
		_object.m_y + _object.m_img->getHeight());

	// 넘겨줄 값
	temp = _object.m_rc;

}

void objectManager::objectMove(THROWOBJECTINFO _object, dungeonMap * _dunMap, PLAYERDIRECTION _direction)
{
	int tileIndex[2];
	rcCollision = _object.m_mainRc;

	switch (_direction)
	{
	case PLAYER_LEFT:
		_object.m_x -= OBJECTSPEED;
		rcCollision = RectMake(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;

	case PLAYER_UP:
		_object.m_y -= OBJECTSPEED;
		rcCollision = RectMake(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;

	case PLAYER_RIGHT:
		_object.m_x += OBJECTSPEED;
		rcCollision = RectMake(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;

	case PLAYER_DOWN:
		_object.m_y += OBJECTSPEED;
		rcCollision = RectMake(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;
	}

	m_tileX = rcCollision.left / OBJ_TILESIZE;
	m_tileY = rcCollision.top / OBJ_TILESIZE;

	switch (_direction)
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

		if ((_dunMap->getAttribute()[tileIndex[i]] == ATTR_UNMOVEABLE) &&
			IntersectRect(&rc, &_dunMap->getMap()[tileIndex[i]].m_rc, &rcCollision))
		{
			switch (_direction)
			{
			case PLAYER_LEFT:
				_object.m_mainRc.left = _dunMap->getMap()[tileIndex[i]].m_rc.right;
				_object.m_mainRc.right = _object.m_mainRc.left + _object.m_img->getWidth();
				_object.m_x = _object.m_mainRc.left + (_object.m_mainRc.right - _object.m_mainRc.left) / 2;
				m_isConnect = true;
				break;

			case PLAYER_RIGHT:
				_object.m_mainRc.right = _dunMap->getMap()[tileIndex[i]].m_rc.left;
				_object.m_mainRc.left = _object.m_mainRc.right - _object.m_img->getWidth();
				_object.m_x = _object.m_mainRc.left + (_object.m_mainRc.right - _object.m_mainRc.left) / 2;
				m_isConnect = true;
				break;

			case PLAYER_UP:
				_object.m_mainRc.top = _dunMap->getMap()[tileIndex[i]].m_rc.bottom;
				_object.m_mainRc.bottom = _object.m_mainRc.top + _object.m_img->getHeight();
				_object.m_y = _object.m_mainRc.top + (_object.m_mainRc.bottom - _object.m_mainRc.top) / 2;
				m_isConnect = true;
				break;

			case PLAYER_DOWN:
				_object.m_mainRc.bottom = _dunMap->getMap()[tileIndex[i]].m_rc.top;
				_object.m_mainRc.top = _object.m_mainRc.bottom - _object.m_img->getHeight();
				_object.m_y = _object.m_mainRc.top + (_object.m_mainRc.bottom - _object.m_mainRc.top) / 2;
				m_isConnect = true;
				break;
			}
			return;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		RECT rc;
		if (_dunMap->getCollisionWAll()[i].obj == OBJ_DONGO &&
			IntersectRect(&rc, &_dunMap->getCollisionWAll()[i].rc, &rcCollision))
		{
			switch (_direction)
			{
			case PLAYER_LEFT:
				_object.m_mainRc.left = _dunMap->getMap()[tileIndex[i]].m_rc.right;
				_object.m_mainRc.right = _object.m_mainRc.left + _object.m_img->getWidth();
				_object.m_x = _object.m_mainRc.left + (_object.m_mainRc.right - _object.m_mainRc.left) / 2;
				m_isConnect = true;
				break;

			case PLAYER_RIGHT:
				_object.m_mainRc.right = _dunMap->getMap()[tileIndex[i]].m_rc.left;
				_object.m_mainRc.left = _object.m_mainRc.right - _object.m_img->getWidth();
				_object.m_x = _object.m_mainRc.left + (_object.m_mainRc.right - _object.m_mainRc.left) / 2;
				m_isConnect = true;
				break;

			case PLAYER_UP:
				_object.m_mainRc.top = _dunMap->getMap()[tileIndex[i]].m_rc.bottom;
				_object.m_mainRc.bottom = _object.m_mainRc.top + _object.m_img->getHeight();
				_object.m_y = _object.m_mainRc.top + (_object.m_mainRc.bottom - _object.m_mainRc.top) / 2;
				m_isConnect = true;
				break;

			case PLAYER_DOWN:
				_object.m_mainRc.bottom = _dunMap->getMap()[tileIndex[i]].m_rc.top;
				_object.m_mainRc.top = _object.m_mainRc.bottom - _object.m_img->getHeight();
				_object.m_y = _object.m_mainRc.top + (_object.m_mainRc.bottom - _object.m_mainRc.top) / 2;
				m_isConnect = true;
				break;
			}
			return;
		}
	}
	rcCollision = RectMake(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
	m_x = _object.m_x;
	m_y = _object.m_y;
	_object.m_mainRc = rcCollision;
}

void objectManager::objectMove(THROWOBJECTINFO _object, dungeonMap * _dunMap, ENEMYDIRECTION _direction ,int speed)
{
	int tileIndex[2];
	rcCollision = _object.m_mainRc;

	//_object.m_x = _object.m_mainRc.left;
	//_//object.m_y = _object.m_mainRc.top;

	switch (_direction)
	{
	case ENEMY_LEFT:
		_object.m_x -= speed;
		rcCollision = RectMake(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;

	case ENEMY_UP:
		_object.m_y -= speed;
		rcCollision = RectMake(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;

	case ENEMY_RIGHT:
		_object.m_x += speed;
		rcCollision = RectMake(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;

	case ENEMY_DOWN:
		_object.m_y += speed;
		rcCollision = RectMake(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;
	}

	m_tileX = rcCollision.left / OBJ_TILESIZE;
	m_tileY = rcCollision.top / OBJ_TILESIZE;

	switch (_direction)
	{
	case  ENEMY_LEFT:
		tileIndex[0] = m_tileX + m_tileY * BACKTILEX;
		tileIndex[1] = m_tileX + (m_tileY + 1) * BACKTILEX;
		break;

	case ENEMY_RIGHT:
		tileIndex[0] = (m_tileX + m_tileY * BACKTILEX) + 1;
		tileIndex[1] = (m_tileX + (m_tileY + 1) * BACKTILEX) + 1;
		break;

	case ENEMY_UP:
		tileIndex[0] = m_tileX + m_tileY * BACKTILEX;
		tileIndex[1] = m_tileX + 1 + m_tileY * BACKTILEX;
		break;

	case ENEMY_DOWN:
		tileIndex[0] = (m_tileX + m_tileY * BACKTILEX) + BACKTILEX;
		tileIndex[1] = (m_tileX + 1 + m_tileY * BACKTILEX) + BACKTILEX;
		break;
	}

	for (int i = 0; i < 2; i++)
	{
		RECT rc;

		if ((_dunMap->getAttribute()[tileIndex[i]] == ATTR_UNMOVEABLE) &&
			IntersectRect(&rc, &_dunMap->getMap()[tileIndex[i]].m_rc, &rcCollision))
		{
			switch (_direction)
			{
			case ENEMY_LEFT:
				_object.m_mainRc.left = _dunMap->getMap()[tileIndex[i]].m_rc.right;
				_object.m_mainRc.right = _object.m_mainRc.left + _object.m_img->getWidth();
				_object.m_x = _object.m_mainRc.left + (_object.m_mainRc.right - _object.m_mainRc.left) / 2;
				m_isConnect = true;
				break;

			case ENEMY_RIGHT:
				_object.m_mainRc.right = _dunMap->getMap()[tileIndex[i]].m_rc.left;
				_object.m_mainRc.left = _object.m_mainRc.right - _object.m_img->getWidth();
				_object.m_x = _object.m_mainRc.left + (_object.m_mainRc.right - _object.m_mainRc.left) / 2;
				m_isConnect = true;
				break;

			case ENEMY_UP:
				_object.m_mainRc.top = _dunMap->getMap()[tileIndex[i]].m_rc.bottom;
				_object.m_mainRc.bottom = _object.m_mainRc.top + _object.m_img->getHeight();
				_object.m_y = _object.m_mainRc.top + (_object.m_mainRc.bottom - _object.m_mainRc.top) / 2;
				m_isConnect = true;
				break;

			case ENEMY_DOWN:
				_object.m_mainRc.bottom = _dunMap->getMap()[tileIndex[i]].m_rc.top;
				_object.m_mainRc.top = _object.m_mainRc.bottom - _object.m_img->getHeight();
				_object.m_y = _object.m_mainRc.top + (_object.m_mainRc.bottom - _object.m_mainRc.top) / 2;
				m_isConnect = true;
				break;
			}
			return;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		RECT rc;
		if (_dunMap->getCollisionWAll()[i].obj == OBJ_DONGO &&
			IntersectRect(&rc, &_dunMap->getCollisionWAll()[i].rc, &rcCollision))
		{
			switch (_direction)
			{
			case ENEMY_LEFT:
				_object.m_mainRc.left = _dunMap->getMap()[tileIndex[i]].m_rc.right;
				_object.m_mainRc.right = _object.m_mainRc.left + _object.m_img->getWidth();
				_object.m_x = _object.m_mainRc.left + (_object.m_mainRc.right - _object.m_mainRc.left) / 2;
				m_isConnect = true;
				break;

			case ENEMY_RIGHT:
				_object.m_mainRc.right = _dunMap->getMap()[tileIndex[i]].m_rc.left;
				_object.m_mainRc.left = _object.m_mainRc.right - _object.m_img->getWidth();
				_object.m_x = _object.m_mainRc.left + (_object.m_mainRc.right - _object.m_mainRc.left) / 2;
				m_isConnect = true;
				break;

			case ENEMY_UP:
				_object.m_mainRc.top = _dunMap->getMap()[tileIndex[i]].m_rc.bottom;
				_object.m_mainRc.bottom = _object.m_mainRc.top + _object.m_img->getHeight();
				_object.m_y = _object.m_mainRc.top + (_object.m_mainRc.bottom - _object.m_mainRc.top) / 2;
				m_isConnect = true;
				break;

			case PLAYER_DOWN:
				_object.m_mainRc.bottom = _dunMap->getMap()[tileIndex[i]].m_rc.top;
				_object.m_mainRc.top = _object.m_mainRc.bottom - _object.m_img->getHeight();
				_object.m_y = _object.m_mainRc.top + (_object.m_mainRc.bottom - _object.m_mainRc.top) / 2;
				m_isConnect = true;
				break;
			}
			return;
		}
	}
	rcCollision = RectMake(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
	m_x = _object.m_x;
	m_y = _object.m_y;
	_object.m_mainRc = rcCollision;
}

void objectManager::obectFollowMove(THROWOBJECTINFO _object, dungeonMap * _dunMap, int speed)
{
	int tileIndex[2];
	rcCollision = _object.m_mainRc;

	//_object.m_x = _object.m_mainRc.left;
	//_//object.m_y = _object.m_mainRc.top;

	switch (_enemyObjectDirect)
	{
	case DIRECTION_LEFT:
		_object.m_x -= speed;
		rcCollision = RectMakeCenter(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;

	case DIRECTION_UP:
		_object.m_y -= speed;
		rcCollision = RectMakeCenter(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;

	case DIRECTION_RIGHT:
		_object.m_x += speed;
		rcCollision = RectMakeCenter(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;

	case DIRECTION_DOWN:
		_object.m_y += speed;
		rcCollision = RectMakeCenter(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;
		
	case DIRECTION_LEFTUP:
		_object.m_x -= speed;
		_object.m_y -= speed;
		rcCollision = RectMakeCenter(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;

	case DIRECTION_RIGHTDOWN:
		_object.m_x += speed;
		_object.m_y += speed;
		rcCollision = RectMakeCenter(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;

	case DIRECTION_LEFTDOWN:
		_object.m_x -= speed;
		_object.m_y += speed;
		rcCollision = RectMakeCenter(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;

	case DIRECTION_RIGHTUP:
		_object.m_x += speed;
		_object.m_y -= speed;
		rcCollision = RectMakeCenter(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
		break;
	}

	m_tileX = rcCollision.left / OBJ_TILESIZE;
	m_tileY = rcCollision.top / OBJ_TILESIZE;

	switch (_enemyObjectDirect)
	{
	case  DIRECTION_LEFT:
		tileIndex[0] = m_tileX + m_tileY * BACKTILEX;
		tileIndex[1] = m_tileX + (m_tileY + 1) * BACKTILEX;
		break;

	case DIRECTION_RIGHT:
		tileIndex[0] = (m_tileX + m_tileY * BACKTILEX) + 1;
		tileIndex[1] = (m_tileX + (m_tileY + 1) * BACKTILEX) + 1;
		break;

	case DIRECTION_UP:
		tileIndex[0] = m_tileX + m_tileY * BACKTILEX;
		tileIndex[1] = m_tileX + 1 + m_tileY * BACKTILEX;
		break;

	case DIRECTION_DOWN:
		tileIndex[0] = (m_tileX + m_tileY * BACKTILEX) + BACKTILEX;
		tileIndex[1] = (m_tileX + 1 + m_tileY * BACKTILEX) + BACKTILEX;
		break;

	case DIRECTION_LEFTUP:
		tileIndex[0] = m_tileX + m_tileY * BACKTILEX;
		tileIndex[1] = m_tileX + (m_tileY + 1) * BACKTILEX;
		break;

	case DIRECTION_RIGHTDOWN:
		tileIndex[0] = (m_tileX + (m_tileY + 1)* BACKTILEX) + 1;
		tileIndex[1] = (m_tileX + (m_tileY + 2) * BACKTILEX) + 1;
		break;

	case DIRECTION_LEFTDOWN :
		tileIndex[0] = m_tileX + (m_tileY + 1) * BACKTILEX;
		tileIndex[1] = m_tileX + (m_tileY + 2) * BACKTILEX;
		break;

	case DIRECTION_RIGHTUP:
		tileIndex[0] = (m_tileX + m_tileY * BACKTILEX) + 1;
		tileIndex[1] = (m_tileX + (m_tileY + 1) * BACKTILEX) + 1;
		break;
	}

	for (int i = 0; i < 2; i++)
	{
		RECT rc;

		if ((_dunMap->getAttribute()[tileIndex[i]] == ATTR_UNMOVEABLE) &&
			IntersectRect(&rc, &_dunMap->getMap()[tileIndex[i]].m_rc, &rcCollision))
		{
			switch (_enemyObjectDirect)
			{
			case DIRECTION_LEFT:
				_object.m_rc.left = _dunMap->getMap()[tileIndex[i]].m_rc.right;
				_object.m_rc.right = _object.m_rc.left + _object.m_img->getWidth();
				_object.m_x = _object.m_rc.left + (_object.m_rc.right - _object.m_rc.left) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_RIGHT:
				_object.m_rc.right = _dunMap->getMap()[tileIndex[i]].m_rc.left;
				_object.m_rc.left = _object.m_rc.right - _object.m_img->getWidth();
				_object.m_x = _object.m_rc.left + (_object.m_rc.right - _object.m_rc.left) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_UP:
				_object.m_rc.top = _dunMap->getMap()[tileIndex[i]].m_rc.bottom;
				_object.m_rc.bottom = _object.m_rc.top + _object.m_img->getHeight();
				_object.m_y = _object.m_rc.top + (_object.m_rc.bottom - _object.m_rc.top) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_DOWN:
				_object.m_rc.bottom = _dunMap->getMap()[tileIndex[i]].m_rc.top;
				_object.m_rc.top = _object.m_rc.bottom - _object.m_img->getHeight();
				_object.m_y = _object.m_rc.top + (_object.m_rc.bottom - _object.m_rc.top) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_LEFTUP:
				_object.m_rc.left = _dunMap->getMap()[tileIndex[i]].m_rc.right;
				_object.m_rc.right = _object.m_rc.left + _object.m_img->getWidth();
				_object.m_x = _object.m_rc.left + (_object.m_rc.right - _object.m_rc.left) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_RIGHTDOWN:
				_object.m_rc.right = _dunMap->getMap()[tileIndex[i]].m_rc.left;
				_object.m_rc.left = _object.m_rc.right - _object.m_img->getWidth();
				_object.m_x = _object.m_rc.left + (_object.m_rc.right - _object.m_rc.left) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_LEFTDOWN:
				_object.m_rc.left = _dunMap->getMap()[tileIndex[i]].m_rc.right;
				_object.m_rc.right = _object.m_rc.left + _object.m_img->getWidth();
				_object.m_x = _object.m_rc.left + (_object.m_rc.right - _object.m_rc.left) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_RIGHTUP :
				_object.m_rc.right = _dunMap->getMap()[tileIndex[i]].m_rc.left;
				_object.m_rc.left = _object.m_rc.right - _object.m_img->getWidth();
				_object.m_x = _object.m_rc.left + (_object.m_rc.right - _object.m_rc.left) / 2;
				m_isConnect = true;
				break;
			}
			rcCollision = RectMakeCenter(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
			m_x = _object.m_x;
			m_y = _object.m_y;
			_object.m_rc = rcCollision;
			return;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		RECT rc;
		if (_dunMap->getCollisionWAll()[i].obj == OBJ_DONGO &&
			IntersectRect(&rc, &_dunMap->getCollisionWAll()[i].rc, &rcCollision))
		{
			switch (_enemyObjectDirect)
			{
			case DIRECTION_LEFT:
				_object.m_rc.left = _dunMap->getMap()[tileIndex[i]].m_rc.right;
				_object.m_rc.right = _object.m_mainRc.left + _object.m_img->getWidth();
				_object.m_x = _object.m_rc.left + (_object.m_rc.right - _object.m_rc.left) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_RIGHT:
				_object.m_rc.right = _dunMap->getMap()[tileIndex[i]].m_rc.left;
				_object.m_rc.left = _object.m_rc.right - _object.m_img->getWidth();
				_object.m_x = _object.m_rc.left + (_object.m_rc.right - _object.m_rc.left) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_UP:
				_object.m_rc.top = _dunMap->getMap()[tileIndex[i]].m_rc.bottom;
				_object.m_rc.bottom = _object.m_rc.top + _object.m_img->getHeight();
				_object.m_y = _object.m_rc.top + (_object.m_rc.bottom - _object.m_rc.top) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_DOWN:
				_object.m_rc.bottom = _dunMap->getMap()[tileIndex[i]].m_rc.top;
				_object.m_rc.top = _object.m_rc.bottom - _object.m_img->getHeight();
				_object.m_y = _object.m_rc.top + (_object.m_rc.bottom - _object.m_rc.top) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_LEFTUP:
				_object.m_rc.left = _dunMap->getMap()[tileIndex[i]].m_rc.right;
				_object.m_rc.right = _object.m_rc.left + _object.m_img->getWidth();
				_object.m_x = _object.m_rc.left + (_object.m_rc.right - _object.m_rc.left) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_RIGHTDOWN:
				_object.m_rc.right = _dunMap->getMap()[tileIndex[i]].m_rc.left;
				_object.m_rc.left = _object.m_rc.right - _object.m_img->getWidth();
				_object.m_x = _object.m_rc.left + (_object.m_rc.right - _object.m_rc.left) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_LEFTDOWN:
				_object.m_rc.left = _dunMap->getMap()[tileIndex[i]].m_rc.right;
				_object.m_rc.right = _object.m_rc.left + _object.m_img->getWidth();
				_object.m_x = _object.m_rc.left + (_object.m_rc.right - _object.m_rc.left) / 2;
				m_isConnect = true;
				break;

			case DIRECTION_RIGHTUP:
				_object.m_rc.right = _dunMap->getMap()[tileIndex[i]].m_rc.left;
				_object.m_rc.left = _object.m_rc.right - _object.m_img->getWidth();
				_object.m_x = _object.m_rc.left + (_object.m_rc.right - _object.m_rc.left) / 2;
				m_isConnect = true;
				break;
			}
			rcCollision = RectMakeCenter(_object.m_x, _object.m_y, _object.m_img->getWidth(), _object.m_img->getHeight());
			m_x = _object.m_x;
			m_y = _object.m_y;
			_object.m_rc = rcCollision;
			return;
		}

	}

}

void objectManager::objectDirect(RECT _enemyRc,THROWOBJECTINFO _object, dungeonMap * _dunMap,RECT _playerRc ,int _objectSpeed)
{
	float time = TIMEMANAGER->getElapsedTime();

	pastTime += time;
	// 좌 우 방향 //
	if (_enemyRc.left - _playerRc.left > _objectSpeed && !m_isDongo) // 플레이어가 왼쪽이라는 전제
	{
		if (_enemyRc.top - (_playerRc.top - 60) > 10)	// 플레이어가 위쪽에 있단 전제
		{
			_enemyObjectDirect = DIRECTION_LEFTUP;
			if (addDeley < pastTime)
			{
				pastTime = 0;
				//obectFollowMove(_object, _dunMap, _objectSpeed);
				OffsetRect(&_object.m_rc, -_objectSpeed, -_objectSpeed);
			}
		}
		if (_playerRc.bottom - _enemyRc.bottom > 100)
		{
			_enemyObjectDirect = DIRECTION_LEFTDOWN;
			if (addDeley < pastTime)
			{
				pastTime = 0;
				OffsetRect(&_object.m_rc, -_objectSpeed, +_objectSpeed);
				//obectFollowMove(_object, _dunMap, _objectSpeed);
			}
		}
		if (addDeley < pastTime)
		{
			_enemyObjectDirect = DIRECTION_LEFT;
			pastTime = 0;
			OffsetRect(&_object.m_rc, -_objectSpeed, 0);
			//obectFollowMove(_object, _dunMap, _objectSpeed);
		}
	}
	else if (_playerDirect == DIRECTION_LEFT && _enemyRc.left - _playerRc.left <= 0) m_isDongo = true;

	if (_playerRc.right - _enemyRc.right > _objectSpeed && !m_isDongo)
	{
		if (_enemyRc.top - (_playerRc.top - 60) > 10)	// 플레이어가 위쪽에 있단 전제
		{
			_enemyObjectDirect = DIRECTION_RIGHTUP;
			if (addDeley < pastTime)
			{
				pastTime = 0;
				OffsetRect(&_object.m_rc, +_objectSpeed, -_objectSpeed);
				//obectFollowMove(_object, _dunMap, _objectSpeed);
			}
		}
		if (_playerRc.bottom - _enemyRc.bottom > 100)
		{
			_enemyObjectDirect = DIRECTION_RIGHTDOWN;
			if (addDeley < pastTime)
			{
				pastTime = 0;
				OffsetRect(&_object.m_rc, +_objectSpeed, +_objectSpeed);
				//obectFollowMove(_object, _dunMap, _objectSpeed);
			}
		}
		if (addDeley < pastTime)
		{
			_enemyObjectDirect = DIRECTION_RIGHT;
			pastTime = 0;
			OffsetRect(&_object.m_rc, +_objectSpeed, 0);
			//obectFollowMove(_object, _dunMap, _objectSpeed);
		}
	}
	
	else if (_playerDirect == DIRECTION_RIGHT && _playerRc.right - _enemyRc.right <= 0) m_isDongo = true;

	//상하 처리
	if (_enemyRc.top - (_playerRc.top - 60) > 10)	// 플레이어가 위쪽에 있단 전제
	{
		if (addDeley < pastTime)
		{
			_enemyObjectDirect = DIRECTION_UP;
			pastTime = 0;
			OffsetRect(&_object.m_rc,0, -_objectSpeed);
			//obectFollowMove(_object, _dunMap, _objectSpeed);
		}
	}
	if (_playerRc.bottom - _enemyRc.bottom > 100)
	{
		if (addDeley < pastTime)
		{
			_enemyObjectDirect = DIRECTION_DOWN;
			pastTime = 0;
			OffsetRect(&_object.m_rc, 0, +_objectSpeed);
			//obectFollowMove(_object, _dunMap, _objectSpeed);
		}
		if (_enemyRc.left - _playerRc.left > 10 || _playerRc.right - _enemyRc.right > 10)
		{
			m_isDongo = false;
		}
	}

}


