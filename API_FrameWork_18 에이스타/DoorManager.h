#pragma once
#include "gameNode.h"
#include "gameTypes.h"
class DoorManager : public gameNode
{
public:
	DoorManager();
	~DoorManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void doorInit(const char* _img, const char* _ani, RECT _intoREct, RECT _imgRECT, DOORSTATUS _status);
	void doorAni();
	void aniStart();

private:
	DungeonDoor door;
	animation * tempAni;

};

