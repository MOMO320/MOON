#pragma once
#include "scene.h"
#include "dungeonMap1.h"
#include "aStar.h"
#include "miniSlime.h"
#include "flea.h"
#include "mushRoom.h"

class DugeonScene : public scene
{
public:
	DugeonScene();
	~DugeonScene();

	HRESULT init();
	void release();
	void update();
	void render();

private:
	dungeonMap1 * m_Map1;
	aStar*		m_aStar;
	aStar*		m_aStar1;
	aStar*		m_aStar2;
	aStar*		m_aStar3;
	miniSlime*  m_miniSlime;
	miniSlime*  m_miniSlime2;
	miniSlime*  m_miniSlime3;
	flea*		m_flea1;
	mushRoom*   m_mushRoom;
	mushRoom*   m_mushRoom1;


};

