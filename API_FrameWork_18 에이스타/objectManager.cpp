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


