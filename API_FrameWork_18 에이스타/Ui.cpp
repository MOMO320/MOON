#include "stdafx.h"
#include "Ui.h"

Ui::Ui() : m_HpBar(new progressBar)
{
}

Ui::~Ui()
{
	delete m_HpBar;
}

HRESULT Ui::init()
{
	// ÁÂÃø
	hpBar.img = IMAGEMANAGER->findImage("hpBarBack");
	hpBar.secondImg = IMAGEMANAGER->findImage("hpBar");
	hpBar.rc = RectMake(140, 38, hpBar.img->getWidth(), hpBar.img->getHeight());

	m_HpBar->init("images/Ui/blood.bmp","images/Ui/hpBar.bmp" , hpBar.rc.left, hpBar.rc.top, hpBar.img->getWidth(), hpBar.img->getHeight(), hpBar.rc.left + 45 , hpBar.rc.top, hpBar.secondImg->getWidth(),hpBar.secondImg->getHeight());

	moneyUi.img = IMAGEMANAGER->findImage("moneyUi");
	moneyUi.rc = RectMake(30, 25, moneyUi.img->getWidth(), moneyUi.img->getHeight());

	cashButton.img = IMAGEMANAGER->findImage("cashUi");
	cashButton.rc = RectMake(5, moneyUi.rc.bottom -15, cashButton.img->getWidth(), cashButton.img->getHeight());
	
	// ¿ìÃø
	invenUi.img = IMAGEMANAGER->findImage("invenButtonUi");
	invenUi.rc = RectMake(WINSIZEX - (30 + invenUi.img->getWidth()), 150, invenUi.img->getWidth(), invenUi.img->getHeight());
	
	equipmentUi.img = IMAGEMANAGER->findImage("backRoundUi");
	equipmentUi.secondImg = IMAGEMANAGER->findImage("ÈÆ·Ã¿ë´Ü°Ë");
	equipmentUi.rc = RectMake(WINSIZEX - (30 + invenUi.img->getWidth()), 30, equipmentUi.img->getWidth(), equipmentUi.img->getHeight());

	aButton.img = IMAGEMANAGER->findImage("aButtonUi");
	aButton.rc = RectMake(equipmentUi.rc.left + (equipmentUi.img->getWidth()/2)/2, equipmentUi.rc.bottom - 10, equipmentUi.img->getWidth(), equipmentUi.img->getHeight());

	qButton.img = IMAGEMANAGER->findImage("qButtonUi");
	qButton.rc = RectMake(equipmentUi.rc.left - 35, (equipmentUi.rc.top + 25), equipmentUi.img->getWidth(), equipmentUi.img->getHeight());

	iButton.img = IMAGEMANAGER->findImage("iButtonUi");
	iButton.rc = RectMake(invenUi.rc.left - 20, invenUi.rc.bottom - 20, iButton.img->getWidth(), iButton.img->getHeight());

	return S_OK;
}

void Ui::release()
{
	IMAGEMANAGER->deleteAll();
	m_HpBar->release();
}

void Ui::update(int _weaponeCount)
{
	if (_weaponeCount == 0)
	{
		equipmentUi.secondImg = IMAGEMANAGER->findImage("ÈÆ·Ã¿ë´Ü°Ë");
	}
	if (_weaponeCount == 1)
	{
		equipmentUi.secondImg = IMAGEMANAGER->findImage("ÇÃ·¹ÀÓº¸¿ì");
	}
	m_HpBar->update(hpBar.rc.left, hpBar.rc.top);
	m_HpBar->setGauge(M_PLAYER.m_player.m_hp, 100);
}

void Ui::render(int _playerMoney, int _playerHp, HDC _hdc)
{
	int intHp = 100;
	string hp = to_string(intHp);
	string slush = "/";
	string currentHp = to_string(_playerHp);
	currentHp += slush;
	currentHp += hp;

	moneyUi.img->render(_hdc, moneyUi.rc.left, moneyUi.rc.top);
	cashButton.img->render(_hdc, cashButton.rc.left, cashButton.rc.top);

	invenUi.img->render(_hdc, invenUi.rc.left, invenUi.rc.top);
	equipmentUi.img->render(_hdc, equipmentUi.rc.left, equipmentUi.rc.top);
	equipmentUi.secondImg->render(_hdc, equipmentUi.rc.left + 5, equipmentUi.rc.top + 5);
	
	qButton.img->render(_hdc, qButton.rc.left, qButton.rc.top);
	aButton.img->render(_hdc, aButton.rc.left, aButton.rc.top);
	iButton.img->render(_hdc, iButton.rc.left, iButton.rc.top);
	
	m_HpBar->render(hpBar.rc.left, hpBar.rc.top, 48,-5);

	printText(_hdc, to_string(_playerMoney).c_str(), "³ª´®½ºÄù¾î_ac Bold", cashButton.rc.right - 10 , cashButton.rc.top + 18, 20, RGB(255, 255, 255), true, RGB(255, 0, 255));
	printText(_hdc, currentHp.c_str(), "³ª´®½ºÄù¾î_ac Bold", hpBar.rc.right - 80, hpBar.rc.bottom , 20, RGB(255, 255, 255), true, RGB(255, 0, 255));
}
