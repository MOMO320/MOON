#include "stdafx.h"
#include "DoorManager.h"

DoorManager::DoorManager()
{
}

DoorManager::~DoorManager()
{
}

HRESULT DoorManager::init()
{
	return S_OK;
}

void DoorManager::release()
{
}

void DoorManager::update()
{
	doorAni();
	aniStart();
}

void DoorManager::render()
{
}

void DoorManager::doorInit(const char * _img, const char * _ani, RECT _intoREct, RECT _imgRECT, DOORSTATUS _status)
{
	door.img = IMAGEMANAGER->findImage(_img);
	door.ani = ANIMATIONMANAGER->findAnimation(_ani);
	door.inToRect = _intoREct;
	door.imgRect = _imgRECT;
	door.status = DOOR_NULL;
}

void DoorManager::doorAni()
{
	tempAni = door.ani;

	switch (door.status)
	{
	case DOOR_NULL:
		break;
	case DOOR_OPEN:
		door.ani = ANIMATIONMANAGER->findAnimation("openOut_Door");
		break;
	case DOOR_CLOSE:
		door.ani = ANIMATIONMANAGER->findAnimation("closeOut_Door");
		break;
	case DOOR_INTO:
		door.img = IMAGEMANAGER->findImage("playerIntoDungeon");
		door.ani = ANIMATIONMANAGER->findAnimation("player_DungeonDoorInto");
		break;
	case DOOR_KEEP:
		door.ani = ANIMATIONMANAGER->findAnimation("keepOpenDoor");
		break;
	}
}

void DoorManager::aniStart()
{
	if (tempAni != door.ani)
	{
		door.ani->start();
	}
}
