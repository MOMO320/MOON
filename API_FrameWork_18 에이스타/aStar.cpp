#include "stdafx.h"
#include "aStar.h"
#include <cmath>

aStar::aStar(): m_enemy(new enemies)
{
	m_enemy->init();
}

aStar::~aStar()
{
	delete m_enemy;
}

HRESULT aStar::init(tagTile _map[])
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

	temp.left = m_astarTiles[47].rc.left;
	temp.top= m_astarTiles[47].rc.top;
	temp.right = m_astarTiles[47].rc.right;
	temp.bottom = m_astarTiles[47].rc.bottom;

	m_enemy->setRect(temp);
	enemyMoveRect = m_enemy->getEnemyInfo()._rc;
	blockType();

	return S_OK;
}

void aStar::release()
{
}

void aStar::update(tagTile _map[], RECT _playerRect)
{
	RECT temp1;
	
	deltaTime = TIMEMANAGER->getElapsedTime();
	pastTime += deltaTime;

	if (IntersectRect(&temp1, &_playerRect, &m_enemy->m_enemy1._fightColli) && !startAstar)
	{
		currentSelect = SELECT_START;
		startAstar = true;
		enemytileSet();
		
	}
		playerTileSet(_playerRect);

	if (!isFind && !noPath &&startAstar)
	{	
		Astar();
	}

	if (isFind)
	{
		rectMoveDirect();  //pathList의 node에 따른 렉트의 이동 방향 설정
	}


	if (enemyMoveOk)
	{
	switch (enemyDirection)
	{
	case DIRECTION_LEFT:
		if (moveX+4 < toGoX)
		{
			toGoX = enemyMoveRect.left;
			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, -4, 0);
				m_enemy->setRect(enemyMoveRect);
			}
		}
		else enemyMoveOk = false;
		break;
	case DIRECTION_RIGHT:
		if (moveX+4 > toGoX)
		{
			toGoX = enemyMoveRect.right;
			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, 4, 0);
				m_enemy->setRect(enemyMoveRect);
			}
		}
		else enemyMoveOk = false;
		break;
	case DIRECTION_UP:
		if (moveY + 4 < toGoY)
		{
			toGoY = enemyMoveRect.top;
			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, 0, -4);
				m_enemy->setRect(enemyMoveRect);
			}
		}
		else enemyMoveOk = false;
		break;
	case DIRECTION_DOWN:
		if (moveY + 4 > toGoY)
		{
			toGoY = enemyMoveRect.bottom;
		    if (pastTime > addCharDeley)
		    {
		    	OffsetRect(&enemyMoveRect, 0, 4);
		    	m_enemy->setRect(enemyMoveRect);	
		    }
		}
		else enemyMoveOk = false;
		break;
	case DIRECTION_LEFTUP:
		if (moveX + 4 < toGoX && moveY + 4 < toGoY)
		{
			toGoX = enemyMoveRect.left;
			toGoY = enemyMoveRect.bottom;

			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, -4, -4);
				m_enemy->setRect(enemyMoveRect);
			}
		}
		else enemyMoveOk = false;
		break;
	case DIRECTION_RIGHTDOWN:
		if (moveX + 4 > toGoX && moveY + 4 > toGoY)
		{
			toGoX = enemyMoveRect.right;
			toGoY = enemyMoveRect.bottom;

			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, 4, 4);
				m_enemy->setRect(enemyMoveRect);
			}
		}
		else enemyMoveOk = false;
		break;
	case DIRECTION_LEFTDOWN:
		if (moveX + 4 < toGoX && moveY + 4 > toGoY)
		{
			toGoX = enemyMoveRect.left;
			toGoY = enemyMoveRect.bottom;

			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, -4, 4);
				m_enemy->setRect(enemyMoveRect);
			}
		}
		else enemyMoveOk = false;
		break;
	case DIRECTION_RIGHTUP:
		if (moveX + 4 > toGoX && moveY + 4 < toGoY)
		{
			toGoX = enemyMoveRect.left;
			toGoY = enemyMoveRect.top;

			if (pastTime > addCharDeley)
			{
				OffsetRect(&enemyMoveRect, 4, -4);
				m_enemy->setRect(enemyMoveRect);
			}
		}else enemyMoveOk = false;
		break;
	default:
		break;
	}
	}


}

void aStar::render()
{
	// 선생님 a* 랜더

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
			colorRectangle(getMemDC(), m_astarTiles[i].rc.left, m_astarTiles[i].rc.top, 80, 80,255, 128, 128);
		}
	}
	m_enemy->render();

	for (int i = 0; i < astarTileX * astarTileY; i++)
	{
		printText(getMemDC(), to_string(i).c_str(), "나눔고딕", m_astarTiles[i].rc.left, m_astarTiles[i].rc.top + 20, 15, RGB(255, 0, 0), true, RGB(255, 0, 255));
	}
	RectangleMakeCenter(getMemDC(), m_astarTiles[startTile].rc.left + 20, m_astarTiles[startTile].rc.top+20, 40,40);
	colorRectangle(getMemDC(), m_astarTiles[endTile].rc.left + 20, m_astarTiles[endTile].rc.top + 20, 40, 40, 0, 0, 160);
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
		noPath = true;
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
		tempTile = m_astarTiles[tempTile].node;
		m_astarTiles[tempTile].showState = STATE_PATH;
		pathList.push_back(m_astarTiles[tempTile].node);
	}
}


void aStar::enemytileSet()
{
	if (startAstar)
	{
		m_startX = (m_enemy->m_enemy1._rc.left / 80) - 2;
		m_startY = abs(m_enemy->m_enemy1._rc.top / 80) - 1;

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

void aStar::rectMoveDirect()
{
	int max;
	RECT temp = m_enemy->getEnemyInfo()._rc;

	if(pathList.size() >= 1)
	max = pathList.size() - 1;
	else max =  0;
	
	if (max == 0)
	{
		isFind = false;
		pathList.clear();
		closeList.clear();
		openList.clear();
		startAstar = false;
		directionCount = 0;
	}
	
	if (!enemyMoveOk )
	{
		for (int i = max; i > 0; i)
		{
			i -= directionCount;

		 // 벡터의 크기가 0이 아닐때			
			if (i == 0)
			{
				isFind = false;
				pathList.clear();
				closeList.clear();
				openList.clear();
				startAstar = false;
				directionCount = 0;
			}
			if (i > 0)
			{
			if (pathList.at(i) - pathList.at(i - 1) == 13) // 좌상단( x : -80 , y : -80)
			{
				enemyDirection = DIRECTION_LEFTUP;

				moveX = m_astarTiles[pathList.at(i - 1)].rc.left;
				toGoX = m_astarTiles[pathList.at(i)].rc.left;

				moveY = m_astarTiles[pathList.at(i - 1)].rc.bottom;
				toGoY = m_astarTiles[pathList.at(i)].rc.bottom;
				
				enemyMoveOk = true;
				directionCount += 1;
				pastTime = 0;
				break;
			}

			if (pathList.at(i) - pathList.at(i - 1) == 12) // 중상단 (y : - 80)
			{
				enemyDirection = DIRECTION_UP;
				moveY = m_astarTiles[pathList.at(i - 1)].rc.top;
				toGoY = m_astarTiles[pathList.at(i)].rc.top;
				enemyMoveOk = true;
				directionCount += 1;
				pastTime = 0;
				break;
			}

			if (pathList.at(i) - pathList.at(i - 1) == 11) // 우상단 (x : 80 , y : -80)
			{
				enemyDirection = DIRECTION_RIGHTUP;
				moveX = m_astarTiles[pathList.at(i - 1)].rc.right;
				toGoX = m_astarTiles[pathList.at(i)].rc.right;

				moveY = m_astarTiles[pathList.at(i - 1)].rc.top;
				toGoY = m_astarTiles[pathList.at(i)].rc.top;
				enemyMoveOk = true;
				directionCount += 1;
				pastTime = 0;
				break;
			}

			if (pathList.at(i) - pathList.at(i - 1) == 1)  // 왼쪽 ( x: -80)
			{
				enemyDirection = DIRECTION_LEFT;
				moveX = m_astarTiles[pathList.at(i - 1)].rc.left;
				toGoX = m_astarTiles[pathList.at(i)].rc.left;
				enemyMoveOk = true;
				 directionCount += 1;
				 pastTime = 0;
				break;
			}

			if (pathList.at(i) - pathList.at(i - 1) == -1)  // 오른쪽 ( x: 80)
			{
				enemyDirection = DIRECTION_RIGHT;
				moveX = m_astarTiles[pathList.at(i - 1)].rc.right;
				toGoX = m_astarTiles[pathList.at(i)].rc.right;

				enemyMoveOk = true;
				 directionCount += 1;
				 pastTime = 0;
				break;
			}
			
			if (pathList.at(i) - pathList.at(i - 1) == -11) // 좌하단 (x: -80 , y: 80)
			{
				enemyDirection = DIRECTION_LEFTDOWN;
				moveX = m_astarTiles[pathList.at(i - 1)].rc.left;
				toGoX = m_astarTiles[pathList.at(i)].rc.left;

				moveY = m_astarTiles[pathList.at(i - 1)].rc.bottom;
				toGoY = m_astarTiles[pathList.at(i)].rc.bottom;

				enemyMoveOk = true;
				directionCount += 1;
				pastTime = 0;
				break;
			}

			if (pathList.at(i) - pathList.at(i - 1) == -12) // 중하단
			{
				enemyDirection = DIRECTION_DOWN;
				moveY = m_astarTiles[pathList.at(i - 1)].rc.bottom;
				toGoY = m_astarTiles[pathList.at(i)].rc.bottom;
				enemyMoveOk = true;
				directionCount += 1;
				pastTime = 0;
				break;
			}

			if (pathList.at(i) - pathList.at(i - 1) == -13) // 우하단 ( x: 80 , y : 80)
			{
				enemyDirection = DIRECTION_RIGHTDOWN;
				moveX = m_astarTiles[pathList.at(i - 1)].rc.right;
				toGoX = m_astarTiles[pathList.at(i)].rc.right;

				moveY = m_astarTiles[pathList.at(i - 1)].rc.bottom;
				toGoY = m_astarTiles[pathList.at(i)].rc.bottom;
				enemyMoveOk = true;
			    directionCount += 1;
				pastTime = 0;
				break;
			}
		    }
		}
	}
}

