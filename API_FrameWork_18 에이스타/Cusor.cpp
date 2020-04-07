#include "stdafx.h"
#include "Cusor.h"
#include "gameTypes.h"

Cusor::Cusor()
{
}

Cusor::~Cusor()
{
}

HRESULT Cusor::init()
{
	cusor.cusorImg = IMAGEMANAGER->findImage("cusor");
	cusor.choiceImg = IMAGEMANAGER->findImage("ChooseCusor");
	return S_OK;
}

void Cusor::release()
{
	IMAGEMANAGER->deleteAll();
}

void Cusor::update(vector<itemInfo> _vItem , vector<RECT> _vRect)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (cusorX == 0)
			cusorX = 4;
		else cusorX -= 1;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (cusorX == 4) cusorX = 0;
		else cusorX += 1;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (cusorY == 0) cusorY = 0;
		else cusorY -= 1;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (cusorY == 5) cusorY = 5;
		else cusorY += 1;
	}

	// 엔터키 누르면 선택
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && enterCount == 0)
	{
		isChoose = true;
		chooseX = cusorX;
		chooseY = cusorY;
		enterCount += 1;
		chooseItem(_vItem);
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_SHIFT) && enterCount == 1)
	{
		changeRect();
		isChoose = false;
		putX = cusorX;
		putY = cusorY;
		enterCount = 0;
	}

}

void Cusor::render(vector<RECT> _vRect)
{
	cusor.cusorImg->render(CAMERAMANAGER->getCameraDC(), _vRect.at((cusorY * 5) + cusorX).left, _vRect.at((cusorY * 5) + cusorX).top);
	if (isChoose)
	{
		cusor.choiceImg->render(CAMERAMANAGER->getCameraDC(), _vRect.at((cusorY * 5) + cusorX).left, _vRect.at((cusorY * 5) + cusorX).top - cusor.choiceImg->getHeight());
		cusor.v_cusorItem.at(0).img->render(CAMERAMANAGER->getCameraDC(), _vRect.at((cusorY * 5) + cusorX).left, _vRect.at((cusorY * 4) + cusorX).top - cusor.choiceImg->getHeight());
	}
}

void Cusor::chooseItem(vector<itemInfo> _vItem)
{
	if (isChoose)
	{
		cusor.v_cusorItem.push_back(_vItem.at((chooseY * 5) + chooseX));
	}
}

void Cusor::intoItem(vector<itemInfo> _vItem, vector<RECT> _vRect)
{

}

int Cusor::changeRect()
{
	int put = ((putY * 5) + putX);
	//cusor.v_cusorItem.clear();
	return put;
}

int Cusor::chooseRect()
{
	int choose = (chooseY * 5) + chooseX;
	return choose;
}

