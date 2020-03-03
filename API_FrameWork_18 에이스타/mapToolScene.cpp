#include "stdafx.h"
#include "mapToolScene.h"

mapToolScene::mapToolScene()
	: m_mapTool(new mapTool)
{
}

mapToolScene::~mapToolScene()
{
	delete m_mapTool;
}

HRESULT mapToolScene::init()
{
	m_mapTool->init();
	return S_OK;
}

void mapToolScene::release()
{
}

void mapToolScene::update()
{

}

void mapToolScene::render()
{
	m_mapTool->render();
	m_mapTool->debugRender();
	m_mapTool->mapToolMenuRender();
}

//void mapToolScene::setMap()
//{
//	m_mapTool->setMap();
//}

