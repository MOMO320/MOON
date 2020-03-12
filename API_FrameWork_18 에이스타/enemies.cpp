#include "stdafx.h"
#include "enemies.h"

enemies::enemies()
{
}

enemies::~enemies()
{
}

HRESULT enemies::init()
{
	m_enemy1.name = "박스";
	m_enemy1._rc = RectMakeCenter(WINSIZEX - 180, WINSIZEY / 2, 80, 80);
	SetRect(&m_enemy1._fightColli,
		300, 100, (WINSIZEX / 2) + 450, (WINSIZEY / 2) + 260);
	m_enemy1.speed = 100;
	//  player 와 enemy 충돌처리 할 공간
	return S_OK;
}

void enemies::release()
{
}

void enemies::update()
{
}

void enemies::render()
{
	AlphaRectangle(getMemDC(), m_enemy1._fightColli.left, m_enemy1._fightColli.top, m_enemy1._fightColli.right , m_enemy1._fightColli.bottom);
	colorRectangle(getMemDC(), m_enemy1._rc.left, m_enemy1._rc.top, 80, 80, 255, 69, 000);
}

//void enemies::enemyInit(enemy _enemy , int _left, int _top, int _right, int _bottom, string _name, int _attack, int _hp)
//{
//	SetRect(&_enemy._rc,
//		_left,
//		_top,
//		_right,
//		_bottom);
//
//	_enemy.name		= _name;
//	_enemy.attack	= _attack;
//	_enemy.hp		= _hp;
//}
