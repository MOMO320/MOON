#pragma once
#include "gameNode.h"
#include "dungeonMap.h"

enum PLAYERDIRECTION
{
	PLAYER_LEFT,
	PLAYER_UP,
	PLAYER_RIGHT,
	PLAYER_DOWN
};

class player : public gameNode
{
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void characterMove();
	void setCharacPosition(RECT rc);
	void setTankMapMemoryAdress(dungeonMap* _dungMap) { m_dungeonMap = _dungMap; }

public:
	int m_frameY;
	float m_speed;
	float m_x, m_y;
	int m_tileX, m_tileY;	// ��ũ�� ��� �ִ� Ÿ�� ��ȣ
	

private:
	RECT _rc;
	RECT m_playerInPlace;
	dungeonMap * m_dungeonMap;
	PLAYERDIRECTION m_playerDirect;
	image* m_img;

	
};

