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
	 void update(RECT _playerRc, RECT _enemyRc, int _objectSpeed);
	 void render();
	 void objectMove(THROWOBJECTINFO _object,  dungeonMap * _dunMap, PLAYERDIRECTION _direction);
	 void objectMove(THROWOBJECTINFO _object,  dungeonMap * _dunMap, ENEMYDIRECTION _direction,int speed);
	 void obectFollowMove(THROWOBJECTINFO _object, dungeonMap * _dunMap, int speed);
	 
	 void objectDirect(RECT _enemyRc , THROWOBJECTINFO _object, dungeonMap * _dunMap, RECT _playerRc,int _objectSpeed );
	 
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
	int m_x, m_y;
	int m_tileX, m_tileY;	
	RECT temp;
	RECT rcCollision;

	// 타임매니저쓸 부분 
	float pastTime = 0.0f;
	float time;
	float addDeley = 0.05f;

	// 방향 정하는 bool 값
	bool m_isDongo = false;
	Direction	_enemyObjectDirect;
	PLAYERDIRECTION _playerDirect;

};

