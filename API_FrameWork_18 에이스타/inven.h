#pragma once
#include "gameNode.h"
#include "item.h"
#include "Cusor.h"
#define LEFTINVENX 260
#define LEFTINVENY 178
#define RECTRANGE 71


class inven : public gameNode
{
public :	
	inven();
	~inven();

	HRESULT init();
	void release();
	void update();
	void render(int _playerHp, int _playerAttack, int _Dev, int _playerSpeed);
	void cusorRender();
	void invenRectSet();
	void itemRectSet();
	vector<RECT> getLeftRect() { return v_invenLeftRect; }

	vector<itemInfo> v_invenItem;
	vector<itemInfo> v_weaponeItem;
	vector<RECT> v_invenLeftRect;
	vector<RECT> v_invenRightRect;
	RECT playerView;

protected:
	Cusor* m_cusor;
	RECT invenTopRect[5];
	RECT invenMidRect[15];
	RECT showItem;
	RECT weaponeRect[2];
	RECT wearEquipment[3];
	
	

	RECT textRect[4];

};

