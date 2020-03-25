#include "stdafx.h"
#include "DugeonScene.h"

DugeonScene::DugeonScene()
	:m_Map1(new dungeonMap1) ,
	m_aStar(new aStar) , m_miniSlime(new miniSlime) , m_miniSlime2(new miniSlime), m_miniSlime3(new miniSlime),
	m_aStar1(new aStar) , m_aStar2(new aStar) , m_flea1(new flea) ,m_aStar3(new aStar) , m_mushRoom(new mushRoom) , m_mushRoom1(new mushRoom)
{
}

DugeonScene::~DugeonScene()
{
	delete m_Map1;
	delete m_aStar;
	delete m_aStar1;
	delete m_aStar2;
	delete m_aStar3;
	delete m_miniSlime;
	delete m_miniSlime2;
	delete m_miniSlime3;
	delete m_flea1;
	delete m_mushRoom;
	delete m_mushRoom1;
}

HRESULT DugeonScene::init()
{
	m_Map1->init();
	m_miniSlime->init(WINSIZEX / 2, WINSIZEY / 2);
	m_miniSlime2->init(WINSIZEX / 2+200, WINSIZEY / 2 +200);
	m_miniSlime3->init(WINSIZEX / 2+100, WINSIZEY / 2 +100);

	m_flea1->init(WINSIZEX - 300, WINSIZEY - 400);
	m_mushRoom->init(WINSIZEX - 450, 300);
	m_mushRoom1->init(400, 300);


	m_aStar->init(m_Map1->getMap() , m_miniSlime , WINSIZEX/2  , WINSIZEY/2);
	m_aStar1->init(m_Map1->getMap() , m_miniSlime2 , WINSIZEX/2 + 200  , WINSIZEY/2+200);
	m_aStar2->init(m_Map1->getMap() , m_miniSlime3 , WINSIZEX / 2 +100, WINSIZEY / 2 + 100);
	m_aStar3->init(m_Map1->getMap(), m_flea1, WINSIZEX - 300, WINSIZEY - 400);

	//===============//
	//	 playerºÒ·³  //
	//===============//
	PLAYER.setTankMapMemoryAdress(m_Map1);
	PLAYER.setCharacPosition(m_Map1->getMap()[288].m_rc);
	PLAYER.m_player.m_money -= 300;
	PLAYER.m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_upIdle");
	PLAYER.m_player.m_ani->start();
	return S_OK;
}

void DugeonScene::release()
{
	IMAGEMANAGER->deleteAll();
	m_miniSlime->release();
	m_miniSlime2->release();
	m_miniSlime3->release();
	m_flea1->release();

	PLAYER.release();
	m_Map1->release();
	m_mushRoom->release();
	m_mushRoom1->release();
}

void DugeonScene::update()
{
	PLAYER.update(m_Map1);
	m_Map1->update();
	m_miniSlime->update();
	m_miniSlime2->update();
	m_miniSlime3->update();
	m_flea1->update();
	m_aStar->update(m_Map1->m_map, PLAYER.getPlayerRect(),m_miniSlime,4);
	m_aStar1->update(m_Map1->m_map, PLAYER.getPlayerRect(),m_miniSlime2,4);
	m_aStar2->update(m_Map1->m_map, PLAYER.getPlayerRect(),m_miniSlime3,4);
	m_aStar3->update(m_Map1->m_map, PLAYER.getPlayerRect(), m_flea1,2);
	m_mushRoom->update(PLAYER.getPlayerRect(),m_Map1);
	m_mushRoom1->update(PLAYER.getPlayerRect(),m_Map1);
}

void DugeonScene::render()
{
	m_Map1->render();
	m_aStar->render(m_miniSlime);
	m_aStar1->render(m_miniSlime2);
	m_aStar2->render(m_miniSlime3);
	m_aStar3->render(m_flea1);
	m_mushRoom->render();
	m_mushRoom1->render();
	m_mushRoom->render(m_Map1);
	m_mushRoom1->render(m_Map1);
	PLAYER.render();
	printText(getMemDC(), std::to_string(PLAYER.m_player.m_money).c_str(), "°íµñ", WINSIZEX / 2, 200, 50, false, RGB(255,255,255),false);
	
}

