#include "stdafx.h"
#include "TownScene.h"

TownScene::TownScene() : m_townMap(new townMap)
{
}

TownScene::~TownScene()
{
	delete m_townMap;
}

HRESULT TownScene::init()
{
	//imageInit();
	RECT playerStartRect;
	POINT init;
	init.x = 2400;
	init.y = 900;
	playerStartRect = RectMakeCenter(765, 500, 40, 40);
	m_townMap->init();
	PLAYER.setCharacPosition(playerStartRect);
	blackScene = IMAGEMANAGER->findImage("blackScene");
	CAMERAMANAGER->setCameraCenter(init);
	return S_OK;
}

void TownScene::release()
{
	PLAYER.release();
	m_townMap->release();
	CAMERAMANAGER->relaese();
	CAMERAMANAGER->releaseSingleton();
}

void TownScene::update()
{
	RECT temp;
	time = TIMEMANAGER->getElapsedTime();
	pastTime += time;
	
	playerCollision = RectMakeCenter(PLAYER.m_player._rc.left + CAMERAMANAGER->getCameraXY().x, PLAYER.m_player._rc.top + CAMERAMANAGER->getCameraXY().y, 40, 40);
	
	PLAYER.update(m_townMap , true, playerCollision);
	m_townMap->update();

	if (IntersectRect(&temp, &playerCollision, &m_townMap->getChangeSceneRect()[0]))
	{
		isNextScene = true;
	}
}

void TownScene::render()
{
	colorRectangle(getMemDC(), playerCollision.left, playerCollision.top, WINSIZEX - 300, WINSIZEY / 2 + 180, 255, 0, 255);
	m_townMap->render();
	PLAYER.render(CAMERAMANAGER->getCameraDC());

	printText(CAMERAMANAGER->getCameraDC(), to_string(playerCollision.left).c_str(), "³ª´®½ºÄù¾î_ac Bold", 400, 400, 20, RGB(255, 255, 255), true, RGB(255, 0, 255));
	printText(CAMERAMANAGER->getCameraDC(), to_string(playerCollision.top).c_str(), "³ª´®½ºÄù¾î_ac Bold", 400, 500, 20, RGB(255, 255, 255), true, RGB(255, 0, 255));
	
	if (alpha >= 240)
	{
		isNextScene = false;
		SCENEMANAGER->scenePush("ToDungeonScene",false);
	}

	if (isNextScene)
	{
		if (addDeleyTime < pastTime && alpha < 230)
		{
			alpha += 35;
			
			pastTime = 0.0f;
		}
		blackScene->alphaRender(CAMERAMANAGER->getCameraDC(), 0, 0, alpha);
		blackScene->alphaRender(getMemDC(),CAMERAMANAGER->getCameraXY().x,CAMERAMANAGER->getCameraXY().y, alpha);
	}

}
