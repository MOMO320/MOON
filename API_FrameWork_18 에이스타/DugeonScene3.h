#pragma once
#include "scene.h"
#include "dungeonMap3.h"
#include "fly.h"
#include "Momo.h"
#include "aStar.h"

class DugeonScene3 : public scene
{
public:
	DugeonScene3();
	~DugeonScene3();

	HRESULT init();
	void release();
	void update();
	void render();

private:
	dungeonMap3 * m_Map3;
	fly * c_fly;
	fly * c_fly2;
	fly * c_fly3;
	Momo * c_momo;
	aStar * c_aStar;


	vector<fly*> v_fly;
	bool isOnce = false;
	float time, past = 0.f;
	float addDeley = 3.0f;

};

