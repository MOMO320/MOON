#pragma once
#include "gameNode.h"
#include "dungeonMap1.h"

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
	void setTankMapMemoryAdress(dungeonMap1* _dungMap1) { m_dunMap1 = _dungMap1; }
	RECT getPlayerRect() { return _rc; }

public:
	int m_frameY;
	float m_speed;
	float m_x, m_y;
	int m_tileX, m_tileY;	// 탱크가 밟고 있는 타일 번호
	

private:
	RECT _rc;
	RECT m_playerInPlace;
	dungeonMap1 * m_dunMap1;
	PLAYERDIRECTION m_playerDirect;
	image* m_img;

	
};

