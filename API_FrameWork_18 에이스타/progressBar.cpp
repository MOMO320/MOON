#include "stdafx.h"
#include "progressBar.h"
progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(char * frontImage, char * backImage, float x, float y, int width, int height)
{
	//_x = x;
	//_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarFront = new image;
	_progressBarFront->init(frontImage, x, y, width, height, true, RGB(255, 0, 255));

	_progressBarBack = new image;
	_progressBarBack->init(backImage, x, y, width, height, true, RGB(255, 0, 255));


	_width = _progressBarFront->getWidth();

	return S_OK;
}

HRESULT progressBar::init(char * frontImage, char * backImage, float x, float y, int width, int height, float x2, float y2, int width2, int height2)
{
	//_x = x;
	//_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarFront = new image;
	_progressBarFront->init(frontImage, x2, y2, width2, height2, true, RGB(255, 0, 255));

	_progressBarBack = new image;
	_progressBarBack->init(backImage, x, y, width, height,true, RGB(255, 0, 255));

	_width = width2;

	return S_OK;
}

void progressBar::release()
{
	SAFE_DELETE(_progressBarFront);
	SAFE_DELETE(_progressBarBack);
}

void progressBar::update(int _x, int _y)
{
	_rcProgress = RectMake(_x, _y, _progressBarBack->getFrameWidth(), _progressBarBack->getHeight());
}

void progressBar::render(int _x , int _y)
{
	_progressBarBack->render(getMemDC(), _x + 5, _y -5, 0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight());

	_progressBarFront->render(getMemDC(), _x + 5, _y -5, 0, 0, _width, _progressBarBack->getHeight());

}

void progressBar::render(int _x, int _y, int _x2, int _y2)
{
	_progressBarBack->render(CAMERAMANAGER->getCameraDC(), _x + 5, _y - 5, 0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight());

	_progressBarFront->render(CAMERAMANAGER->getCameraDC(), _x + _x2,_y + _y2, 0, 0, _width, _progressBarBack->getHeight());
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge)* _progressBarFront->getWidth();
}
