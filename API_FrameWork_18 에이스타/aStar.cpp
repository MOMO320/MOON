#include "stdafx.h"
#include "aStar.h"

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
	exTile = NULL;
	enemyDirection = DIRECTION_DOWN;
	enemyMoveOk = false;
	enemyMoveRect = m_enemy->getEnemyInfo()._rc;
	moveCount = 0;

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

	m_enemy->setRect(m_astarTiles[47].rc);

	blockType();

	return S_OK;
}

void aStar::release()
{
}

void aStar::update(tagTile _map[], RECT _playerRect)
{
	RECT temp1;
	
	if (IntersectRect(&temp1, &_playerRect, &m_enemy->m_enemy1._fightColli) && !startAstar)
	{
		currentSelect = SELECT_START;
		startAstar = true;
		enemytileSet();
		
	}
	
	if (!isFind && !noPath &&startAstar)
	{
		playerTileSet(_playerRect);
		Astar();
	}

	if (isFind && !enemyMoveOk)
	{
		rectMoveDirect();  //pathList의 node에 따른 렉트의 이동 방향 설정
	}

	//if (enemyMoveOk)
	//{
	//	switch (enemyDirection)
	//	{
	//	case DIRECTION_LEFT:
	//		break;
	//	case DIRECTION_RIGHT:
	//		break;
	//	case DIRECTION_UP:
	//		break;
	//	case DIRECTION_DOWN:
	//		if (m_enemy->getEnemyInfo()._rc.bottom + 80 < enemyMoveRect.bottom )
	//		{
	//			OffsetRect(&enemyMoveRect, 0,  1);
	//			m_enemy->setRect(enemyMoveRect);
	//		}
	//		else
	//		{
	//			enemyMoveOk = false;
	//		}
	//		break;
	//	case DIRECTION_LEFTUP:
	//		break;
	//	case DIRECTION_RIGHTDOWN:
	//		break;
	//	case DIRECTION_LEFTDOWN:
	//		break;
	//	case DIRECTION_RIGHTUP:
	//		break;
	//	default:
	//		break;
	//	}
	//}






}

void aStar::render()
{

	// 선생님 a* 랜더

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
			if (m_astarTiles[y * astarTileX + x].block) tempBlock[i] = true;
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
		m_startY = (m_enemy->m_enemy1._rc.top / 80) - 1;

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
	max = pathList.size() - 1;
	float tempTime ;
	float elpasedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elpasedTime * m_enemy->getEnemyInfo().speed;

	for (int i = max; i > 0 ;i)
	{
		if (i == 0) continue;
			
		if (pathList.at(i) - pathList.at(i - 1) == -13) // 좌상단
		{
			if (m_astarTiles[pathList.at(i - 1)].rc.left >= m_enemy->getEnemyInfo()._rc.left)
			{
				OffsetRect(&temp, -moveSpeed, -moveSpeed);
				m_enemy->setRect(temp);
			}
		}
		if (pathList.at(i) - pathList.at(i - 1) == -12) // 중상단
		{
			if (m_astarTiles[pathList.at(i - 1)].rc.top >= m_enemy->getEnemyInfo()._rc.top)
			{
				OffsetRect(&temp, 0, -moveSpeed);
				m_enemy->setRect(temp);
			}
		}

		if (pathList.at(i) - pathList.at(i - 1) == -12) // 중하단
		{
			if (m_astarTiles[pathList.at(i - 1)].rc.bottom > enemyMoveRect.top)
			{
				tempTime = TIMEMANAGER->getElapsedTime();
				if (tempTime > elpasedTime)
				{
					OffsetRect(&enemyMoveRect, 0, 1);
					m_enemy->setRect(enemyMoveRect);
				}
				
					
			}else enemyMoveOk = true;

		}

		if (enemyMoveOk) i--;
	}

}

