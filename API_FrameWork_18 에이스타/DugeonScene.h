#pragma once
#include "scene.h"
#include "dungeonMap1.h"
#include "miniSlime.h"
#include "flea.h"
#include "mushRoom.h"
#include "dungeonMap4.h"

class DugeonScene : public scene
{
public:
	DugeonScene();
	~DugeonScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void collision();
	void deathDelete();

private:
	dungeonMap1 * m_Map1;
	dungeonMap4 * m_Map4;
	miniSlime*  m_miniSlime1;
	miniSlime*  m_miniSlime2;
	miniSlime*  m_miniSlime3;
	flea*		m_flea1;
	mushRoom*   m_mushRoom1;
	mushRoom*   m_mushRoom2;

	vector<flea*> _fleas;
	vector<miniSlime*> _miniSlimes;
	vector<mushRoom*> _mushRooms;
	int damage;
	bool isDamage = false;

	float addDeley = 1.0f;
	float pastTime = 0.0f;

	float time = 0.0f , diePastTime = 0.0f;
	float addDieTime = 1.0f;
};

