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
	ITEMMANAGER->addItem("�Ʒÿ�ܰ�", "�Ʒÿ�ܰ�", 1000, 500, 0);
	ITEMMANAGER->addItem("�÷��Ӻ���", "�÷��Ӻ���", 1000, 500, 0);
	ITEMMANAGER->addItem("�߰�����", "�߰�����", 300, 150, 0);
	ITEMMANAGER->addItem("�̽�", "item1", 0, 50, 0);
	ITEMMANAGER->addItem("����", "item2", 0, 80, 0);
	ITEMMANAGER->addItem("�볪��", "item3", 0, 100, 0);
	ITEMMANAGER->addItem("����", "item4", 0, 30, 0);
	ITEMMANAGER->addItem("������", "item5", 0, 50, 0);
	ITEMMANAGER->addItem("��������", "item6",0, 80, 0);
	ITEMMANAGER->addItem("¤", "item7", 0, 40, 0);

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


