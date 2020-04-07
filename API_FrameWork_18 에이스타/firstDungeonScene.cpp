#include "stdafx.h"
#include "firstDungeonScene.h"

firstDungeonScene::firstDungeonScene(): m_firstMap(new frontMap)
{
}

firstDungeonScene::~firstDungeonScene()
{
	delete m_firstMap;
}

HRESULT firstDungeonScene::init()
{
	m_firstMap->init();

	POINT player;

	// 플레이어 셋팅
	PLAYER.m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_upIdle");
	PLAYER.m_player.m_ani->start();
	PLAYER.setTankMapMemoryAdress(m_firstMap);
	PLAYER.setCharacPosition(m_firstMap->getMap()[288].m_rc);
	
	//카메라 셋팅
	player.x = PLAYER.m_player._rc.left;
	player.y = PLAYER.m_player._rc.top;
	CAMERAMANAGER->setCameraCenter(player);

	// 던전문
	forestDoorDown.img = IMAGEMANAGER->findImage("forestDoor_Bottom");
	forestDoorDown.Zimg = IMAGEMANAGER->findImage("forestDoorHead_Bottom");
	forestDoorDown.ani = ANIMATIONMANAGER->findAnimation("close_forest_Door_Bottom");
	forestDoorDown.Zani = ANIMATIONMANAGER->findAnimation("forestDoor_Head_Bottom");
	forestDoorDown.imgRect = m_firstMap->getMap()[287].m_rc;
	forestDoorDown.inToRect = RectMake(forestDoorDown.imgRect.left, forestDoorDown.imgRect.top + 100, 100, 100);
	forestDoorDown.status = DOOR_CLOSE;

	forestDoorUp.img = IMAGEMANAGER->findImage("forestDoorOpen");
	forestDoorUp.Zimg = IMAGEMANAGER->findImage("forestDoorHead_up");
	forestDoorUp.ani = ANIMATIONMANAGER->findAnimation("open_forest_Door");
	forestDoorUp.Zani = ANIMATIONMANAGER->findAnimation("forestDoor_Head_Top");
	forestDoorUp.imgRect = m_firstMap->getMap()[7].m_rc;
	forestDoorUp.inToRect = RectMake(forestDoorUp.imgRect.left + 80, forestDoorUp.imgRect.bottom, 100,30);
	forestDoorUp.status = DOOR_OPEN;

	// 서브젝트
	subjectImg = IMAGEMANAGER->findImage("subject");
	subjectAni = ANIMATIONMANAGER->findAnimation("sub");
	subjectAni->start();



	return S_OK;
}

void firstDungeonScene::release()
{
	PLAYER.release();
	m_firstMap->release();
	ANIMATIONMANAGER->deleteALL();
}

void firstDungeonScene::update()
{
	float time = TIMEMANAGER->getElapsedTime();
	pastTime += time;
	RECT temp; // 문충돌용 렉트
	RECT playerMoveRect = RectMakeCenter(WINSIZEX / 2 + 5, 360, WINSIZEX - 300, WINSIZEY / 2 + 180);

	m_firstMap->update();
	PLAYER.update(m_firstMap, false, playerMoveRect);


	// 문 충돌
	if (IntersectRect(&temp, &PLAYER.m_player._rc, &forestDoorUp.inToRect))
	{
		SCENEMANAGER->scenePush("DungeonScene1",true);
	}

	// 문애니메이션 
	if (forestDoorDown.ani->getPlayIndex() == forestDoorDown.ani->getPlaySize().size() - 1)
	{
		forestDoorDown.ani->pause();
	}
	if (forestDoorUp.ani->getPlayIndex() == forestDoorUp.ani->getPlaySize().size() - 1)
	{
		forestDoorUp.ani->pause();
	}
}

void firstDungeonScene::render()
{
	m_firstMap->render();
	forestDoorDown.img->aniRender(getMemDC(), forestDoorDown.imgRect.left, forestDoorDown.imgRect.top +25, forestDoorDown.ani);
	forestDoorUp.img->aniRender(getMemDC(), forestDoorUp.imgRect.left, forestDoorUp.imgRect.top, forestDoorUp.ani);
	PLAYER.render(getMemDC());
	forestDoorDown.Zimg->aniRender(getMemDC(), forestDoorDown.imgRect.left, forestDoorDown.imgRect.top + 25, forestDoorDown.Zani);
	forestDoorUp.Zimg->aniRender(getMemDC(), forestDoorUp.imgRect.left, forestDoorUp.imgRect.top, forestDoorUp.Zani);
	subjectImg->aniRender(getMemDC(), WINSIZEX / 2, WINSIZEY, subjectAni);
	//rectRender();
}

void firstDungeonScene::doorAni(DungeonDoor _door)
{
	tempAni = _door.ani;

	switch (_door.status)
	{
	case DOOR_NULL:
		break;
	case DOOR_OPEN:
		_door.img = IMAGEMANAGER->findImage("forestDoorOpen");
		_door.Zimg = IMAGEMANAGER->findImage("forestDoorHead_up");
		_door.ani = ANIMATIONMANAGER->findAnimation("open_forest_Door");
		_door.Zani = ANIMATIONMANAGER->findAnimation("forestDoor_Head_Top");
		break;
	case DOOR_CLOSE:
		_door.img = IMAGEMANAGER->findImage("forestDoor_Bottom");
		_door.Zimg = IMAGEMANAGER->findImage("forestDoorHead_Bottom");
		_door.ani = ANIMATIONMANAGER->findAnimation("close_forest_Door_Bottom");
		_door.Zani = ANIMATIONMANAGER->findAnimation("forestDoor_Head_Bottom");
		break;
	}
}

void firstDungeonScene::aniStart(DungeonDoor _door)
{
	if (tempAni != _door.ani)
	{
		_door.ani->start();
	}
}

void firstDungeonScene::rectRender()
{
	AlphaRectangle(getMemDC(), forestDoorUp.inToRect.left, forestDoorUp.inToRect.top, forestDoorUp.inToRect.right, forestDoorUp.inToRect.bottom);
	AlphaRectangle(getMemDC(), forestDoorDown.inToRect.left, forestDoorDown.inToRect.top, forestDoorDown.inToRect.right, forestDoorDown.inToRect.bottom);

}
