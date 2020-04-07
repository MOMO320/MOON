#pragma once
#include "gameNode.h"
#include "dungeonMap.h"
#include "arrow.h"
#include "objectManager.h"
#include "Ui.h"
#include "invenScene.h"

struct playerInfo
{
	PLAYERDIRECTION m_playerDirect;		// player ����
	PLAYERSTATUS	m_playerStatus;		// player ���� �ִϸ��̼� �ؾ��� ����
	ANISTATUS		m_aniStauts;		// player �ִϸ��̼� ��Ȳ
	WEAPONEANI		m_weaponAni;		// ���⺰ �ִϸ��̼�


	RECT _rc;							// player�� �浹 rect
	RECT m_playerInPlace;				// player�� �̵� ����
	RECT fightRc;
	
	image* m_img[5];					// player img
	animation* m_ani;				// player ani
	animation* m_bigAni;

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
	void update( dungeonMap* _dungMap , bool _isCamera , RECT _playerMove);
	void render(HDC _hdc);
	void cameraRender();

	void characterMove(dungeonMap* _dungMap);
	void setCharacPosition(RECT rc);
	void setTankMapMemoryAdress(dungeonMap * _dungMap) { m_dunMap = _dungMap; }
	RECT getPlayerRect() { return m_player._rc; }
	playerInfo getPlayerInfo() { return m_player; }
	//image * getPlayerImage() { return m_player.m_img; }

	void wallCollision(RECT wallRc[]);
	//playerInfo getPlayerInfo() { return m_player; }
	playerInfo m_player; // �÷��̾� ����

public:
	int m_frameY;
	float m_speed;
	float m_x, m_y;
	int m_tileX, m_tileY;	// �÷��̾ ��� �ִ� Ÿ�� ��ȣ
	
private:
	void animation(PLAYERDIRECTION _Directtion , PLAYERSTATUS _status , ANISTATUS _aniStatus , WEAPONEANI _weapone , dungeonMap* _dungMap , bool _isCamera);


private:
	invenScene *    m_invenScene;
	dungeonMap*		m_dunMap;
	arrow*			m_arrow;
	objectManager * m_objManager;
	Ui*				m_ui;


	RECT rcCollision;

	int  m_attackCombo = 0;
	bool m_isCombo = false;
	bool m_isRoll = false;
	bool m_isBow = false;
	bool m_bowAniOnce = false;
	bool m_bowAlpha = false;

	bool m_walk = false;
	bool m_rightWalk = false;

	float pastTime = 0;
	float addDeleyTime = 2.0f;
	float time = 0;

	int m_weaponeChangeCount = 0;

	// �κ���
	bool isInvneScene = false;
	
};

