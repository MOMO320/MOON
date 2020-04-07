#include "stdafx.h"
#include "scene.h"

scene::scene() 
{
}

scene::~scene()
{
}

HRESULT scene::init()
{
	//Zobject = IMAGEMANAGER->addImage("Ä«¸Þ¶ó2", WINSIZEX, WINSIZEY);
	return S_OK;
}

void scene::release()
{
}

void scene::update()
{
	time = TIMEMANAGER->getElapsedTime();
	pastTime += time;
}

//void cameraManager::render(image * img)
//{
//	GdiTransparentBlt(img->getMemDC(), _cameraXY.x, _cameraXY.y, WINSIZEX, WINSIZEY, _camera->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, RGB(0, 0, 0));
//}


void scene::imageInit()
{
	blackScene = IMAGEMANAGER->findImage("blackScene");
}

void scene::closeBlackSceneRender(bool _isAlpha, BYTE _alpha, const char * _sceneName)
{
	//if (_isAlpha)
	//{
	//    if (addDeley < pastTime && _alpha < 230)
	//    {
	//		_alpha += 25;
	//    
	//    	pastTime = 0.0f;
	//    }

	//	blackScene->alphaRender(CAMERAMANAGER->getCameraDC(), 0, 0, _alpha);
	//	blackScene->alphaRender(getMemDC(), CAMERAMANAGER->getCameraXY().x, CAMERAMANAGER->getCameraXY().y, _alpha);
	//}

	//if (_alpha >= 240)
	//{
	//	_isAlpha = false;
	//	SCENEMANAGER->changeScene(_sceneName);
	//}
}

void scene::openBlackSceneRender(bool _isAlpha, BYTE _alpha)
{
	//if (!_isAlpha)
	//{
	//	if (addDeley < pastTime && _alpha > 25)
	//	{
	//		_alpha -= 25;

	//		pastTime = 0.0f;
	//	}

	//	blackScene->alphaRender(CAMERAMANAGER->getCameraDC(), 0, 0, _alpha);
	//	blackScene->alphaRender(getMemDC(), CAMERAMANAGER->getCameraXY().x, CAMERAMANAGER->getCameraXY().y, _alpha);
	//}
	//if (_alpha <= 25)
	//{
	//	_isAlpha = true;
	//}
}
