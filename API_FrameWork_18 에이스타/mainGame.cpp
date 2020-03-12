#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
	:m_mapTool(new mapTool), m_startMenuScene(new startMenuScene), m_mapToolScene(new mapToolScene),
	m_maptoolKind(ONCETILE) , m_DungeonScene1(new DugeonScene)
{
}


mainGame::~mainGame()
{
	delete m_mapTool;
	delete m_mapToolScene;
	delete m_DungeonScene1;
	delete m_startMenuScene;
}

HRESULT mainGame::init()
{
	gameNode::init(true);

	//===================//
	//��ŸƮ���θ޴��̹�6��//
	//===================//
	IMAGEMANAGER->addFrameImage("���۸޴��������", "images/Menu/menuIntro.bmp", 20480, WINSIZEY, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���۸޴�������", "images/Menu/menububble.bmp", 20480, WINSIZEY, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���۸޴��繮", "images/Menu/intro2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ӷΰ�", "images/Menu/gameLogo.bmp", 302 * 2, 160 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���۸޴�����ui_L", "images/Menu/choiceIcon.bmp", 22 * 2, 21 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���۸޴�����ui_R", "images/Menu/choiceIconR.bmp", 22 * 2, 21 * 2, true, RGB(255, 0, 255));


	////===================//
	////������ ���̽� �̹��� //
	////===================//
	IMAGEMANAGER->addImage("��������", "images/Maptool/Dungeon/Base/MapToolMain.bmp", 215 * 2, 285 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ڽ�����", "images/Maptool/Dungeon/Base/BOXCLOSE.bmp", 281 * 2, 273 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����������", "images/Maptool/Dungeon/Base/nextPage.bmp", 32 * 2, 32 * 2, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addImage("����������", "images/Maptool/Dungeon/Base/beforePage.bmp", 32 * 2, 32 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̺�ε��ư", "images/Maptool/Menu/saveLoad.bmp", 580 / 3, 191 / 3, true, RGB(255, 0, 255));

	//// - ������( �ٴ�, ��)
	IMAGEMANAGER->addImage("ic������1", "images/Maptool/Dungeon/Flow/Room1.bmp", 576 / 8, 360 / 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ic������2", "images/Maptool/Dungeon/Flow/Room2.bmp", 576 / 8, 360 / 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ic������", "images/Maptool/Dungeon/Flow/bossRoom.bmp", 576 / 8, 360 / 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ic������1", "images/Maptool/Dungeon/Wall/Wall1.bmp", 576 / 4, 360 / 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ic������2", "images/Maptool/Dungeon/Wall/Wall2.bmp", 576 / 4, 360 / 4, true, RGB(255, 0, 255));

	////  ����ִ� Ÿ��
	IMAGEMANAGER->addImage("������1", "images/Maptool/Dungeon/Flow/Room1.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������2", "images/Maptool/Dungeon/Flow/Room2.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/Maptool/Dungeon/Flow/bossRoom.bmp", WINSIZEX*2, WINSIZEY*2, true, RGB(255, 0, 255));

	//// 2. ��(wall)		
	IMAGEMANAGER->addImage("������1", "images/Maptool/Dungeon/Wall/Wall1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������2", "images/Maptool/Dungeon/Wall/Wall2.bmp", WINSIZEX *2, WINSIZEY *2, true, RGB(255, 0, 255));

	//// 3. ������Ʈ(������)
	IMAGEMANAGER->addFrameImage("����Ǵ¿�����Ʈ", "images/Maptool/Dungeon/object/throwObjectTile.bmp", 320, 320, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����ȵǴ¿�����Ʈ1", "images/Maptool/Dungeon/object/ObjectTiles1.bmp", 320, 320, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����ȵǴ¿�����Ʈ2", "images/Maptool/Dungeon/object/ObjectTiles2.bmp", 320, 320, 4, 4, true, RGB(255, 0, 255));

	// 4. �꼺 �ͷ���
	IMAGEMANAGER->addFrameImage("�꼺�ͷ���", "images/Maptool/Dungeon/Terrain/terrainTile.bmp", 320, 160, 4, 2, true, RGB(255, 0, 255));

	////--------------------------------------------------------------------------------------------------------
	ANIMATIONMANAGER->addDefAnimation("bubbleAni1", "���۸޴��������", 8, false, true);
	ANIMATIONMANAGER->addDefAnimation("bubbleAni2", "���۸޴�������", 8, false, true);


	////--------------------------------------------------------------------------------------------------------
	SCENEMANAGER->addScene("StartSceneMenu", m_startMenuScene);
	SCENEMANAGER->addScene("MapToolScene", m_mapToolScene);
	SCENEMANAGER->addScene("DungeonScene1", m_DungeonScene1);

	SCENEMANAGER->scenePush("StartSceneMenu");
	m_mapTool->init();
	//--------------------------------------------------------------------------------------------------------

	// ī�޶� ���ÿ� RECT
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
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			SCENEMANAGER->scenePush("DungeonScene1");
		}

		break;

	case MAPTOOL:
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			SCENEMANAGER->scenePush("MapToolScene");
	
		}
		break;

	case END:

		break;

	default:
		break;

	}


	

}

void mainGame::render(/*HDC hdc*/)
{
	//��� ��Ʈ��
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY/2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===================================================
	SCENEMANAGER->render();
	TIMEMANAGER->render(CAMERAMANAGER->getCameraDC());

	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	Rectangle(getMemDC(), rc2.left, rc2.top, rc2.right, rc2.bottom);
	//=================================================
	//������� ������ HDC�� �׸���.(�ǵ帮������.)
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y -WINSIZEY / 2, WINSIZEX, WINSIZEY);
}

void mainGame::setMap()
{
  m_mapToolScene->setMap();
}









