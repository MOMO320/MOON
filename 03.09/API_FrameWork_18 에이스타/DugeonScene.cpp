#include "stdafx.h"
#include "DugeonScene.h"

DugeonScene::DugeonScene()
	:m_dunGeonMap(new dungeonMap) , m_player(new player)
{
	m_player->init();
}

DugeonScene::~DugeonScene()
{
	delete m_dunGeonMap;
	delete m_player;
}

HRESULT DugeonScene::init()
{
	m_dunGeonMap->init();
	
	//===============//
	//	 playerºÒ·³  //
	//===============//
	m_player->setTankMapMemoryAdress(m_dunGeonMap);
	m_player->setCharacPosition(m_dunGeonMap->getMap()[m_dunGeonMap->getPosFirst()].m_rc);

	return S_OK;
}

void DugeonScene::release()
{
	SAFE_DELETE(m_dunGeonMap);
	SAFE_DELETE(m_player);
}

void DugeonScene::update()
{
	m_player->update();
	m_dunGeonMap->update();
}

void DugeonScene::render()
{
	m_dunGeonMap->render();
	m_player->render();
}
