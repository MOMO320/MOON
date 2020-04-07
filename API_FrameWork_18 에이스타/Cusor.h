#pragma once
#include "gameNode.h"

struct CusorInfo
{
	vector<itemInfo> v_cusorItem;
	RECT	cusorRect;
	RECT	chooseRect;
	image*	cusorImg;
	image*	choiceImg;
};

class Cusor : public gameNode
{
public:
	Cusor();
	~Cusor();

	HRESULT init();
	void release();
	void update(vector<itemInfo> _vItem , vector<RECT> _vRect);
	void render(vector<RECT> _vRect);
	void chooseItem(vector<itemInfo> _vItem);
	void intoItem(vector<itemInfo> _vItem, vector<RECT> _vRect);
	int changeRect();
	int chooseRect();

private:
	CusorInfo cusor;
	int cusorX = 0;
	int cusorY = 0;
	bool isChoose = false;

	//선택된 아이템 담고 있기
	int chooseX = 0;
	int chooseY = 0;
	int putX = 0;
	int putY = 0;
	int enterCount = 0;

};

