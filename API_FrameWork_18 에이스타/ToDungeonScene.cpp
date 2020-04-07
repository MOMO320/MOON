#include "stdafx.h"
#include "ToDungeonScene.h"

ToDungeonScene::ToDungeonScene() : m_toDungeonMap(new toDungeonMap), m_ui(new Ui)
{
}

ToDungeonScene::~ToDungeonScene()
{
	delete m_toDungeonMap;
	delete m_ui;
}

HRESULT ToDungeonScene::init()
{
	SOUNDMANAGER->stop("introSound");

	POINT playerPt;
	
	playerPt.x = 1780 ;
	playerPt.y = 2700;

	playerCollision = RectMakeCenter(1835, 2690, 40, 40); // 초반 캐릭터위치 잡기

	//문의 상태
	forestDoor.img = IMAGEMANAGER->findImage("openOutDoor");
	forestDoor.ani = ANIMATIONMANAGER->findAnimation("keepOpenDoor");
	forestDoor.inToRect = RectMake(2500, 1390, 100, 300);
	forestDoor.imgRect = RectMake(2448, 1251, forestDoor.img->getFrameWidth(), forestDoor.img->getFrameHeight());
	forestDoor.status = DOOR_NULL;
	//문의 상태

	m_toDungeonMap->init();
	blackScene = IMAGEMANAGER->findImage("blackScene");
	upObject = IMAGEMANAGER->findImage("town2Up");
	PLAYER.setCharacPosition(playerCollision);
	CAMERAMANAGER->setCameraCenter(playerPt);

	m_ui->init();

	//SOUNDMANAGER->stop("introSound");
	//SOUNDMANAGER->play("windTown", 1.0f);

	return S_OK;
}

void ToDungeonScene::release()
{
	PLAYER.release();
	m_toDungeonMap->release();
	CAMERAMANAGER->relaese();
	CAMERAMANAGER->releaseSingleton();
}

void ToDungeonScene::update()
{
	RECT temp; 
	float time = TIMEMANAGER->getElapsedTime();
	pastTime += time;

	playerMoveRect = RectMakeCenter(0,0 ,m_toDungeonMap->toDungeon->getWidth()*3, m_toDungeonMap->toDungeon->getHeight() * 3);

	PLAYER.update(m_toDungeonMap, true , playerMoveRect);
	m_toDungeonMap->update();

	//m_ui->update();

	// 던전 입구 애니메이션
	doorAni();
	aniStart();

	// 던전으로가는 입구

	if (isInSide)
	{
		if (!IntersectRect(&temp, &PLAYER.m_player._rc, &forestDoor.inToRect))
		{
			isInSide = false;
			forestDoor.status = DOOR_CLOSE;
		}
	}

	if (IntersectRect(&temp, &PLAYER.m_player._rc, &forestDoor.inToRect))
	{
		if (!KEYMANAGER->isOnceKeyDown(VK_RETURN) && forestDoor.status != DOOR_KEEP && forestDoor.status != DOOR_INTO)
		{
			forestDoor.status = DOOR_OPEN;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RETURN))
		{
			forestDoor.status = DOOR_INTO;
		}
		isInSide = true;
	}

	if (forestDoor.status == DOOR_OPEN && forestDoor.ani->getPlayIndex() == forestDoor.ani->getPlaySize().size()-1)
	{
		forestDoor.status = DOOR_KEEP;
	}
	if (forestDoor.status == DOOR_CLOSE && forestDoor.ani->getPlayIndex() == forestDoor.ani->getPlaySize().size()-1)
	{
		forestDoor.status = DOOR_NULL;
	}

	if (forestDoor.status == DOOR_INTO && forestDoor.ani->getPlayIndex() == forestDoor.ani->getPlaySize().size()-1 && !isOnce)
	{
		isBlack = true;
		forestDoor.ani->setPlayIndex(18);
		forestDoor.ani->pause();
		isOnce = true;
	}

	if (alpha >= 240)
	{
		isBlack = false;
		alpha = 0;
		SCENEMANAGER->scenePush("FirstDungeonScene", true);
	}
}

void ToDungeonScene::render()
{
	m_toDungeonMap->render();
	//colorRectangle(getMemDC(), playerMoveRect.left, playerMoveRect.top, m_toDungeonMap->toDungeon->getWidth() * 3, m_toDungeonMap->toDungeon->getHeight() * 3, 255, 0, 255);
	
	//AlphaRectangle(getMemDC(), forestDoor.inToRect.left, forestDoor.inToRect.top, forestDoor.inToRect.right, forestDoor.inToRect.bottom);
	
	if(forestDoor.status != DOOR_NULL)
	forestDoor.img->aniRender(getMemDC(), forestDoor.imgRect.left, forestDoor.imgRect.top, forestDoor.ani);
	
	if (forestDoor.status != DOOR_INTO)
	{
		PLAYER.render(getMemDC());
	}
	//printText(getMemDC(), to_string(PLAYER.m_player._rc.left).c_str(), "나눔스퀘어_ac Bold", PLAYER.m_player._rc.left -40, PLAYER.m_player._rc.top - 60, 20, RGB(255, 255, 255), true, RGB(255, 0, 255));
	//printText(getMemDC(), to_string(PLAYER.m_player._rc.top).c_str(), "나눔스퀘어_ac Bold", PLAYER.m_player._rc.left - 40, PLAYER.m_player._rc.top -30, 20, RGB(255, 255, 255), true, RGB(255, 0, 255));
	
	upObject->render(getMemDC(), 820, -35);
	
	if (isBlack)
	{
		if (addDeley < pastTime)
		{
			alpha += 25;
			pastTime = 0.0f;
		}
		blackScene->alphaRender(getMemDC(), CAMERAMANAGER->getCameraXY().x, CAMERAMANAGER->getCameraXY().y, alpha);
	}
}

void ToDungeonScene::doorAni()
{
	tempAni = forestDoor.ani;

	switch (forestDoor.status)
	{
	case DOOR_NULL:
		break;
	case DOOR_OPEN:
		forestDoor.ani = ANIMATIONMANAGER->findAnimation("openOut_Door");
		break;
	case DOOR_CLOSE:
		forestDoor.ani = ANIMATIONMANAGER->findAnimation("closeOut_Door");
		break;
	case DOOR_INTO:
		forestDoor.img = IMAGEMANAGER->findImage("playerIntoDungeon");
		forestDoor.ani = ANIMATIONMANAGER->findAnimation("player_DungeonDoorInto");
		break;
	case DOOR_KEEP:
		forestDoor.ani = ANIMATIONMANAGER->findAnimation("keepOpenDoor"); 
		break;
	}
}

void ToDungeonScene::aniStart()
{
	if (tempAni != forestDoor.ani)
	{
		forestDoor.ani->start();
	}
}
