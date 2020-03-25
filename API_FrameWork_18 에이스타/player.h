#pragma once
#include "gameNode.h"
#include "dungeonMap.h"
#include "arrow.h"
#include "objectManager.h"

struct playerInfo
{
	PLAYERDIRECTION m_playerDirect;		// player ����
	PLAYERSTATUS	m_playerStatus;		// player ���� �ִϸ��̼� �ؾ��� ����
	ANISTATUS		m_aniStauts;		// player �ִϸ��̼� ��Ȳ
	WEAPONEANI		m_weaponAni;		// ���⺰ �ִϸ��̼�


	RECT _rc;							// player�� �浹 rect
	RECT m_playerInPlace;				// player�� �̵� ����
	
	image* m_img[5];					// player img
	animation* m_ani;				// player ani

	int m_speed;						//	�ӵ�
	int m_attack;						// ���ݷ�
	int m_hp;							// hp
	int m_dev;							// ����
	int m_money;						// ������
};

class player : public gameNode
{
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update(dungeonMap* _dungMap);
	void render();

	void characterMove(dungeonMap* _dungMap);
	void setCharacPosition(RECT rc);
	void setTankMapMemoryAdress(dungeonMap * _dungMap) { m_dunMap = _dungMap; }
	RECT getPlayerRect() { return m_player._rc; }
	//playerInfo getPlayerInfo() { return m_player; }
	playerInfo m_player; // �÷��̾� ����

public:
	int m_frameY;
	float m_speed;
	float m_x, m_y;
	int m_tileX, m_tileY;	// �÷��̾ ��� �ִ� Ÿ�� ��ȣ
	
private:
	void animation(PLAYERDIRECTION _Directtion , PLAYERSTATUS _status , ANISTATUS _aniStatus , WEAPONEANI _weapone , dungeonMap* _dungMap);


private:
	dungeonMap*		m_dunMap;
	arrow*			m_arrow;
	objectManager * m_objManager;

	RECT rcCollision;

	int  m_attackCombo = 0;
	bool m_isCombo = false;
	bool m_isRoll = false;
	bool m_isBow = false;
	bool m_bowAniOnce = false;
	bool m_bowAlpha = false;

	float pastTime = 0;
	float addDeleyTime = 1.0f;
	float time = 0;

	int m_weaponeChangeCount = 0;


	
};

