#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
	:m_mapTool(new mapTool), m_startMenuScene(new startMenuScene), m_mapToolScene(new mapToolScene),
	m_maptoolKind(ONCETILE) , m_DungeonScene1(new DugeonScene) , m_scene(new scene) , m_DungeonScene2(new DugeonScene2),
	m_DungeonScene3(new DugeonScene3) , c_townScene(new TownScene) ,c_toDungeonScene(new ToDungeonScene), c_firstScene(new firstDungeonScene),
	c_invenScene(new invenScene) 
{
}


mainGame::~mainGame()
{
	delete m_mapTool;
	delete m_mapToolScene;
	delete m_DungeonScene1;
	delete m_DungeonScene2;
	delete m_DungeonScene3;
	delete m_startMenuScene;
	delete m_scene;
	delete c_townScene;
	delete c_toDungeonScene;
	delete c_firstScene;
	delete c_invenScene;
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
	IMAGEMANAGER->addImage("세이브로드버튼", "images/Maptool/Menu/saveLoad.bmp", 580 / 3, 191 / 3, true, RGB(255, 0, 255));

	//// - 아이콘( 바닥, 벽)
	IMAGEMANAGER->addImage("ic던전룸1", "images/Maptool/Dungeon/Flow/Room1.bmp", 576 / 8, 360 / 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ic던전룸2", "images/Maptool/Dungeon/Flow/Room2.bmp", 576 / 8, 360 / 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ic보스룸", "images/Maptool/Dungeon/Flow/bossRoom.bmp", 576 / 8, 360 / 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ic던전벽1", "images/Maptool/Dungeon/Wall/Wall1.bmp", 576 / 4, 360 / 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ic던전벽2", "images/Maptool/Dungeon/Wall/Wall2.bmp", 576 / 4, 360 / 4, true, RGB(255, 0, 255));

	////  깔아주는 타일
	IMAGEMANAGER->addImage("던전룸1", "images/Maptool/Dungeon/Flow/Room1.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("던전룸2", "images/Maptool/Dungeon/Flow/Room2.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스룸", "images/Maptool/Dungeon/Flow/bossRoom.bmp", WINSIZEX*2, WINSIZEY*2, true, RGB(255, 0, 255));

	//// 2. 벽(wall)		
	IMAGEMANAGER->addImage("던전벽1", "images/Maptool/Dungeon/Wall/Wall1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("던전벽2", "images/Maptool/Dungeon/Wall/Wall2.bmp", WINSIZEX *2, WINSIZEY *2, true, RGB(255, 0, 255));

	//// 3. 오브젝트(던전용)
	IMAGEMANAGER->addFrameImage("통과되는오브젝트", "images/Maptool/Dungeon/object/throwObjectTile.bmp", 320, 320, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("통과안되는오브젝트1", "images/Maptool/Dungeon/object/ObjectTiles1.bmp", 320, 320, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("통과안되는오브젝트2", "images/Maptool/Dungeon/object/ObjectTiles2.bmp", 320, 320, 4, 4, true, RGB(255, 0, 255));

	// 4. 산성 터레인
	IMAGEMANAGER->addFrameImage("산성터레인", "images/Maptool/Dungeon/Terrain/terrainTile.bmp", 320, 160, 4, 2, true, RGB(255, 0, 255));

	//===================//
    // plyaer 던전 이미지 //
    //===================//
	IMAGEMANAGER->addFrameImage("dungeonPlayer", "images/Player/dungeonCharact/dungeonCharact.bmp", 1200 + 300, 1560 + 390, 10, 13, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addFrameImage("dungeonPlayerBig", "images/Player/dungeonCharact/dungeonCharact.bmp", (1200 + 300)*2, (1560 + 390)*2, 10, 13, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addFrameImage("swordPlayer", "images/Player/dungeonCharact/swordCharact.bmp", 1320 + 330 , 480  + 120, 11, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bowPlayer", "images/Player/dungeonCharact/will_bow.bmp", 1080 + 270, 480 +120 , 9, 4, true, RGB(255, 0, 255));
	//===================//
	// plyaer 마을 이미지 //
	//===================//
	IMAGEMANAGER->addFrameImage("townPlayer", "images/Player/townCharact/shopPlayer.bmp", 1300 + 325 , 1560 + 390, 10, 12, true, RGB(255, 0, 255));

	// player 화살 (arrow) - ANI arrowUp
	IMAGEMANAGER->addFrameImage("upArrowMan", "images/arrowUp150.bmp", 79 * 2, 32 * 2 , 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("downArrowMan", "images/arrowDown150.bmp", 79 *2 ,32 *2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrowLeft", "images/object/arrows/arrowLeft2.bmp", 125 *2,  12 * 2,5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrowRight", "images/object/arrows/arrowRight2.bmp", 125 * 2, 12 *2, 5, 1, true, RGB(255, 0, 255));
	// player 화살 
	IMAGEMANAGER->addImage("arrowOnceUp","images/ArrowUpMAN.bmp", 7 + 3, 25 + 12,true , RGB(255,0,255));
	IMAGEMANAGER->addImage("arrowOnceDown","images/ArrowDownMAN.bmp", 7 + 3, 25 + 12,true , RGB(255,0,255));
	IMAGEMANAGER->addImage("ARLeft", "images/object/arrows/ARLeft.bmp", 25 +12, 7+3,true , RGB(255,0,255));
	IMAGEMANAGER->addImage("ARRight", "images/object/arrows/ARRight.bmp", 25 + 12, 7 + 3,true , RGB(255,0,255));

	// player 던전 안에 들어가는 애니메이션
	IMAGEMANAGER->addFrameImage("playerIntoDungeon", "images/Player/townCharact/intoDungeon.bmp", 710*3, 160*3, 10, 2, true, RGB(255, 0, 255));


	// Enemy 이미지 ( 미니슬라임 )
	IMAGEMANAGER->addFrameImage("miniSlime", "images/Enemies/zeli/mini.bmp", 76 * 2, 13 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("miniSlimeDeath", "images/Enemies/zeli/deathMiniSlime.bmp", 13 * 2, 11 * 2, true, RGB(255, 0, 255));

	// Enemy 이미지 ( 벼룩 )
	IMAGEMANAGER->addFrameImage("flea", "images/Enemies/zeli/what.bmp", 66 * 2, 24 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fleaDeath", "images/Enemies/zeli/whatDeath.bmp", 22 * 2, 24 * 2, true, RGB(255, 0, 255));

	// Enemy 이미지 ( 바주카 플라워 ) && 바주카 플라워 오브젝트 넣음
	IMAGEMANAGER->addFrameImage("bazookaFlower_bottom", "images/Enemies/flowerbajookaPo/bottomBajooka.bmp", 660 * 2 + 660/4, 232 * 2 + 232/4, 11, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bazookaFlower_up", "images/Enemies/flowerbajookaPo/topBajooka.bmp", 660 * 2 + 660/4, 232 * 2 + 232/4, 11, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bazookaFlower_right", "images/Enemies/flowerbajookaPo/rightBajooka.bmp", 720 * 2 + 720/4, 232 * 2 + 232/4, 12, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bazookaFlower_left", "images/Enemies/flowerbajookaPo/leftBajooka.bmp", 720 * 2 + 720/4, 232 * 2 + 232/4, 12, 4, true, RGB(255, 0, 255));
	// 오브젝트
	IMAGEMANAGER->addImage("bazookaObject", "images/Enemies/flowerbajookaPo/bajooObject.bmp", 10 * 2, 8 * 2, true, RGB(255, 0, 255)); 
	// 오브젝트 충돌시 프레임
	IMAGEMANAGER->addFrameImage("bazookaObjectFrame", "images/Enemies/flowerbajookaPo/bajooObjectFrame.bmp", 60 * 2, 21 * 2, 3, 1, true, RGB(255, 0, 255));

	// mushRoom 적 이미지 
	IMAGEMANAGER->addFrameImage("mushRoom", "images/Enemies/mushroom/mushRoom.bmp", 561*2 , 108*2 ,17,3,true, RGB(255,0,255));

	// 모모적 이미지
	/*Bottom*/
	IMAGEMANAGER->addFrameImage("momoEnemy_Bottom", "images/Enemies/momoMushroom/momoBottom.bmp", 540 * 2, 244 * 2, 12, 4, true, RGB(255, 0, 255));
	/*Top*/
	IMAGEMANAGER->addFrameImage("momoEnemy_Top", "images/Enemies/momoMushroom/momoTop.bmp", 540 * 2, 244 * 2, 12, 4, true, RGB(255, 0, 255));
	/*Right*/
	IMAGEMANAGER->addFrameImage("momoEnemy_Right", "images/Enemies/momoMushroom/momoRight.bmp", 540 * 2, 244 * 2, 12, 4, true, RGB(255, 0, 255));
	/*Left*/
	IMAGEMANAGER->addFrameImage("momoEnemy_Left", "images/Enemies/momoMushroom/momoLeft.bmp", 540 * 2, 244 * 2, 12, 4, true, RGB(255, 0, 255));
	
	/* object */
	IMAGEMANAGER->addImage("momoObject", "images/Enemies/momoMushroom/momoObject.bmp", 11 * 2, 11 * 2, true, RGB(255, 0, 255)); 
	/* object Boom */
	IMAGEMANAGER->addFrameImage("momoObjectBoom", "images/Enemies/momoMushroom/momoObjectBomm.bmp", 120 * 2, 25 * 2, 5, 1, true, RGB(255, 0, 255));


	// 날파리 enemy
	IMAGEMANAGER->addFrameImage("flyEnemy", "images/Enemies/fly/flyEnemy.bmp", 756 * 2, 248 * 2, 14, 4, true, RGB(255, 0, 255));


	//타운씬 이미지 작업
	IMAGEMANAGER->addImage("town", "images/Maptool/Town/town.bmp", 1301 * 3, 1067 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town2", "images/Maptool/Town/town2.bmp", 1200*3, 1024*3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town2Up", "images/Maptool/Town/town2Up.bmp", 703 * 3, 851 * 3, true, RGB(255, 0, 255));
	//ui바
	IMAGEMANAGER->addImage("hpBarBack", "images/Ui/hpBar.bmp", 160 + 40, 35 + 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hpBar", "images/Ui/blood.bmp", 125 +31, 35 + 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("moneyUi", "images/Ui/moneyUi.bmp", 49 + 24, 45 + 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cashUi", "images/Ui/cashUI.bmp", 28 * 2, 28 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("aButtonUi", "images/Ui/aButton.bmp", 24 * 2, 25 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("iButtonUi", "images/Ui/iButton.bmp", 24 * 2, 25 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("qButtonUi", "images/Ui/qButton.bmp", 24 * 2, 25 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("backRoundUi", "images/Ui/backRound.bmp", 49 +24, 45+22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("invenButtonUi", "images/Ui/inventorybutton.bmp", 49 + 24, 45 + 22, true, RGB(255, 0, 255));

	// 아이템 이미지
	IMAGEMANAGER->addImage("훈련용단검", "images/items/훈련용단검.bmp", 32*2, 32*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레임보우", "images/items/플레임보우.bmp", 32*2, 32*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("중간포션", "images/items/중간포션.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item1", "images/items/item1.bmp", 20*3, 20*3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item2", "images/items/item2.bmp", 20*3, 20*3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item3", "images/items/item3.bmp", 20*3, 20*3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item4", "images/items/item4.bmp", 20*3, 22*3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item5", "images/items/item5.bmp", 20*3, 20*3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item6", "images/items/item6.bmp", 20*3, 22*3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item7", "images/items/item7.bmp", 20*3, 22*3, true, RGB(255, 0, 255));
	
	// inven 작업
	IMAGEMANAGER->addImage("인벤", "images/inven/inven.bmp", 518 * 2, 314 * 2, true, RGB(255, 0, 255));


	// 던전 밖 문
	IMAGEMANAGER->addFrameImage("openOutDoor", "images/Maptool/Town/door.bmp", 710*3, 63*3, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("clostOutDoor", "images/Dungeon/door/closeFirstDorr.bmp", 700*3, 54*3, 10, 1, true, RGB(255, 0, 255));

	// 던전속 문 (포레스트)
	/*탑*/
	IMAGEMANAGER->addFrameImage("forestDoorClose", "images/Dungeon/door/basicDoor.bmp", 896 * 2, 70 * 2, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("forestDoorOpen", "images/Dungeon/door/basicDoor.bmp", 896 * 2, 70 * 2, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("forestDoorHead_up", "images/Dungeon/door/basicDoorHead.bmp", 896 * 2, 70 * 2, 7, 1, true, RGB(255, 0, 255));
	/*바텀*/
	IMAGEMANAGER->addFrameImage("forestDoor_Bottom", "images/Dungeon/door/basicDoor_bottom.bmp", 896 * 2, 70 * 2, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("forestDoorHead_Bottom", "images/Dungeon/door/basicDoorHead_bottom.bmp", 896 * 2, 70 * 2, 7, 1, true, RGB(255, 0, 255));

	// 씬넘어갈때 블랙
	IMAGEMANAGER->addImage("blackScene", "images/sceneBlack.bmp", 1280, 720, true, RGB(255, 0, 255));

	// 던전제목(subject)
	IMAGEMANAGER->addFrameImage("subject", "images/subject.bmp", 2050 * 2, 52 * 2, 10, 1, true, RGB(255, 0, 255)); 

	// 인밴 커서
	IMAGEMANAGER->addImage("cusor", "images/cusor1.bmp", 32 * 2, 32 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ChooseCusor", "images/chooseCusor.bmp", 36*2, 36* 2, true, RGB(255, 0, 255));

	// 사운드 작업
	SOUNDMANAGER->addSound("introSound", "sound/main/introSound.mp3", true, true);
	SOUNDMANAGER->addSound("windTown", "sound/바람부는곳/dungeon_entrance_wind_ambient-resources.assets-4656.wav", true, true);
	// 던전 문들어가는 작업
	SOUNDMANAGER->addSound("DungeonOpendDoor", "sound/던전들어가는문/dungeon_entrance_slime_door_opened_loop-resources.assets-5109.wav", true, true);
	SOUNDMANAGER->addSound("DungeonIntoDoor", "sound/던전들어가는문/dungeon_entrance_slime_door_absorb-resources.assets-4979.wav", true, false);
	SOUNDMANAGER->addSound("DungeonCloseDoor", "sound/던전들어가는문/dungeon_entrance_slime_door_close-resources.assets-5001.wav", true, false);
	// 플레이어 공격 사운드
	SOUNDMANAGER->addSound("attackShortSword", "sound/will_bowAttack.wav", true, false);
	SOUNDMANAGER->addSound("attackBow", "sound/will_bowAttack.wav", true, false);
	// 던전 사운드
	SOUNDMANAGER->addSound("FirstDungeon", "sound/던전/forest_dungeon_floor-sharedassets0.assets-1006.wav", true, true);
	SOUNDMANAGER->addSound("FightDungeon", "sound/던전/forest_dungeon_floor_variation_1-sharedassets0.assets-995.wav", true, true);
	// 몬스터 사운드 
	SOUNDMANAGER->addSound("flyMonster", "sound/몬스터/forest_dungeon_bladetreesprout_attack-resources.assets-5134.wav", true, true);
	SOUNDMANAGER->addSound("momoMonster", "sound/몬스터/forest_dungeon_elaterium_attack-resources.assets-4921.wav", true, false);
	SOUNDMANAGER->addSound("bazookaMonster", "sound/몬스터/forest_dungeon_fruitturret_attack-resources.assets-4930.wav", true, false);
	SOUNDMANAGER->addSound("mushRoomMonster", "sound/몬스터/forest_dungeon_spinningmushroom_clash-resources.assets-4948.wav", true, false);
	
	


	////-----------------------------------------------------------------------------/---------------------------
	ANIMATIONMANAGER->addDefAnimation("bubbleAni1", "시작메뉴버블바탕", 8, false, true);
	ANIMATIONMANAGER->addDefAnimation("bubbleAni2", "시작메뉴버블위", 8, false, true);
	aniArray();

	////--------------------------------------------------------------------------------------------------------
	SCENEMANAGER->addScene("StartSceneMenu", m_startMenuScene);
	SCENEMANAGER->addScene("MapToolScene", m_mapToolScene);
	SCENEMANAGER->addScene("DungeonScene1", m_DungeonScene1);
	SCENEMANAGER->addScene("DungeonScene2", m_DungeonScene2);
	SCENEMANAGER->addScene("DungeonScene3", m_DungeonScene3);
	SCENEMANAGER->addScene("TownScene", c_townScene);
	SCENEMANAGER->addScene("ToDungeonScene", c_toDungeonScene);
	SCENEMANAGER->addScene("FirstDungeonScene", c_firstScene);
	SCENEMANAGER->addScene("InvenScene", c_invenScene);


	SCENEMANAGER->scenePush("StartSceneMenu",false);
	c_item->init();
	PLAYER.init();
	m_mapTool->init();
	m_scene->init();
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
	SOUNDMANAGER->release();
}

void mainGame::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	ANIMATIONMANAGER->update();
	SOUNDMANAGER->update();

	switch (m_startMenuScene->choiceMenu())
	{
	case GAME:
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			SCENEMANAGER->changeScene("ToDungeonScene");
		}

		break;

	case MAPTOOL:
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			SCENEMANAGER->scenePush("MapToolScene",true);
	
		}
		break;

	case END:

		break;

	default:
		break;

	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->scenePush("DungeonScene2", true);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->scenePush("DungeonScene3", true);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		
	}
}

void mainGame::render(/*HDC hdc*/)
{
	//흰색 비트맵
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY/2, WINSIZEX, WINSIZEY, BLACKNESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
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

void mainGame::aniArray()
{
	//===================//
	// plyaer 던전 ANI 1 //
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

	// 빅플레이어
	ANIMATIONMANAGER->addAnimation("1Player_upWalk", "dungeonPlayerBig", 0, 7, 10, false, true);
	ANIMATIONMANAGER->addAnimation("1Player_downWalk", "dungeonPlayerBig", 10, 17, 10, false, true);
	ANIMATIONMANAGER->addAnimation("1Player_rightWalk", "dungeonPlayerBig", 20, 27, 10, false, true);
	ANIMATIONMANAGER->addAnimation("1Player_leftWalk", "dungeonPlayerBig", 30, 37, 10, false, true);
	ANIMATIONMANAGER->addAnimation("1Player_rightRoll", "dungeonPlayerBig", 40, 47, 10, false, true);
	ANIMATIONMANAGER->addAnimation("1Player_leftRoll", "dungeonPlayerBig", 50, 57, 10, false, true);
	ANIMATIONMANAGER->addAnimation("1Player_upRoll", "dungeonPlayerBig", 60, 67, 10, false, true);
	ANIMATIONMANAGER->addAnimation("1Player_downRoll", "dungeonPlayerBig", 70, 77, 10, false, true);
	ANIMATIONMANAGER->addAnimation("1Player_rightIdle", "dungeonPlayerBig", 80, 89, 10, false, true);
	ANIMATIONMANAGER->addAnimation("1Player_leftIdle", "dungeonPlayerBig", 90, 99, 10, false, true);
	ANIMATIONMANAGER->addAnimation("1Player_upIdle", "dungeonPlayerBig", 100, 109, 10, false, true);
	ANIMATIONMANAGER->addAnimation("1Player_downIdle", "dungeonPlayerBig", 110, 119, 10, false, true);
	ANIMATIONMANAGER->addAnimation("1Player_die", "dungeonPlayerBig", 120, 129, 10, false, true);

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

	ANIMATIONMANAGER->addDefAnimation("player_DungeonDoorInto", "playerIntoDungeon", 10, false, false);

	// 던전문 닿고 열기(밖에)
	ANIMATIONMANAGER->addDefAnimation("openOut_Door", "openOutDoor", 10, false, true); //오픈
	ANIMATIONMANAGER->addAnimation("keepOpenDoor", "openOutDoor", 5, 9, 5, false, true);  // 킵오픈
	ANIMATIONMANAGER->addDefAnimation("closeOut_Door", "openOutDoor", 10,true, true);	// 클로즈
	
	/* top */
	ANIMATIONMANAGER->addDefAnimation("close_forest_Door", "forestDoorClose", 10, false, false);
	ANIMATIONMANAGER->addDefAnimation("open_forest_Door", "forestDoorOpen", 10, false, false);
	ANIMATIONMANAGER->addDefAnimation("forestDoor_Head_Top", "forestDoorHead_up", 10, false, false);
	ANIMATIONMANAGER->addDefAnimation("forestDoor_Head_Bottom", "forestDoorHead_Bottom", 10, false, false);
	ANIMATIONMANAGER->addDefAnimation("close_forest_Door_Bottom", "forestDoor_Bottom", 10, false, false);

	// 슬라임 && 벼룩 애니메이션 
	ANIMATIONMANAGER->addDefAnimation("miniSlime_Ani", "miniSlime", 10, false, true);
	ANIMATIONMANAGER->addDefAnimation("flea_Ani", "flea", 10, false, true);

	// 바주카 플라워 애니메이션 (오브젝트 포함)
	/* bottom */
	ANIMATIONMANAGER->addAnimation("bazooka_Bottom_Move", "bazookaFlower_bottom", 0, 7, 5, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_Bottom_AttackReady", "bazookaFlower_bottom", 11, 18,8, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_Bottom_Attack", "bazookaFlower_bottom", 22, 29,8, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_Bottom_Reload", "bazookaFlower_bottom", 33, 36, 6, false, true);

	/* top */
	ANIMATIONMANAGER->addAnimation("bazooka_Top_Move", "bazookaFlower_up", 0, 10, 8, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_Top_Attack", "bazookaFlower_up", 11, 18,8, false, true);
	
	/* right */
	ANIMATIONMANAGER->addAnimation("bazooka_right_Move", "bazookaFlower_right", 0, 8, 5, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_right_Attack", "bazookaFlower_right", 12, 18, 9, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_right_Reload", "bazookaFlower_right", 24, 35, 8, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_right_AttackReady", "bazookaFlower_right", 36, 47, 8, false, true);

	/* left */
	ANIMATIONMANAGER->addAnimation("bazooka_left_Move", "bazookaFlower_left", 0, 8, 5, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_left_Attack", "bazookaFlower_left", 12, 19, 8, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_left_AttackReady", "bazookaFlower_left", 24, 35,8, false, true);
	ANIMATIONMANAGER->addAnimation("bazooka_left_Reload", "bazookaFlower_left", 36, 47, 8, false, true);

	/* 바주카 오브젝트 */
	ANIMATIONMANAGER->addAnimation("bazooka_object_boom", "bazookaObjectFrame", 0,2,10, false, true);

	// 버섯 몬스터 애니메이션
	ANIMATIONMANAGER->addAnimation("mushRoom_wait", "mushRoom", 0, 7, 7, false, true);
	ANIMATIONMANAGER->addAnimation("mushRoom_Move1", "mushRoom", 17, 33, 10, false, true);
	ANIMATIONMANAGER->addAnimation("mushRoom_Move2", "mushRoom", 34, 45, 10, false, true);

	// 모모 몬스터 애니메이션

	/* bottom */
	ANIMATIONMANAGER->addAnimation("momo_Bottom_Move", "momoEnemy_Bottom", 0, 7, 10,false, true);
	ANIMATIONMANAGER->addAnimation("momo_Bottom_AttackReady", "momoEnemy_Bottom", 12, 22, 10, false, true);
	ANIMATIONMANAGER->addAnimation("momo_Bottom_Attack", "momoEnemy_Bottom", 24, 27,10, false, true);
	ANIMATIONMANAGER->addAnimation("momo_Bottom_AttackEnd", "momoEnemy_Bottom", 36, 43,10, false, true);

	/* Top */
	ANIMATIONMANAGER->addAnimation("momo_Top_Move", "momoEnemy_Top", 0, 5,10, false, true);
	ANIMATIONMANAGER->addAnimation("momo_Top_AttackReady", "momoEnemy_Top", 12, 23, 10, false, true);
	ANIMATIONMANAGER->addAnimation("momo_Top_Attack", "momoEnemy_Top", 24, 31,10, false, true);
	ANIMATIONMANAGER->addAnimation("momo_Top_AttackEnd", "momoEnemy_Top", 36, 39,10, false, true);

	/* left */
	ANIMATIONMANAGER->addAnimation("momo_Left_Move", "momoEnemy_Left", 0, 6, 10, false, true);
	ANIMATIONMANAGER->addAnimation("momo_Left_AttackReady", "momoEnemy_Left", 12,23, 10, false, true);
	ANIMATIONMANAGER->addAnimation("momo_Left_Attack", "momoEnemy_Left", 24, 32,10, false, true);
	ANIMATIONMANAGER->addAnimation("momo_Left_AttackEnd", "momoEnemy_Left", 36, 44,10, false, true);

	/* Right */
	ANIMATIONMANAGER->addAnimation("momo_Right_Move", "momoEnemy_Right", 0, 5,10, false, true);
	ANIMATIONMANAGER->addAnimation("momo_Right_AttackReady", "momoEnemy_Right", 12, 22,10, false, true);
	ANIMATIONMANAGER->addAnimation("momo_Right_Attack", "momoEnemy_Right", 24, 31,10, false, true);
	ANIMATIONMANAGER->addAnimation("momo_Right_AttackEnd", "momoEnemy_Right", 36, 42,10, false, true);

	/* objectBoom */
	ANIMATIONMANAGER->addDefAnimation("momoObjecAni", "momoObjectBoom", 5, false, true);

	// 날파리
	ANIMATIONMANAGER->addAnimation("fly_Wait", "flyEnemy", 0, 2,5, false, true);
	ANIMATIONMANAGER->addAnimation("fly_Move", "flyEnemy", 14, 27,10, false, true);
	ANIMATIONMANAGER->addAnimation("fly_MoveReady", "flyEnemy", 28, 30,5, false, true);
	ANIMATIONMANAGER->addAnimation("fly_Attack", "flyEnemy", 42, 53,10, false, true);

	// 던전 애니메이션
	ANIMATIONMANAGER->addDefAnimation("sub", "subject", 10, false, false);

}









