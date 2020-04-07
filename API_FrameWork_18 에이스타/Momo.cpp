#include "stdafx.h"
#include "Momo.h"

Momo::Momo() : m_ball(new momoBall) , m_ball2(new momoBall) , m_ball3(new momoBall)
{
}

Momo::~Momo()
{
	delete m_ball;
	delete m_ball2;
	delete m_ball3;
}

HRESULT Momo::init(int x, int y)
{
	m_momo.m_img = IMAGEMANAGER->findImage("momoEnemy_Left");
	m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Left_Move");
	m_momo._rc = RectMakeCenter(x, y, m_momo.m_img->getFrameWidth() / 2, m_momo.m_img->getFrameHeight() / 2);
	m_momo.name = "모모";
	m_momo.attack = 2;
	m_momo.hp = 35;
	m_momo.speed = MOMOSPEED;

	m_momo.m_ani->start();

	pastTime = 0;

	// 이전 애니담는 temp

	m_direct = ENEMY_LEFT;
	m_momo.m_momoAni = MOMO_MOVE;

	enemySetRect(x, y);

	ballInit();

	return S_OK;
}

void Momo::release()
{
	IMAGEMANAGER->deleteAll();
	ANIMATIONMANAGER->deleteALL();
	m_ball->release();
}

void Momo::update()
{
}

void Momo::render()
{
	m_momo.m_img->aniRender(getMemDC(), m_momo._rc.left, m_momo._rc.top, m_momo.m_ani);

	if (isPathOk)
	{
		AlphaRectangle(getMemDC(), m_momo._fightColli.left, m_momo._fightColli.top, m_momo._fightColli.right, m_momo._fightColli.bottom);
		ballRender();
	}
}

void Momo::render(PLAYERDIRECTION _direct, RECT _rc)
{
}

void Momo::update(RECT _rc , Direction _astarDirect , int _currentPath, int _firstPath, dungeonMap * _dunMap)
{
	float time = TIMEMANAGER->getElapsedTime();

	animationCollect(_astarDirect);
	animationAction(_astarDirect, _currentPath, _firstPath); // down 이미지 null 뜸 확인해야함
	animationStart();
	enemySetRect(0, 0);

	// 공격 모션때 오브젝트 

	if (_currentPath == _firstPath && !isPathOk && m_momo.m_momoAni == MOMO_ATTACKREADY)
	{
		isPathOk = true;
		playerRect = _rc;
	}

	if (isPathOk)
	{
		ballUpdate(_dunMap);
	}

	if (m_ball->getVBall().size() == 11)
	{
		isPathOk = false;
	}

	if (m_ball->getVBall().empty() && m_ball2->getVBall().empty() && m_ball3->getVBall().empty() && isPathOk)
	{

		isPathOk = false;
	}
}

void Momo::enemySetRect(int _x, int _y)
{
	m_momo._fightColli = RectMake(120, 80, WINSIZEX - 240, WINSIZEY - 160);
	m_momo._realCollRect = RectMakeCenter(m_momo._rc.left, m_momo._rc.top, 400, 400);
	m_momo._objectRc = RectMakeCenter(m_momo._rc.left, m_momo._rc.top, m_momo.m_img->getFrameWidth(), 100);
}

//==================//
// 모모볼  관련 함수 //
//=================//
void Momo::ballInit()
{
	m_ball->init("momoObject", 12, 600);
	m_ball2->init("momoObject", 12, 600);
	m_ball3->init("momoObject", 12, 600);
}

void Momo::ballUpdate(dungeonMap * _dunMap)
{
	m_ball->update();
	m_ball2->update();
	m_ball3->update();


	if (!m_ball->getFullobject())
	{
		this->momoBulletFire();
	}
	this->ballCollision(_dunMap, m_ball);
	this->ballCollision(_dunMap, m_ball2);
	this->ballCollision(_dunMap, m_ball3);
}

void Momo::momoBulletFire()
{
	m_ball->fire(m_momo._rc.right,
		m_momo._rc.top + 50,
		getAngle(m_momo._rc.right,
			m_momo._rc.top +50 ,
			PLAYER.m_player._rc.right  ,
			PLAYER.m_player._rc.top), 5.0f);

	m_ball2->fire(m_momo._rc.right ,
		m_momo._rc.top +50 ,
		getAngle(m_momo._rc.right,
			m_momo._rc.top +50 ,
			PLAYER.m_player._rc.right ,
			PLAYER.m_player._rc.top), 7.0f);


	m_ball3->fire(m_momo._rc.right,
		m_momo._rc.top + 50,
		getAngle(m_momo._rc.right,
			m_momo._rc.top +50 ,
			PLAYER.m_player._rc.right ,
			PLAYER.m_player._rc.top), 8.0f);
}

void Momo::ballRender()
{
	m_ball->render();
	m_ball2->render();
	m_ball3->render();
}

void Momo::ballCollision(dungeonMap * _dunMap , momoBall * _momoBall)
{
	if (!_momoBall->getVBall().empty())
	{
		for (int i = 0; i < _momoBall->getVBall().size(); i++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_momoBall->getVBall()[i].rc, &PLAYER.getPlayerRect()))
			{
				_momoBall->removeBullet(i);
				break;
			}
		}
		
		for (int i = 0 ; i < _momoBall->getVBall().size() ; i++)
		{
			RECT rc1;
			for (int j = 0; j < 4; j++)
			{
				if (IntersectRect(&rc1, &_momoBall->getVBall()[i].rc, &(_dunMap->getCollisionWAll()[j].rc)))
				{
					_momoBall->removeBullet(i);
					break;	
				}
			}
		}
	    
		for (int i = 0; i < _momoBall->getVBall().size(); i++)
		{
			RECT rc2;
			for (int k = 0; k < BACKTILEX * BACKTILEY; k++)
			{
				if (_dunMap->getMap()[k].m_obj == OBJ_DONGO)
				{
					if (IntersectRect(&rc2, &_momoBall->getVBall()[i].rc, &(_dunMap->getMap()[k].m_rc)))
					{
						_momoBall->removeBullet(i);
						break;
					}
				}
			}
		}
		for (int i = 0; i < _momoBall->getVBall().size(); i++)
		{
			RECT rc3;
			for (int k = 0; k < BACKTILEX * BACKTILEY; k++)
			{
				if (_dunMap->getMap()[k].m_obj == OBJ_TREE)
	    		{
	    			if (IntersectRect(&rc3, &_momoBall->getVBall()[i].rc, &(_dunMap->getMap()[k].m_rc)))
	    			{
						_momoBall->removeBullet(i);
						break;
	    			}
	    		}
	    	}
	    }
	}
}

//=================//
//  모모 애니메이션 //
//=================//

void Momo::animationStart()
{
	if (tempAni != m_momo.m_ani)
	{
		m_momo.m_ani->start();
	}
}
void Momo::animationCollect(Direction _astarDirect)
{
	// astar 다이렉션에 따른 애니메이션 작업
	switch (_astarDirect)
	{
	case DIRECTION_LEFT:
		m_momo.m_img = IMAGEMANAGER->findImage("momoEnemy_Left");
		break;
	case DIRECTION_RIGHT:
		m_momo.m_img = IMAGEMANAGER->findImage("momoEnemy_Right");
		break;
	case DIRECTION_UP:
		m_momo.m_img = IMAGEMANAGER->findImage("momoEnemy_Top");
		break;
	case DIRECTION_DOWN:
		m_momo.m_img = IMAGEMANAGER->findImage("momoEnemy_Bottom");
		break;
	case DIRECTION_LEFTUP:
		m_momo.m_img = IMAGEMANAGER->findImage("momoEnemy_Left");
		break;
	case DIRECTION_RIGHTDOWN:
		m_momo.m_img = IMAGEMANAGER->findImage("momoEnemy_Right");
		break;
	case DIRECTION_LEFTDOWN:
		m_momo.m_img = IMAGEMANAGER->findImage("momoEnemy_Left");
		break;
	case DIRECTION_RIGHTUP:
		m_momo.m_img = IMAGEMANAGER->findImage("momoEnemy_Right");
		break;
	}
}

void Momo::animationAction(Direction _astarDirect, int _currentPath , int _firstPath )
{
	tempAni = m_momo.m_ani;

	if (_currentPath != _firstPath ) // 만약 마지막 pathTile이 아니라면
	{
	    switch (_astarDirect)
	    {
	    case DIRECTION_LEFT:
			m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Left_Move");
	    	break;
	    case DIRECTION_RIGHT:
			m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Right_Move");
	    	break;
	    case DIRECTION_UP:
			m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Top_Move");
	    	break;
	    case DIRECTION_DOWN:
			m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Bottom_Move");
	    	break;
	    case DIRECTION_LEFTUP:
			m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Left_Move");
	    	break;
	    case DIRECTION_RIGHTDOWN:
			m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Right_Move");
	    	break;
	    case DIRECTION_LEFTDOWN:
			m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Left_Move");
	    	break;
	    case DIRECTION_RIGHTUP:
			m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Right_Move");
	    	break;
	    }
		m_momo.m_momoAni = MOMO_MOVE;
	}//end if(!lastPathTile)


	if (_currentPath == _firstPath)
	{
		lastPathRect = m_momo._rc;
		switch (_astarDirect)
		{
		case DIRECTION_LEFT:
			if(m_momo.m_momoAni == MOMO_MOVE) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Left_AttackReady");
			if(m_momo.m_momoAni == MOMO_ATTACKREADY) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Left_Attack");
			if(m_momo.m_momoAni == MOMO_ATTACK)
				m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Left_AttackEnd");
			break;
		case DIRECTION_RIGHT:
			if(m_momo.m_momoAni == MOMO_MOVE)
				m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Right_AttackReady");
			if(m_momo.m_momoAni == MOMO_ATTACKREADY) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Right_Attack");
			if(m_momo.m_momoAni == MOMO_ATTACK) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Right_AttackEnd");
			break;
		case DIRECTION_UP:
			if(m_momo.m_momoAni == MOMO_MOVE) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Top_AttackReady");
			if(m_momo.m_momoAni == MOMO_ATTACKREADY) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Top_Attack");
			if (m_momo.m_momoAni == MOMO_ATTACK) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Top_AttackEnd");
			break;
		case DIRECTION_DOWN:
			if(m_momo.m_momoAni == MOMO_MOVE) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Bottom_AttackReady");
			if(m_momo.m_momoAni == MOMO_ATTACKREADY) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Bottom_Attack");
			if(m_momo.m_momoAni == MOMO_ATTACK) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Bottom_AttackEnd");
			break;
		case DIRECTION_LEFTUP:
			if(m_momo.m_momoAni == MOMO_MOVE) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Left_AttackReady");
			if(m_momo.m_momoAni == MOMO_ATTACKREADY) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Left_Attack");
			if (m_momo.m_momoAni == MOMO_ATTACK)
				m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Left_AttackEnd");
			break;
		case DIRECTION_RIGHTDOWN:
			if(m_momo.m_momoAni == MOMO_MOVE) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Right_AttackReady");
			if(m_momo.m_momoAni == MOMO_ATTACKREADY) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Right_Attack");
			if (m_momo.m_momoAni == MOMO_ATTACK) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Right_AttackEnd");
			break;
		case DIRECTION_LEFTDOWN:
			if(m_momo.m_momoAni == MOMO_MOVE) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Left_AttackReady");
			if(m_momo.m_momoAni == MOMO_ATTACKREADY) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Left_Attack");
			if(m_momo.m_momoAni == MOMO_ATTACK) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Left_AttackEnd");
			break;
		case DIRECTION_RIGHTUP:
			if(m_momo.m_momoAni == MOMO_MOVE) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Right_AttackReady");
			if(m_momo.m_momoAni == MOMO_ATTACKREADY) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Right_Attack");
			if (m_momo.m_momoAni == MOMO_ATTACK) m_momo.m_ani = ANIMATIONMANAGER->findAnimation("momo_Right_AttackEnd");
			break;
		}	

		if (m_momo.m_momoAni == MOMO_ATTACKREADY && m_momo.m_ani->getPlayIndex() == m_momo.m_ani->getPlaySize().size() - 1 && m_momo.attackCount <= 3)
		{
			m_momo.attackCount += 1;
			m_momo.m_ani->setPlayIndex(0);
		}

	}
	if (m_momo.m_momoAni == MOMO_MOVE && m_momo.m_ani->getPlayIndex() == m_momo.m_ani->getPlaySize().size()-1)
	{
		m_momo.m_momoAni = MOMO_ATTACKREADY;
	}

	if (m_momo.m_momoAni == MOMO_ATTACKREADY && m_momo.m_ani->getPlayIndex() == m_momo.m_ani->getPlaySize().size()-1 && m_momo.attackCount == 4)
	{
		m_momo.m_momoAni = MOMO_ATTACK;
		m_momo.attackCount = 0;
	}

	if (m_momo.m_momoAni == MOMO_ATTACK && m_momo.m_ani->getPlayIndex() == m_momo.m_ani->getPlaySize().size()-1 )
	{
		m_momo.m_momoAni = MOMO_ATTACKREADY;
	}

}
