#pragma once
#include "gameNode.h"
#include "dungeonMap.h"
#define RECTDIRECT  50
#define OBJECTSPEED	20


class objectManager : public gameNode
{
public:
	objectManager();
	~objectManager();

	 HRESULT init();
	 void release();
	 void update(THROWOBJECTINFO _object,RECT _rc );
	 void render();
	 void objectMove(THROWOBJECTINFO _object,  dungeonMap * _dunMap, PLAYERDIRECTION _direction);
	 void objectMove(THROWOBJECTINFO _object,  dungeonMap * _dunMap, ENEMYDIRECTION _direction,int speed);
	 void setObjPosition(THROWOBJECTINFO _object , RECT _rc);
	 
	 void setisConnect(bool _isConnect) { m_isConnect = _isConnect; }
	 bool getisConnect() { return m_isConnect; }


	 RECT getobject() { return temp; }
	 RECT getRcCollision() { return rcCollision; }
	 
	 int  getX() { return m_x; }
	 int  getY() { return m_y; }


	 bool m_isConnect;

private:
	int m_frameY;
	float m_speed;
	float m_x, m_y;
	int m_tileX, m_tileY;	
	RECT temp;
	RECT rcCollision;

};

