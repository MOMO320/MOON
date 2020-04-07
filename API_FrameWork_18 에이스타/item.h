#pragma once
#include "itemManager.h"

class item : public itemManager
{
public:
	item();
	~item();

	HRESULT init();
	void release();
	void update();
	void render();

private:

};

