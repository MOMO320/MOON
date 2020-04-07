#include "stdafx.h"
#include "DungeonScene5.h"

DungeonScene5::DungeonScene5():m_flea(new flea)
{
}

DungeonScene5::~DungeonScene5()
{
	delete m_flea;
}

HRESULT DungeonScene5::init()
{
	m_Map4->init();

	m_flea->init(WINSIZEX - 300, WINSIZEY - 400, m_Map4, m_flea);
	PLAYER.setTankMapMemoryAdress(m_Map4);
	PLAYER.setCharacPosition(m_Map4->getMap()[288].m_rc);
	
	PLAYER.m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_upIdle");
	PLAYER.m_player.m_ani->start();
	
	v_flea.push_back(m_flea);

	return S_OK;
}

void DungeonScene5::release()
{
	IMAGEMANAGER->deleteAll();
	m_Map4->release();
	m_flea->release();
}

void DungeonScene5::update()
{
	RECT playerMoveRect = RectMakeCenter(WINSIZEX / 2 + 5, 360, WINSIZEX - 300, WINSIZEY / 2 + 180);

	PLAYER.update(m_Map4, false, playerMoveRect);
	m_Map4->update();

	for (int i = 1; i <= v_flea.size(); i++)
	{
		v_flea[i - 1]->update();
		v_flea[i - 1]->update(m_Map4, PLAYER.m_player._rc, v_flea[i - 1], 2, false, PLAYER.m_player.fightRc, PLAYER.m_player.m_attack);
	}


}

void DungeonScene5::render()
{
	m_Map4->render();

	for (int i = 0; i < v_flea.size(); i++)
	{
		v_flea[i]->render(v_flea[i]);
	}
	PLAYER.render(getMemDC());
}
