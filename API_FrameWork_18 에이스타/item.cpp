#include "stdafx.h"
#include "item.h"

item::item()
{
}

item::~item()
{
}

HRESULT item::init()
{
	ITEMMANAGER->addItem("훈련용단검", "훈련용단검", 1000, 500, 0);
	ITEMMANAGER->addItem("플레임보우", "플레임보우", 1000, 500, 0);
	ITEMMANAGER->addItem("중간포션", "중간포션", 300, 150, 0);
	ITEMMANAGER->addItem("이슬", "item1", 0, 50, 0);
	ITEMMANAGER->addItem("열매", "item2", 0, 80, 0);
	ITEMMANAGER->addItem("통나무", "item3", 0, 100, 0);
	ITEMMANAGER->addItem("양파", "item4", 0, 30, 0);
	ITEMMANAGER->addItem("나뭇잎", "item5", 0, 50, 0);
	ITEMMANAGER->addItem("빨간열매", "item6",0, 80, 0);
	ITEMMANAGER->addItem("짚", "item7", 0, 40, 0);

	return S_OK;
}

void item::release()
{
}

void item::update()
{
}

void item::render()
{
}


