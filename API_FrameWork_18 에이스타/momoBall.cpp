#include "stdafx.h"
#include "momoBall.h"

momoBall::momoBall()
{
	srand(NULL);
}

momoBall::~momoBall()
{
}

HRESULT momoBall::init(char * imgaeName, int bulletMax, float range)
{
	m_imageName = imgaeName;
	m_bulletMax = bulletMax;
	m_range = range;

	return S_OK;
}

void momoBall::release()
{
	IMAGEMANAGER->release();
}

void momoBall::update()
{
	time = TIMEMANAGER->getElapsedTime();
	move();
}

void momoBall::render()
{
	if (KEYMANAGER->isToggleKey(VK_F3))
	{	
	}

	m_viBullet = m_vBullet.begin();
	for (m_viBullet; m_viBullet != m_vBullet.end(); ++m_viBullet)
	{
		if (m_viBullet->connect == false)
		{
		   //Rectangle(getMemDC(), m_viBullet->rc.left, m_viBullet->rc.top, m_viBullet->rc.right, m_viBullet->rc.bottom);
		   m_viBullet->bulletImage->render(getMemDC(), m_viBullet->rc.left +30, m_viBullet->rc.top);
		}

		if (m_viBullet->connect == true)
		{
			m_viBullet->bulletImage->aniRender(getMemDC(), m_viBullet->rc.left + 30, m_viBullet->rc.top, m_viBullet->ani);
		}
	}

}

void momoBall::fire(float x, float y, float angle, float speed)
{
	objectPastTime += time;
	
	if (isFullObject == false)
	{
	    for (int i = 0; i < m_bulletMax; i++)
	    {
	    	if (objectDeley < objectPastTime)
	    	{
	            objectBullet bullet;
	            ZeroMemory(&bullet, sizeof(objectBullet));
	            bullet.bulletImage = new image;
	            bullet.bulletImage = IMAGEMANAGER->findImage(m_imageName);
				bullet.ani = ANIMATIONMANAGER->findAnimation("momoObjecAni");
				bullet.connect = false;
				bullet.angle = angle;
	            bullet.speed = speed;
	            bullet.x = bullet.fireX = x + (rand()% 30);
	            bullet.y = bullet.fireY = y + (rand()& 30);
	            bullet.rc = RectMakeCenter(bullet.x , bullet.y /*+ ((i % 4) * 15)*/,
	            	bullet.bulletImage->getWidth(),
	            	bullet.bulletImage->getHeight());
	            
	    		objectPastTime = 0.0f;
	            m_vBullet.push_back(bullet);
	    	}
	    }
	}

	if (m_vBullet.size() == 12)
	{
		isFullObject = true;
	}
}

void momoBall::move()
{
	for (m_viBullet = m_vBullet.begin(); m_viBullet != m_vBullet.end();)
	{
		if (m_viBullet->connect == false)
		{
		    m_viBullet->x += cosf((m_viBullet->angle)) *  m_viBullet->speed;
		    m_viBullet->y += -sinf(m_viBullet->angle /*+ ((ballCount % 4) * 1)*/) * m_viBullet->speed;
		    
		    m_viBullet->rc = RectMakeCenter(m_viBullet->x, m_viBullet->y,
		    	m_viBullet->bulletImage->getWidth(),
		    	m_viBullet->bulletImage->getHeight());
		    ballCount += 1;
		    if (ballCount == 4) ballCount = 0;
		    
		    if (m_range < getDistance(m_viBullet->x, m_viBullet->y, m_viBullet->fireX, m_viBullet->fireY))
		    {
		    	m_viBullet = m_vBullet.erase(m_viBullet);
		    }
		    else ++m_viBullet;
		    pastTime = 0;
		}
		else
		{
			++m_viBullet;
		}
	}	
}

void momoBall::connectBullet(int addNum)
{
	if (m_vBullet.at(addNum).connect == false)
	{
		m_vBullet.at(addNum).ani->start();
		m_vBullet.at(addNum).connect = true;
		m_vBullet.at(addNum).bulletImage = IMAGEMANAGER->findImage("momoObjectBoom");
	}
	if (m_vBullet.at(addNum).ani->getPlayIndex() == 5)
	{
		m_vBullet.at(addNum).connect = false;
		removeBullet(addNum);
	}
}

void momoBall::removeBullet(int arrNum)
{
	//m_vBullet.at(arrNum).connect = false;
	
	m_vBullet.erase(m_vBullet.begin() + arrNum);
}
