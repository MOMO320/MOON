#include "stdafx.h"
#include "DugeonScene3.h"

DugeonScene3::DugeonScene3()
	: c_fly(new fly) , m_Map3(new dungeonMap3) , c_fly2(new fly), c_fly3(new fly),
	c_momo(new Momo) , c_aStar(new aStar)
{
}

DugeonScene3::~DugeonScene3()
{
	delete c_fly;
	delete c_fly2;
	delete c_fly3;
	delete c_momo;
	delete m_Map3;
	delete c_aStar;
}

HRESULT DugeonScene3::init()
{
	m_Map3->init();
	c_fly->init(WINSIZEX / 2, WINSIZEY / 2);
	c_fly2->init(WINSIZEX / 2 -200, WINSIZEY / 2-100);
	c_fly3->init(WINSIZEX / 2+150, WINSIZEY / 2+150);

	v_fly.push_back(c_fly);
	v_fly.push_back(c_fly2);
	v_fly.push_back(c_fly3);

	c_momo->init(WINSIZEX / 2, WINSIZEY / 2 +80);
	c_aStar->init(m_Map3->getMap(), c_momo, WINSIZEX / 2, WINSIZEY / 2 + 80);

	PLAYER.m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_rightIdle");
	PLAYER.m_player.m_ani->start();
	PLAYER.setTankMapMemoryAdress(m_Map3);
	PLAYER.setCharacPosition(m_Map3->getMap()[162].m_rc);

	return S_OK;
}

void DugeonScene3::release()
{
	PLAYER.release();
	m_Map3->release();
	
	for (int i = 0; i < v_fly.size(); i++)
	{
		v_fly[i]->release();
	}
	c_aStar->release();
}

void DugeonScene3::update()
{
	RECT playerMoveRect = RectMakeCenter(WINSIZEX / 2 + 5, 360, WINSIZEX - 300, WINSIZEY / 2 + 180);

	time = TIMEMANAGER->getElapsedTime();
	m_Map3->update();
	PLAYER.update(m_Map3 , false, playerMoveRect);
	c_aStar->update(m_Map3->m_map, PLAYER.getPlayerRect(),c_momo, 4, true);
	c_momo->update(PLAYER.m_player._rc, c_aStar->getDirection(), c_aStar->getcurrentPath() , c_aStar->getFirstPath(), m_Map3);

	for (int i = 0; i < v_fly.size(); i++)
	{
		v_fly[i]->update(PLAYER.m_player._rc);
	}
}

void DugeonScene3::render()
{
	m_Map3->render();
	c_aStar->render(c_momo);
	PLAYER.render(getMemDC());

	for (int i = 0; i < v_fly.size(); i++)
	{
		v_fly[i]->render();
	}
	c_momo->render();

}
