#include "stdafx.h"
#include "invenScene.h"


invenScene::invenScene() : m_inven(new inven)
{
}

invenScene::~invenScene()
{
	delete m_inven;
}

HRESULT invenScene::init()
{
	m_inven->init();
	m_inven->invenRectSet();
	imgInven = IMAGEMANAGER->findImage("ÀÎº¥");


	return S_OK;
}

void invenScene::release()
{
	IMAGEMANAGER->deleteAll();
}

void invenScene::update()
{
	m_inven->update();
}

void invenScene::render(int _playerHp, int _playerAttack, int _Dev, int _playerSpeed)
{
	imgInven->render(CAMERAMANAGER->getCameraDC(), (WINSIZEX - imgInven->getWidth()) / 2 ,  (WINSIZEY - imgInven->getHeight()) / 2);
	m_inven->render(_playerHp, _playerAttack, _Dev, _playerSpeed);


}
