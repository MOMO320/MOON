#include "stdafx.h"
#include "townMap.h"

townMap::townMap()
{
}

townMap::~townMap()
{
}

HRESULT townMap::init()
{
	townImg = IMAGEMANAGER->findImage("town");
	m_changeSceneRect[0] = RectMake(950, 0, 100, 100);
	m_changeSceneRect[1] = RectMake(1650,500, 100, 100);

	return S_OK;
}

void townMap::release()
{
	IMAGEMANAGER->release();
}

void townMap::update()
{

}

void townMap::render()
{
	string x = "x : ";
	string y = "y : ";
	x += to_string(PLAYER.m_player._rc.left);
	y += to_string(PLAYER.m_player._rc.top);
	townImg->render(getMemDC(), 0,0);

	printText(CAMERAMANAGER->getCameraDC(), x.c_str(), "³ª´®½ºÄù¾î_ac", PLAYER.m_player._rc.left - 50, PLAYER.m_player._rc.top - 30, 20, RGB(255, 255, 255), true, RGB(255, 0, 255));
	printText(CAMERAMANAGER->getCameraDC(), y.c_str(), "³ª´®½ºÄù¾î_ac", PLAYER.m_player._rc.left - 50, PLAYER.m_player._rc.top - 10, 20, RGB(255, 255, 255), true, RGB(255, 0, 255));
	
	
	colorRectangle(getMemDC(), m_changeSceneRect[0].left, m_changeSceneRect[0].top, 100, 100,255,0,0);
	colorRectangle(getMemDC(), m_changeSceneRect[1].left, m_changeSceneRect[1].top, 100, 100,0,255,0);
	
}
