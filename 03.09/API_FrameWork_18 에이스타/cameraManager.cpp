#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	_camera = IMAGEMANAGER->addImage("Ä«¸Þ¶ó", WINSIZEX, WINSIZEY);

	_center = PointMake(WINSIZEX / 2, WINSIZEY / 2);

	_cameraXY = PointMake(_center.x - WINSIZEX / 2, _center.y - WINSIZEY / 2);


	return S_OK;
}

void cameraManager::relaese()
{
}

void cameraManager::update()
{
	_cameraXY = PointMake(_center.x - WINSIZEX / 2, _center.y - WINSIZEY / 2);
}

void cameraManager::render(image * img)
{
	GdiTransparentBlt(img->getMemDC(), _cameraXY.x, _cameraXY.y, WINSIZEX , WINSIZEY , _camera->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, RGB(255, 255, 255));
}

void cameraManager::setCameraCenter(POINT point)
{
	_center.x = point.x;
	_center.y = point.y;

}
