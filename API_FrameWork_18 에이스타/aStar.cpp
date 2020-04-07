#include "stdafx.h"
#include "aStar.h"
#include "gameTypes.h"
#include <cmath>

aStar::aStar()
{
}

aStar::~aStar()
{

}

HRESULT aStar::init(tagTile _map[], enemies* _enemy , int _x, int _y)
{
	RECT temp;

	exTile = NULL;
	enemyDirection = DIRECTION_DOWN;
	enemyMoveOk = false;
	
	moveCount = 0;

	deltaTime = 0;

	m_startX = 0;
	m_startY = 0;

	m_endX = 0;
	m_endY = 0;

	// a star 타일 셋팅
	for (int i = 1; i <= astarTileY; i++)
	{
		for (int j = 0; j < astarTileX; j++)
		{
			m_astarTiles[j + (i-1) * astarTileX].rc = _map[(i*40) + (j+2)].m_rc;
			m_astarTiles[j + (i - 1) * astarTileX].obj = _map[(i * 40) + (j + 2)].m_obj;
		}
	}

	startTile = endTile = -1;

	currentSelect = SELECT_START;

	isFind     = false;
	noPath     = false;
	startAstar = false;

	_enemy->enemySetRect(_x, _y);
	enemyMoveRect = _enemy->getEnemyInfo()._rc;

	blockType();

	return S_OK;
}

void aStar::release()
{
}

void aStar::update(tagTile _map[], RECT _playerRect , enemies* _enemy, int _speed ,bool _aniIndexUse)
{
	RECT temp1;
	RECT enemyFightCollision;
	enemyFightCollision = _enemy->getEnemyInfo()._fightColli;

	deltaTime = TIMEMANAGER->getElapsedTime();
	pastTime += deltaTime;

	if (IntersectRect(&temp1, &_playerRect , &enemyFightCollision) && !startAstar)
	{ 
		currentSelect = SELECT_START;
		startAstar = true;
		enemytileSet(_enemy);
	}
	
	playerTileSet(_playerRect);

	if (!isFind && !noPath &&startAstar)
	{	
		Astar();
	}

	if (isFind)
	{
		rectMoveDirect(_enemy , _aniIndexUse);  //pathList의 node에 따른 렉트의 이동 방향 설정
	}

	if (enemyMoveOk)
	{
	switch (enemyDirection)
	{
	case DIRECTION_LEFT:
		if (moveX- 24 < toGoX)
		{
			toGoX = enemyMoveRect.left;
			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, -_speed, 0);
				_enemy->setRect(enemyMoveRect);
			}
		}
		else
		{
			enemyMoveOk = false;
			firstCount = false;
		}
		break;
	case DIRECTION_RIGHT:
		if (moveX+ 24 > toGoX)
		{
			toGoX = enemyMoveRect.right;
			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, _speed, 0);
				_enemy->setRect(enemyMoveRect);
			}
		}
		else
		{
			enemyMoveOk = false;
			firstCount = false;
		}
		break;
	case DIRECTION_UP:
		if (moveY - 24 < toGoY)
		{
			toGoY = enemyMoveRect.top;
			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, 0, -_speed);
				_enemy->setRect(enemyMoveRect);
				directionCount = 0;
			}
		}
		else
		{
			enemyMoveOk = false;
			firstCount = false;
		}
		break;
	case DIRECTION_DOWN:
		if (moveY + 24 > toGoY)
		{
			toGoY = enemyMoveRect.bottom;
		    if (pastTime > addCharDeley)
		    {
		    	OffsetRect(&enemyMoveRect, 0, _speed);
				_enemy->setRect(enemyMoveRect);
		    }
		}
		else
		{
			enemyMoveOk = false;
			firstCount = false;
		}
		break;
	case DIRECTION_LEFTUP:
		if (moveX - 32 < toGoX && moveY - 32 < toGoY)
		{
			toGoX = enemyMoveRect.left;
			toGoY = enemyMoveRect.bottom;

			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, -_speed, -_speed);
				_enemy->setRect(enemyMoveRect);
			}
		}
		else
		{
			enemyMoveOk = false;
			firstCount = false;
		}
		break;
	case DIRECTION_RIGHTDOWN:
		if (moveX + 32 > toGoX && moveY + 32 > toGoY)
		{
			toGoX = enemyMoveRect.right;
			toGoY = enemyMoveRect.bottom;

			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, _speed, _speed);
				_enemy->setRect(enemyMoveRect);
			}
		}
		else
		{
			enemyMoveOk = false;
			firstCount = false;
		}
		break;
	case DIRECTION_LEFTDOWN:
		if (moveX - 32 < toGoX && moveY + 32 > toGoY)
		{
			toGoX = enemyMoveRect.left;
			toGoY = enemyMoveRect.bottom;

			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, -_speed, _speed);
				_enemy->setRect(enemyMoveRect);
			}
		}
		else
		{
			enemyMoveOk = false;
			firstCount = false;
		}
		break;
	case DIRECTION_RIGHTUP:
		if (moveX + 32 > toGoX && moveY - 32 < toGoY)
		{
			toGoX = enemyMoveRect.left;
			toGoY = enemyMoveRect.top;

			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, _speed, -_speed);
				_enemy->setRect(enemyMoveRect);
			}
		}
		else
		{
			enemyMoveOk = false;
			firstCount = false;
		}
		break;
	}
	}
}

void aStar::render(enemies* _enemy)
{
	// 선생님 a* 랜더

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		for (int i = 0; i < astarTileSize; i++)
		{
			if (m_astarTiles[i].block == true)
				colorRectangle(getMemDC(), m_astarTiles[i].rc.left, m_astarTiles[i].rc.top, 80, 80, 0, 0, 255);
		}

		for (int i = 0; i < astarTileSize; i++)
		{
			if (m_astarTiles[i].block)
			{
				if (i == startTile)
				{
					startTile = -1;
				}
				if (i == endTile)
				{
					endTile = -1;
				}
			}
			else if (i == startTile)
			{
				colorRectangle(getMemDC(), m_astarTiles[i].rc.left, m_astarTiles[i].rc.top, 80, 80, 0, 255, 0);
			}
			else if (i == endTile)
			{
				colorRectangle(getMemDC(), m_astarTiles[i].rc.left, m_astarTiles[i].rc.top, 80, 80, 255, 0, 0);
			}
			else if (m_astarTiles[i].showState == STATE_OPEN)
			{
				colorRectangle(getMemDC(), m_astarTiles[i].rc.left, m_astarTiles[i].rc.top, 80, 80, 128, 255, 255);
			}
			else if (m_astarTiles[i].showState == STATE_CLOSE)
			{
				colorRectangle(getMemDC(), m_astarTiles[i].rc.left, m_astarTiles[i].rc.top, 80, 80, 128, 255, 0);
			}
			else if (m_astarTiles[i].showState == STATE_PATH)
			{
				colorRectangle(getMemDC(), m_astarTiles[i].rc.left, m_astarTiles[i].rc.top, 80, 80, 255, 128, 128);
			}

		}
	}
	_enemy->render();

	//for(int i = 0 ; i < astarTileSize ; i++)
	//printText(getMemDC(), to_string(i).c_str(), "고딕", m_astarTiles[i].rc.left, m_astarTiles[i].rc.top, 20, 255, 100, 50);

	//RectangleMakeCenter(getMemDC(), m_astarTiles[startTile].rc.left + 20, m_astarTiles[startTile].rc.top+20, 40,40);
	//colorRectangle(getMemDC(), m_astarTiles[endTile].rc.left + 20, m_astarTiles[endTile].rc.top + 20, 40, 40, 0, 0, 160);

	//printText(getMemDC(), to_string(directionCount).c_str(), "고딕", WINSIZEX/2, 0, 50, 100, 100, 50);
}

void aStar::enemyRender(enemies * _enemy)
{
}

void aStar::Astar()
{
	int endX = endTile % astarTileX;
	int endY = endTile / astarTileX;

	int currentX = currentTile % astarTileX;
	int currentY = currentTile / astarTileX;
	
	// left , right , up , down , leftup , rightdown , leftdown , rightup
	int dx[] = { -1, 1 , 0 , 0 ,  -1 , 1 , -1, 1 };
	int dy[] = { 0 , 0 , -1, 1 ,  -1 , 1 , 1 , -1 };
	bool tempBlock[8];

	// 방향 찾는 방복문

	for (int i = 0; i < 8; i++)
	{
		int x = currentX + dx[i];
		int y = currentY + dy[i];
		tempBlock[i] = false;

		// 해당 방향으로 움직인 타일이 유효한 타일인지 확인
		if (0 <= x && x < astarTileX && 0 <= y && y < astarTileY)
		{
			bool isOpen;
			// 대각선 타일의 이동 문제로 (주변에 블락있으면 못감) 임시로 블락 상태 저장
			if (m_astarTiles[y * astarTileX + x].block)
				tempBlock[i] = true;
			else {
				// check closeList z
				bool isClose = false;
				for (int j = 0; j < closeList.size(); j++)
				{
					if (closeList[j] == y * astarTileX + x)
					{
						isClose = true;
						break;
					}
				}
				if (isClose) continue;

				if (i < 4)
				{
					m_astarTiles[y * astarTileX + x].g = 10;
				}
				else
				{
					// leftup인 경우 left나 up에 블락있으면 안됨
					if (i == DIRECTION_LEFTUP &&
						tempBlock[DIRECTION_LEFT] || tempBlock[DIRECTION_UP]) continue;
					// rightdown인 경우 right나 down에 블락있으면 안됨
					if (i == DIRECTION_RIGHTDOWN &&
						tempBlock[DIRECTION_RIGHT] || tempBlock[DIRECTION_DOWN]) continue;
					// rightup인 경우 right나 up에 블락있으면 안됨
					if (i == DIRECTION_RIGHTUP &&
						tempBlock[DIRECTION_RIGHT] || tempBlock[DIRECTION_UP]) continue;
					// leftdown인 경우 left나 down에 블락있으면 안됨
					if (i == DIRECTION_LEFTDOWN &&
						tempBlock[DIRECTION_LEFT] || tempBlock[DIRECTION_DOWN]) continue;
					m_astarTiles[y * astarTileX + x].g = 14;

				}
				//abs절대값

				m_astarTiles[y * astarTileX + x].h = (abs(endX - x) + abs(endY - y)) * 10;
				m_astarTiles[y * astarTileX + x].f = m_astarTiles[y * astarTileX + x].g + m_astarTiles[y * astarTileX + x].h;

				// 오픈리스트에 있으면 g 비용 비교 후 처리
				isOpen = false;
				for (int i = 0; i < openList.size(); i++)
				{
					if (openList[i] == y * astarTileX + x)
					{
						isOpen = true;
						if (m_astarTiles[openList[i]].g > m_astarTiles[y * astarTileX + x].g)
						{
							m_astarTiles[openList[i]].h = m_astarTiles[y * astarTileX + x].h;
							m_astarTiles[openList[i]].g = m_astarTiles[y * astarTileX + x].g;
							m_astarTiles[openList[i]].f = m_astarTiles[y * astarTileX + x].f;
							m_astarTiles[openList[i]].node = currentTile;
						}
					}
				}
				// 없으면 그냥 넣고 부모 설정
				if (!isOpen)
				{
					openList.push_back(y * astarTileX + x);
					m_astarTiles[y * astarTileX + x].node = currentTile;
				}

				// find
				if (y * astarTileX + x == endTile)
					isFind = true;
			}
		}
	}

	// 선택 지점 열린목록에서 빼기
	for (iter = openList.begin(); iter != openList.end(); ++iter)
	{
		if ((*iter) == currentTile)
		{
			iter = openList.erase(iter);
			break;
		}
	}

	// not Find
	if (openList.size() == 0)
	{
		noPath = false;
	}

	// 현재 타일 클로즈리스트에 넣기
	closeList.push_back(currentTile);

	if (openList.size() != 0)
	{
		// find minimum f cost in openList
		int min = m_astarTiles[*openList.begin()].h;
		currentTile = *openList.begin();
		for (iter = openList.begin(); iter != openList.end(); ++iter)
		{
			if (min > m_astarTiles[(*iter)].h)
			{
				min = m_astarTiles[(*iter)].h;
				currentTile = *iter;
			}
		}
	}
	//}

	// 타일 렌더를 위해 상태 저장
	for (int i = 0; i < openList.size(); i++)
	{
		m_astarTiles[openList[i]].showState = STATE_OPEN;
	}
	for (int i = 0; i < closeList.size(); i++)
	{
		m_astarTiles[closeList[i]].showState = STATE_CLOSE;
	}
	// 길 찾기 성공시 각 타일에 길찾기 상태 저장
	int tempTile = endTile;
	while (m_astarTiles[tempTile].node != startTile
		&& isFind)
	{
		if (!firstPath)
		{
			pathList.push_back(m_astarTiles[tempTile].node);
			firstPath = true;
		}
		tempTile = m_astarTiles[tempTile].node;
		m_astarTiles[tempTile].showState = STATE_PATH;
		pathList.push_back(m_astarTiles[tempTile].node);
	}
}


void aStar::enemytileSet(enemies* _enemy)
{
	if (startAstar)
	{
		m_startX = (_enemy->getEnemyInfo()._rc.left / 80) - 2;
		m_startY = abs(_enemy->getEnemyInfo()._rc.top / 80) - 1;

		startTile = m_startY * astarTileX + m_startX;
		currentTile = startTile;

		if (currentTile != exTile)
		{
			openList.push_back(currentTile);
			exTile = currentTile;
		}
	}
}

void aStar::playerTileSet(RECT _playerRect)
{
	if (startAstar)
	{
		m_endX = (_playerRect.left / 80) - 2;
		m_endY = (_playerRect.top / 80) - 1;

		endTile = m_endY * astarTileX + m_endX;
	}
}

void aStar::blockType()
{
	for (int i = 0; i < astarTileX * astarTileY; i++)
	{
		if (m_astarTiles[i].obj == OBJ_TREE)
			m_astarTiles[i].block = true;

		if(m_astarTiles[i].obj == OBJ_DONGO)
			m_astarTiles[i].block = true;
			
		if(m_astarTiles[i].obj == OBJ_TREASUREBOX)
			m_astarTiles[i].block = true;
	}
}

void aStar::rectMoveDirect(enemies* _enemy, bool _aniIndexUse)
{
	int max;
	RECT temp = _enemy->getEnemyInfo()._rc;

	if(pathList.size() > 0)
	fistPath = pathList.at(0);

	if (pathList.size() > 1)
	{
		max = pathList.size() - 1;
	}
	if(pathList.size() == 0)
	{
		max = 0;
		
		if (_aniIndexUse == true)
		{
		    if (_enemy->getEnemyInfo().m_ani->getPlayIndex() == _enemy->getEnemyInfo().m_ani->getPlaySize().size() - 1 && _enemy->getEnemyInfo().m_momoAni == MOMO_ATTACKREADY && _enemy->getEnemyInfo().attackCount == 3  )
		    {
		        if (max == 0)
		        {
		        	isFind = false;
		        	pathList.clear();
		        	closeList.clear();
		        	openList.clear();
		        	startAstar = false;
		        	firstPath = false;
		        	directionCount = 0;
		        }
		    }
		}
		else if (_aniIndexUse == false)
		{
			if (max == 0)
			{
				isFind = false;
				pathList.clear();
				closeList.clear();
				openList.clear();
				startAstar = false;
				firstPath = false;
				directionCount = 0;
			}
		}
	}

	if (!enemyMoveOk)
	{
		for (int i = max; i > 0; i)
		{
			i -= directionCount;
			currentPath = pathList.at(i);
	
			if (!firstCount && i == max)
			{
				directionCount = 0;
				firstCount = true;
			}

		 // 벡터의 크기가 0이 아닐때			
			if (i == 0)
			{
				if (_aniIndexUse == true)
				{
				    if (_enemy->getEnemyInfo().m_ani->getPlayIndex() == _enemy->getEnemyInfo().m_ani->getPlaySize().size()-1 && _enemy->getEnemyInfo().m_momoAni == MOMO_ATTACKREADY && _enemy->getEnemyInfo().attackCount == 3)
				    {
				       isFind = false;
				       pathList.clear();
				       closeList.clear();
				       openList.clear();
				       startAstar = false;
				       firstPath = false;
				       directionCount = 0;
				    }
				}
				if (_aniIndexUse == false)
				{
					isFind = false;
					pathList.clear();
					closeList.clear();
					openList.clear();
					startAstar = false;
					firstPath = false;
					directionCount = 0;
				}
			}
			if (i > 0)
			{
			
			if (pathList.at(i) - pathList.at(i - 1) == 13) // 좌상단( x : -80 , y : -80)
			{
				enemyDirection = DIRECTION_LEFTUP;

				moveX = m_astarTiles[pathList.at(i - 1)].rc.left + 40;
				toGoX = m_astarTiles[pathList.at(i)].rc.left + 40;

				moveY = m_astarTiles[pathList.at(i - 1)].rc.bottom - 40;
				toGoY = m_astarTiles[pathList.at(i)].rc.bottom - 40;
				
				enemyMoveOk = true;
				directionCount += 1;
			
				pastTime = 0;
				break;
			}

			if (pathList.at(i) - pathList.at(i - 1) == 12) // 중상단 (y : - 80)
			{
				enemyDirection = DIRECTION_UP;
				moveY = m_astarTiles[pathList.at(i - 1)].rc.top + 40;
				toGoY = m_astarTiles[pathList.at(i)].rc.top + 40;
				enemyMoveOk = true;
				directionCount += 1;
			
				pastTime = 0;
				break;
			}

			if (pathList.at(i) - pathList.at(i - 1) == 11) // 우상단 (x : 80 , y : -80)
			{
				enemyDirection = DIRECTION_RIGHTUP;
				moveX = m_astarTiles[pathList.at(i - 1)].rc.right - 40;
				toGoX = m_astarTiles[pathList.at(i)].rc.right - 40;

				moveY = m_astarTiles[pathList.at(i - 1)].rc.top + 40;
				toGoY = m_astarTiles[pathList.at(i)].rc.top + 40;
				enemyMoveOk = true;
				directionCount += 1;
			
				pastTime = 0;
				break;
			}

			if (pathList.at(i) - pathList.at(i - 1) == 1)  // 왼쪽 ( x: -80)
			{
				enemyDirection = DIRECTION_LEFT;
				moveX = m_astarTiles[pathList.at(i - 1)].rc.left + 40;
				toGoX = m_astarTiles[pathList.at(i)].rc.left + 40;
				enemyMoveOk = true;
				directionCount += 1;
			
				pastTime = 0;
				break;
			}

			if (pathList.at(i) - pathList.at(i - 1) == -1)  // 오른쪽 ( x: 80)
			{
				enemyDirection = DIRECTION_RIGHT;
				moveX = m_astarTiles[pathList.at(i - 1)].rc.right - 40;
				toGoX = m_astarTiles[pathList.at(i)].rc.right - 40;

				enemyMoveOk = true;
				 directionCount += 1;
			
				 pastTime = 0;
				break;
			}
			
			if (pathList.at(i) - pathList.at(i - 1) == -11) // 좌하단 (x: -80 , y: 80)
			{
				enemyDirection = DIRECTION_LEFTDOWN;
				moveX = m_astarTiles[pathList.at(i - 1)].rc.left + 40;
				toGoX = m_astarTiles[pathList.at(i)].rc.left + 40;

				moveY = m_astarTiles[pathList.at(i - 1)].rc.bottom - 40;
				toGoY = m_astarTiles[pathList.at(i)].rc.bottom - 40;

				enemyMoveOk = true;
				directionCount += 1;
			
				pastTime = 0;
				break;
			}

			if (pathList.at(i) - pathList.at(i - 1) == -12) // 중하단
			{
				enemyDirection = DIRECTION_DOWN;
				moveY = m_astarTiles[pathList.at(i - 1)].rc.bottom - 40;
				toGoY = m_astarTiles[pathList.at(i)].rc.bottom - 40;
				enemyMoveOk = true;
				directionCount += 1;
			
				pastTime = 0;
				break;
			}

			if (pathList.at(i) - pathList.at(i - 1) == -13) // 우하단 ( x: 80 , y : 80)
			{
				enemyDirection = DIRECTION_RIGHTDOWN;
				moveX = m_astarTiles[pathList.at(i - 1)].rc.right - 40;
				toGoX = m_astarTiles[pathList.at(i)].rc.right - 40;

				moveY = m_astarTiles[pathList.at(i - 1)].rc.bottom - 40;
				toGoY = m_astarTiles[pathList.at(i)].rc.bottom - 40;
				enemyMoveOk = true;
			    directionCount += 1;
			
				pastTime = 0;
				break;
			}
		    }
		}
	}
}

