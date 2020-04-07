#include "stdafx.h"
#include "DugeonScene2.h"

DugeonScene2::DugeonScene2():m_Map2(new dungeonMap2) , m_bazookaFlower1(new bazookaFlower),
m_bazookaFlower2(new bazookaFlower)
{
}

DugeonScene2::~DugeonScene2()
{
	delete m_Map2;
	//delete m_bazookaFlower1;
	delete m_bazookaFlower2;

}

HRESULT DugeonScene2::init()
{
	m_Map2->init();
	m_bazookaFlower1->init(WINSIZEX/2 +200 , WINSIZEY/2);
	m_bazookaFlower2->init( 400 , WINSIZEY/2-50);
	//PLAYER.init();

	PLAYER.m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_rightIdle");
	PLAYER.m_player.m_ani->start();
	PLAYER.setTankMapMemoryAdress(m_Map2);
	PLAYER.setCharacPosition(m_Map2->getMap()[162].m_rc);

	return S_OK;
}

void DugeonScene2::release()
{
	PLAYER.release();
	m_Map2->release();
	
	m_bazookaFlower2->release();
}

void DugeonScene2::update()
{
	RECT playerMoveRect = RectMakeCenter(WINSIZEX / 2 + 5, 360, WINSIZEX - 300, WINSIZEY / 2 + 180);
	float time = TIMEMANAGER->getElapsedTime();
	pastTime += time;

	m_Map2->update();
	PLAYER.update(m_Map2 ,false, playerMoveRect);

	m_bazookaFlower2->update(PLAYER.m_player._rc, m_Map2);
	m_bazookaFlower1->update(PLAYER.m_player._rc, m_Map2);
	
}

void DugeonScene2::render()
{
	m_Map2->render();
    m_bazookaFlower1->render();
    m_bazookaFlower1->render(PLAYER.m_player.m_playerDirect, PLAYER.m_player._rc);
	
	m_bazookaFlower2->render();
	m_bazookaFlower2->render(PLAYER.m_player.m_playerDirect, PLAYER.m_player._rc);
	PLAYER.render(getMemDC());
	//printText(getMemDC(), std::to_string(PLAYER.m_player.m_money).c_str(), "°íµñ", WINSIZEX / 2, 200, 50, false, RGB(255, 255, 255), false);
}
