#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
	:m_mapTool(new mapTool), m_startMenuScene(new startMenuScene), m_mapToolScene(new mapToolScene)
{
}


mainGame::~mainGame()
{
	delete m_mapTool;
	delete m_mapToolScene;
}

HRESULT mainGame::init()
{
	gameNode::init(true);

	//===================//
	//스타트메인메뉴이미6지//
	//===================//
	IMAGEMANAGER->addFrameImage("시작메뉴버블바탕", "images/Menu/menuIntro.bmp", 20480, WINSIZEY, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("시작메뉴버블위", "images/Menu/menububble.bmp", 20480, WINSIZEY, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("시작메뉴양문", "images/Menu/intro2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("게임로고", "images/Menu/gameLogo.bmp", 302 * 2, 160 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("시작메뉴선택ui_L", "images/Menu/choiceIcon.bmp", 22 * 2, 21 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("시작메뉴선택ui_R", "images/Menu/choiceIconR.bmp", 22 * 2, 21 * 2, true, RGB(255, 0, 255));


	////===================//
	////맵툴용 베이스 이미지 //
	////===================//
	IMAGEMANAGER->addImage("맵툴메인", "images/Maptool/Dungeon/Base/MapToolMain.bmp", 215 * 2, 285 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("박스닫힘", "images/Maptool/Dungeon/Base/BOXCLOSE.bmp", 281 * 2, 273 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("다음페이지", "images/Maptool/Dungeon/Base/nextPage.bmp", 32 * 2, 32 * 2, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addImage("이전페이지", "images/Maptool/Dungeon/Base/beforePage.bmp", 32 * 2, 32 * 2, true, RGB(255, 0, 255));


	//// - 아이콘( 바닥, 벽)
	IMAGEMANAGER->addImage("ic던전룸1", "images/Maptool/Dungeon/Flow/Room1.bmp", 576 / 8, 360 / 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ic던전룸2", "images/Maptool/Dungeon/Flow/Room2.bmp", 576 / 8, 360 / 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ic보스룸", "images/Maptool/Dungeon/Flow/bossRoom.bmp", 576 / 8, 360 / 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ic던전벽1", "images/Maptool/Dungeon/Wall/Wall1.bmp", 576 / 4, 360 / 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ic던전벽2", "images/Maptool/Dungeon/Wall/Wall2.bmp", 576 / 4, 360 / 4, true, RGB(255, 0, 255));

	////  깔아주는 타일
	IMAGEMANAGER->addImage("던전룸1", "images/Maptool/Dungeon/Flow/Room1.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("던전룸2", "images/Maptool/Dungeon/Flow/Room2.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스룸", "images/Maptool/Dungeon/Flow/bossRoom.bmp", 1280, 720, true, RGB(255, 0, 255));

	//// 2. 벽(wall)		
	IMAGEMANAGER->addImage("던전벽1", "images/Maptool/Dungeon/Wall/Wall1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("던전벽2", "images/Maptool/Dungeon/Wall/Wall2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//// 3. 오브젝트(던전용)
	//IMAGEMANAGER->addImage(""

	////--------------------------------------------------------------------------------------------------------
	ANIMATIONMANAGER->addDefAnimation("bubbleAni1", "시작메뉴버블바탕", 8, false, true);
	ANIMATIONMANAGER->addDefAnimation("bubbleAni2", "시작메뉴버블위", 8, false, true);


	////--------------------------------------------------------------------------------------------------------
	SCENEMANAGER->addScene("StartSceneMenu", m_startMenuScene);
	SCENEMANAGER->addScene("MapToolScene", m_mapToolScene);

	SCENEMANAGER->changeScene("StartSceneMenu");
	m_mapTool->init();
	//--------------------------------------------------------------------------------------------------------

	// 카메라 예시용 RECT
	//rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	//rc2 = RectMakeCenter(WINSIZEX * 2, 1000, 100, 100);


	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	SCENEMANAGER->release();
}

void mainGame::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	ANIMATIONMANAGER->update();

	switch (m_startMenuScene->choiceMenu())
	{
	case GAME:

		break;

	case MAPTOOL:
		if (KEYMANAGER->isOnceKeyDown('Z'))
			SCENEMANAGER->scenePush("MapToolScene");
		break;

	case END:

		break;

	default:
		break;

	}


	// 카메라만 움직이게 하는 코드
	//if (KEYMANAGER->isStayKeyDown(VK_LEFT) && CAMERAMANAGER->getCameraXY().x > 0)
	//{
	//	CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x - 50, CAMERAMANAGER->getCameraCenter().y));
	//}
	//
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	//{
	//	CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x + 50, CAMERAMANAGER->getCameraCenter().y));
	//}
	//
	//if (KEYMANAGER->isStayKeyDown(VK_UP) && CAMERAMANAGER->getCameraXY().y > 0)
	//{
	//	CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y - 50));
	//}
	//
	//if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	//{
	//	CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y + 50));
	//}

}

void mainGame::render(/*HDC hdc*/)
{
	//흰색 비트맵
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY/2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===================================================
	SCENEMANAGER->render();
	TIMEMANAGER->render(CAMERAMANAGER->getCameraDC());

	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	Rectangle(getMemDC(), rc2.left, rc2.top, rc2.right, rc2.bottom);
	//=================================================
	//백버퍼의 내용을 HDC에 그린다.(건드리지말것.)
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y -WINSIZEY / 2, WINSIZEX, WINSIZEY);
}

void mainGame::setMap()
{
	m_mapToolScene->setMap();
}









