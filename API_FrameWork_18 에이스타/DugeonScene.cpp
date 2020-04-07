#include "stdafx.h"
#include "DugeonScene.h"

DugeonScene::DugeonScene()
	:m_Map1(new dungeonMap1) , m_miniSlime1(new miniSlime) , m_miniSlime2(new miniSlime), m_miniSlime3(new miniSlime) , m_flea1(new flea) , m_mushRoom1(new mushRoom) , m_mushRoom2(new mushRoom)
{
}

DugeonScene::~DugeonScene()
{
	delete m_Map1;
	delete m_miniSlime1;
	delete m_miniSlime2;
	delete m_miniSlime3;
	delete m_flea1;
	delete m_mushRoom1;
	delete m_mushRoom2;
}

HRESULT DugeonScene::init()
{
	m_Map1->init();

	// aStar 몬스터
	m_miniSlime1->init(WINSIZEX / 2, WINSIZEY / 2, m_Map1 ,m_miniSlime1);
	m_miniSlime2->init(WINSIZEX / 2+200, WINSIZEY / 2 +200 , m_Map1 , m_miniSlime2);
	m_miniSlime3->init(WINSIZEX / 2+100, WINSIZEY / 2 +100 , m_Map1 , m_miniSlime3);
	m_flea1->init(WINSIZEX - 300, WINSIZEY - 400 , m_Map1, m_flea1);

	m_mushRoom1->init(WINSIZEX - 450, 300);
	m_mushRoom2->init(400, 300);

	//===============//
	//	 player불럼  //
	//===============//
	PLAYER.setTankMapMemoryAdress(m_Map1);
	PLAYER.setCharacPosition(m_Map1->getMap()[288].m_rc);
	PLAYER.m_player.m_money -= 300;
	PLAYER.m_player.m_ani = ANIMATIONMANAGER->findAnimation("Player_upIdle");
	PLAYER.m_player.m_ani->start();
	
	_fleas.push_back(m_flea1);
	_miniSlimes.push_back(m_miniSlime1);
	_miniSlimes.push_back(m_miniSlime2);
	_miniSlimes.push_back(m_miniSlime3);
	_mushRooms.push_back(m_mushRoom1);
	_mushRooms.push_back(m_mushRoom2);


	return S_OK;
}

void DugeonScene::release()
{
	IMAGEMANAGER->deleteAll();
	m_miniSlime1->release();
	m_miniSlime2->release();
	m_miniSlime3->release();
	m_flea1->release();

	PLAYER.release();
	m_Map1->release();
	m_mushRoom1->release();
	m_mushRoom2->release();
}

void DugeonScene::update()
{
	RECT playerMoveRect = RectMakeCenter(WINSIZEX / 2 + 5, 360, WINSIZEX - 300, WINSIZEY / 2 + 180);
	time = TIMEMANAGER->getElapsedTime();
	pastTime += time;
	/*diePastTime += time;*/

	PLAYER.update(m_Map1 ,false, playerMoveRect);
	m_Map1->update();

	for (int i = 1; i <= _miniSlimes.size(); i++)
	{
		_miniSlimes[i-1]->update();
		_miniSlimes[i - 1]->update(m_Map1, PLAYER.m_player._rc, _miniSlimes[i - 1], 4, false, PLAYER.m_player.fightRc, PLAYER.m_player.m_attack);
	}
	for (int i = 1; i <= _fleas.size(); i++)
	{
		_fleas[i-1]->update();
		_fleas[i-1]->update(m_Map1, PLAYER.m_player._rc, _fleas[i-1],2, false , PLAYER.m_player.fightRc , PLAYER.m_player.m_attack);
	}
	for (int i = 1; i <= _mushRooms.size(); i++)
	{
		_mushRooms[i-1]->update(PLAYER.getPlayerRect(), m_Map1, PLAYER.m_player.fightRc, PLAYER.m_player.m_attack);
	}

	collision();
	deathDelete();
}

void DugeonScene::render()
{
	m_Map1->render();

	for (int i = 0; i < _miniSlimes.size(); i++)
	{
		_miniSlimes[i]->render(_miniSlimes[i]);
	}
	for (int i = 0; i < _fleas.size(); i++)
	{
		_fleas[i]->render(_fleas[i]);
	}

	for (int i = 1; i <= _mushRooms.size(); i++)
	{
		_mushRooms[i-1]->render();
		_mushRooms[i-1]->render(m_Map1);
	}
	PLAYER.render(getMemDC());
	//printText(getMemDC(), std::to_string(PLAYER.m_player.m_money).c_str(), "고딕", WINSIZEX / 2, 200, 50, false, RGB(255,255,255),false);

	if (isDamage)
	{
		string dama = "-";
		dama += to_string(damage);
		printText(getMemDC(), dama.c_str(), "나눔스퀘어_ac Bold", PLAYER.m_player._rc.left + 10, PLAYER.m_player._rc.top - 5, 25, RGB(255, 0, 0), true, RGB(255, 0, 255));
	}


	
}

void DugeonScene::collision()
{
	// 플레이어와 적들의 충돌처리
	RECT rc;
	RECT mushRoomRect[2];
	for (int i = 0; i < _mushRooms.size(); i++)
	{
		mushRoomRect[i] = RectMake(_mushRooms[i]->m_mushRoom.x, _mushRooms[i]->m_mushRoom.y, _mushRooms[i]->m_mushRoom.m_img->getFrameWidth(), _mushRooms[i]->m_mushRoom.m_img->getFrameHeight());
	}
	//==========================================

	for (int i = 0; i < _miniSlimes.size(); i++)
	{
		if (IntersectRect(&rc, &PLAYER.m_player._rc, &_miniSlimes[i]->m_miniSlime._rc) && !isDamage)
		{
			damage = _miniSlimes[i]->m_miniSlime.attack;
			PLAYER.m_player.m_hp -= _miniSlimes[i]->m_miniSlime.attack;
			isDamage = true;
			break;
		}
	}

	for (int i = 0; i < _mushRooms.size(); i++)
	{
		if (IntersectRect(&rc, &PLAYER.m_player._rc, &mushRoomRect[i]) && !isDamage)
		{
			damage = _mushRooms[i]->m_mushRoom.attack;
			PLAYER.m_player.m_hp -= _mushRooms[i]->m_mushRoom.attack;
			isDamage = true;
			break;
		}
	}

	for (int i = 0; i < _fleas.size(); i++)
	{
		if (IntersectRect(&rc, &PLAYER.m_player._rc, &_fleas[i]->m_flea._rc) && !isDamage)
		{
			damage = _fleas[i]->m_flea.attack;
			PLAYER.m_player.m_hp -= _fleas[i]->m_flea.attack;
			isDamage = true;
			break;
		}
	}

	if (addDeley > pastTime && isDamage)
	{
		string dama = "-";
		dama = to_string(damage);
		printText(getMemDC(), dama.c_str(), "나눔스퀘어_ac Bold", PLAYER.m_player._rc.left +  10, PLAYER.m_player._rc.top - 30, 50, RGB(255, 0,0), true, RGB(255, 0, 255));
	}
	else
	{
		pastTime = 0.0f;
		isDamage = false;
	}

}

void DugeonScene::deathDelete()
{
	for (auto& iter = _fleas.begin(); iter != _fleas.end();)
	{
		if ((*iter)->getEnemyInfo().hp <= 0)
		{
		  _fleas.erase(iter);
		  break;
		}
		else 
		{
			iter++;
		}
	}

	for (auto& iter = _miniSlimes.begin(); iter != _miniSlimes.end();)
	{
		if ((*iter)->getEnemyInfo().hp <= 0)
		{
			_miniSlimes.erase(iter);
			break;
		}
		else 
		{
			iter++;
		}
	}

	for (auto& iter = _mushRooms.begin(); iter != _mushRooms.end();)
	{
		if ((*iter)->m_mushRoom.hp <= 0)
		{
			_mushRooms.erase(iter);
			break;
			//diePastTime = 0.0f;
		}
		else 
		{
			iter++;
		}
	}
}

