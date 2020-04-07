#pragma once
#include "gameNode.h"
#include "progressBar.h"

struct uiButton
{
	image* img;
	RECT   rc;
	image *  secondImg;
	bool   isActive;
};

struct uiInfo
{
	image*   img;
	RECT     rc;
	image *  secondImg;
};


class Ui : public gameNode
{
public:
	Ui();
	~Ui();

	HRESULT init();
	void release();
	void update(int _weaponeCount);
	void render(int _playerMoney, int _playerHp , HDC _hdc);

private:
	progressBar * m_HpBar;
	uiInfo		hpBar;
	uiButton	aButton;
	uiButton	iButton;
	uiButton	qButton;
	uiInfo		moneyUi;
	uiButton	cashButton;
	uiButton	invenUi;
	uiInfo		equipmentUi;

	int countEquipKind = 0;
	bool isOnceChange = false;

};

