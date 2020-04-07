#pragma once
#include "scene.h"
#include "dungeonMap2.h"
#include "bazookaFlower.h"


class DugeonScene2 : public scene
{
public:
	DugeonScene2();
	~DugeonScene2();

	HRESULT init();
	void release();
	void update();
	void render();

private:
	dungeonMap2 * m_Map2;
	bazookaFlower * m_bazookaFlower1;
	bazookaFlower * m_bazookaFlower2;


	// 시간 함수
	float  pastTime = 0;
	float  addDeley = 3.0f;
};

