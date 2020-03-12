#include "stdafx.h"
#include "DugeonScene.h"

DugeonScene::DugeonScene()
	:m_Map1(new dungeonMap1) , m_player(new player) ,
	m_aStar(new aStar)
{
	m_player->init();
	
}

DugeonScene::~DugeonScene()
{
	delete m_Map1;
	delete m_player;
	delete m_aStar;
}

HRESULT DugeonScene::init()
{
	m_Map1->init();
	m_aStar->init(m_Map1->getMap());
	//===============//
	//	 playerºÒ·³  //
	//===============//
	m_player->setTankMapMemoryAdress(m_Map1);
	m_player->setCharacPosition(m_Map1->getMap()[m_Map1->getPosFirst()].m_rc);

	return S_OK;
}

void DugeonScene::release()
{
	IMAGEMANAGER->deleteAll();
}

void DugeonScene::update()
{
	m_player->update();
	m_Map1->update();
	m_aStar->update(m_Map1->m_map, m_player->getPlayerRect());
}

void DugeonScene::render()
{
	m_Map1->render();
	m_aStar->render();
	m_player->render();
}
