#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
	:m_mapTool(new mapTool), m_startMenuScene(new startMenuScene), m_mapToolScene(new mapToolScene),
	m_maptoolKind(ONCETILE) , m_DungeonScene1(new DugeonScene) , m_scene(new scene) , m_DungeonScene2(new DugeonScene2)
{
}


mainGame::~mainGame()
{
	delete m_mapTool;
	delete m_mapToolScene;
	delete m_DungeonScene1;
	delete m_startMenuScene;
	delete m_scene;
	delete m_DungeonScene2;
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

	//===================//
    // plyaer ���� �̹��� //
    //===================//
	IMAGEMANAGER->addFrameImage("dungeonPlayer", "images/Player/dungeonCharact/dungeonCharact.bmp", 1200 + 300, 1560 + 390, 10, 13, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addFrameImage("swordPlayer", "images/Player/dungeonCharact/swordCharact.bmp", 1320 + 330 , 480  + 120, 11, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bowPlayer", "images/Player/dungeonCharact/will_bow.bmp", 1080 + 270, 480 +120 , 9, 4, true, RGB(255, 0, 255));
	//===================//
	// plyaer ���� �̹��� //
	//===================//
	IMAGEMANAGER->addFrameImage("townPlayer", "images/Player/townCharact/shopPlayer.bmp", 1300 + 325 , 1560 + 390, 10, 12, true, RGB(255, 0, 255));

	// player ȭ�� (arrow) - ANI arrowUp
	IMAGEMANAGER->addFrameImage("upArrowMan", "images/arrowUp150.bmp", 79 * 2, 32 * 2 , 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("downArrowMan", "images/arrowDown150.bmp", 79 *2 ,32 *2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrowLeft", "images/object/arrows/arrowLeft2.bmp", 125 *2,  12 * 2,5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrowRight", "images/object/arrows/arrowRight2.bmp", 125 * 2, 12 *2, 5, 1, true, RGB(255, 0, 255));
	// player ȭ�� 
	IMAGEMANAGER->addImage("arrowOnceUp","images/ArrowUpMAN.bmp", 7 + 3, 25 + 12,true , RGB(255,0,255));
	IMAGEMANAGER->addImage("arrowOnceDown","images/ArrowDownMAN.bmp", 7 + 3, 25 + 12,true , RGB(255,0,255));
	IMAGEMANAGER->addImage("ARLeft", "images/object/arrows/ARLeft.bmp", 25 +12, 7+3,true , RGB(255,0,255));
	IMAGEMANAGER->addImage("ARRight", "images/object/arrows/ARRight.bmp", 25 + 12, 7 + 3,true , RGB(255,0,255));

	// Enemy �̹��� ( �̴Ͻ����� )
	IMAGEMANAGER->addFrameImage("miniSlime", "images/Enemies/zeli/mini.bmp", 76 * 2, 13 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("miniSlimeDeath", "images/Enemies/zeli/deathMiniSlime.bmp", 13 * 2, 11 * 2, true, RGB(255, 0, 255));

	// Enemy �̹��� ( ���� )
	IMAGEMANAGER->addFrameImage("flea", "images/Enemies/zeli/what.bmp", 66 * 2, 24 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fleaDeath", "images/Enemies/zeli/whatDeath.bmp", 22 * 2, 24 * 2, true, RGB(255, 0, 255));

	// Enemy �̹��� ( ����ī �ö�� ) && ����ī �ö�� ������Ʈ ����
	IMAGEMANAGER->addFrameImage("bazookaFlower_bottom", "images/Enemies/flowerbajookaPo/bottomBajooka.bmp", 660 * 2 + 660/4, 232 * 2 + 232/4, 11, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bazookaFlower_up", "images/Enemies/flowerbajookaPo/topBajooka.bmp", 660 * 2 + 660/4, 232 * 2 + 232/4, 11, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bazookaFlower_right", "images/Enemies/flowerbajookaPo/rightBajooka.bmp", 720 * 2 + 720/4, 232 * 2 + 232/4, 12, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bazookaFlower_left", "images/Enemies/flowerbajookaPo/leftBajooka.bmp", 720 * 2 + 720/4, 232 * 2 + 232/4, 12, 4, true, RGB(255, 0, 255));
	// ������Ʈ
	IMAGEMANAGER->addImage("bazookaObject", "images/Enemies/flowerbajookaPo/bajooObject.bmp", 10 * 2, 8 * 2, true, RGB(255, 0, 255)); 
	// ������Ʈ �浹�� ������
	IMAGEMANAGER->addFrameImage("bazookaObjectFrame", "images/Enemies/flowerbajookaPo/bajooObjectFrame.bmp", 60 * 2, 21 * 2, 3, 1, true, RGB(255, 0, 255));

	// mushRoom �� �̹��� 
	IMAGEMANAGER->addFrameImage("mushRoom", "images/Enemies/mushroom/mushRoom.bmp", 561*2 , 108*2 ,17,3,true, RGB(255,0,255));


	////--------------------------------------------------------------------------------------------------------
	ANIMATIONMANAGER->addDefAnimation("bubbleAni1", "���۸޴��������", 8, false, true);
	ANIMATIONMANAGER->addDefAnimation("bubbleAni2", "���۸޴�������", 8, false, true);
	aniArray();

	////--------------------------------------------------------------------------------------------------------
	SCENEMANAGER->addScene("StartSceneMenu", m_startMenuScene);
	SCENEMANAGER->addScene("MapToolScene", m_mapToolScene);
	SCENEMANAGER->addScene("DungeonScene1", m_DungeonScene1);
	SCENEMANAGER->addScene("DungeonScene2", m_DungeonScene2);

	SCENEMANAGER->scenePush("StartSceneMenu");
	PLAYER.init();
	m_mapTool->init();
	m_scene->init();
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
			SCENEMANAGER->scenePush("DungeonScene2");
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
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->scenePush("DungeonScene2");
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

void mainGame::aniArray()
{
	//===================//
	// plyaer ���� ANI 1 //
	//===================//
	ANIMATIONMANAGER->addAnimation("Player_upWalk", "dungeonPlayer", 0, 7, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_downWalk", "dungeonPlayer", 10, 17, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_rightWalk", "dungeonPlayer", 20, 27, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_leftWalk", "dungeonPlayer", 30, 37, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_rightRoll", "dungeonPlayer", 40, 47, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_leftRoll", "dungeonPlayer", 50, 57, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_upRoll", "dungeonPlayer", 60, 67, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_downRoll", "dungeonPlayer", 70, 77, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_rightIdle", "dungeonPlayer", 80, 89, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_leftIdle", "dungeonPlayer", 90, 99, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_upIdle", "dungeonPlayer", 100, 109, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_downIdle", "dungeonPlayer", 110, 119, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_die", "dungeonPlayer", 120, 129, 10, false, true);

	// swordPlayer //
	ANIMATIONMANAGER->addAnimation("Player_swordUpCombo1", "swordPlayer", 0, 5, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_swordUpCombo2", "swordPlayer", 6, 10, 10, false, true);

	ANIMATIONMANAGER->addAnimation("Player_swordDownCombo1", "swordPlayer", 11, 17,13, false, true);
	ANIMATIONMANAGER->addAnimation("Player_swordDownCombo2", "swordPlayer", 18, 21, 10, false, true);
	
	ANIMATIONMANAGER->addAnimation("Player_swordRightCombo1", "swordPlayer", 22, 27, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_swordRightCombo2", "swordPlayer", 28, 32, 10, false, true);
	
	ANIMATIONMANAGER->addAnimation("Player_swordLeftCombo1", "swordPlayer", 33, 38, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_swordLeftCombo2", "swordPlayer", 39, 43, 10, false, true);

	// bowPlayer //
	ANIMATIONMANAGER->addAnimation("Player_bowUp", "bowPlayer", 0, 8, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_bowDown", "bowPlayer", 9, 17, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_bowRight", "bowPlayer", 18, 26, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_bowLeft", "bowPlayer", 27, 35, 10, false, true);

	// arrow //
	ANIMATIONMANAGER->addDefAnimation("Arrow_Left"	, "arrowLeft",10, false, true);
	ANIMATIONMANAGER->addDefAnimation("Arrow_Right"	, "arrowRight", 10, false, true);
	ANIMATIONMANAGER->addAnimation   ("Arrow_Up"	, "upArrowMan", 0, 4,10, false, true);
	ANIMATIONMANAGER->addAnimation   ("Arrow_Down"	, "downArrowMan",0 ,4 ,10, false, true);
	
	// shopPlayer //
	ANIMATIONMANAGER->addAnimation("Player_TwonLeftWalk", "townPlayer", 0, 7, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_TwonLeftIdle", "townPlayer", 10, 19, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_TwonRihgtWalk", "townPlayer", 20, 27, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_TwonRightIdle", "townPlayer", 30, 39, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_TwonDownWalk", "townPlayer", 40, 47, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_TwonDownIdle", "townPlayer", 50, 59, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_TwonUpWalk", "townPlayer", 60, 67, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_TwonUpIdle", "townPlayer", 70, 79, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_TwonLeftRoll", "townPlayer", 80, 87, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_TwonRightRoll", "townPlayer", 90, 97, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_TwonDownRoll", "townPlayer", 100, 107, 10, false, true);
	ANIMATIONMANAGER->addAnimation("Player_TwonUpRoll", "townPlayer", 110, 117, 10, false, true);

	// ������ && ���� �ִϸ��̼� 
	ANIMATIONMANAGER->addDefAnimation("miniSlime_Ani", "miniSlime", 10, false, true);
	ANIMATIONMANAGER->addDefAnimation("flea_Ani", "flea", 10, false, true);

	// ����ī �ö�� �ִϸ��̼� (������Ʈ ����)
	/* bottom */
	ANIMATIONMANAGER->addAnimation("bazooka_Bottom_Move", "bazookaFlower_bottom", 0, 7, 5, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_Bottom_AttackReady", "bazookaFlower_bottom", 11, 18,8, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_Bottom_Attack", "bazookaFlower_bottom", 22, 29, 4, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_Bottom_Reload", "bazookaFlower_bottom", 33, 36, 8, false, true);

	/* top */
	ANIMATIONMANAGER->addAnimation("bazooka_Top_Move", "bazookaFlower_up", 0, 10, 5, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_Top_Attack", "bazookaFlower_up", 11, 18,8, false, true);
	
	/* right */
	ANIMATIONMANAGER->addAnimation("bazooka_right_Move", "bazookaFlower_right", 0, 8, 5, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_right_Attack", "bazookaFlower_right", 12, 18, 8, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_right_Reload", "bazookaFlower_right", 24, 35, 8, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_right_AttackReady", "bazookaFlower_right", 36, 47, 8, false, true);

	/* left */
	ANIMATIONMANAGER->addAnimation("bazooka_left_Move", "bazookaFlower_left", 0, 8, 5, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_left_Attack", "bazookaFlower_left", 12, 19, 8, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_left_AttackReady", "bazookaFlower_left", 24, 35,8, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_left_Reload", "bazookaFlower_left", 36, 47, 8, false, true);

	/* ����ī ������Ʈ */
	ANIMATIONMANAGER->addAnimation("bazooka_object_boom", "bazookaObjectFrame", 0,2,10, false, true);

	// ���� ���� �ִϸ��̼�
	ANIMATIONMANAGER->addAnimation("mushRoom_wait", "mushRoom", 0, 7, 7, false, true);
	ANIMATIONMANAGER->addAnimation("mushRoom_Move1", "mushRoom", 17, 33, 10, false, true);
	ANIMATIONMANAGER->addAnimation("mushRoom_Move2", "mushRoom", 34, 45, 10, false, true);

}









