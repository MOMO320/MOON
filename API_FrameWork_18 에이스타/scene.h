#pragma once
#include "gameNode.h"
#include "player.h"

class scene : public gameNode
{
public:
	scene();
	~scene();

	HRESULT init();
	void release();
	void update();
	void render();

protected:
	int m_count;

};

