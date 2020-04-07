#pragma once
#include "gameNode.h"
#include "dungeonMap.h"
#include "arrow.h"
#include "objectManager.h"
#include "Ui.h"
#include "invenScene.h"

struct playerInfo
{
	PLAYERDIRECTION m_playerDirect;		// player 방향
	PLAYERSTATUS	m_playerStatus;		// player 현재 애니메이션 해야할 상태
	ANISTATUS		m_aniStauts;		// player 애니메이션 상황
	WEAPONEANI		m_weaponAni;		// 무기별 애니메이션


	RECT _rc;							// player의 충돌 rect
	RECT m_playerInPlace;				// player의 이동 범위
	RECT fightRc;
	
	image* m_img[5];					// player img
	animation* m_ani;				// player ani
	animation* m_bigAni;

	int m_speed;						//	속도
	int m_attack;						// 공격력
	int m_hp;							// hp
	int m_dev;							// 방어력
	int m_money;						// 소지금
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
	playerInfo m_player; // 플레이어 정의

public:
	int m_frameY;
	float m_speed;
	float m_x, m_y;
	int m_tileX, m_tileY;	// 플레이어가 밟고 있는 타일 번호
	
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

	// 인벤씬
	bool isInvneScene = false;
	
};

