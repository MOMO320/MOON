#include "stdafx.h"
#include "itemManager.h"

itemManager::itemManager()
{
}

itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	
	return S_OK;
}

void itemManager::release()
{
	IMAGEMANAGER->deleteAll();
}

void itemManager::update()
{
}

void itemManager::render()
{
	if (v_item.size() > 0)
	{
		for (int i = 0; i < v_item.size(); i++)
		{
			v_item[i].img->render(CAMERAMANAGER->getCameraDC(), v_item[i].rc.left, v_item[i].rc.top);
		}
	}
}

void itemManager::addItem(string _name, const char * _img, int _price, int _sellPrice ,int _healHp)
{
	item.name = _name;
	item.img = IMAGEMANAGER->findImage(_img);
	item.price = _price;
	item.sellPrice = _sellPrice;
	item.healHp = _healHp;

	v_item.push_back(item);
	map_item.insert(std::make_pair(_name,v_item));
}

vector<itemInfo> itemManager::findItem(string _name)
{		
	return map_item.find(_name)->second;
}

RECT itemManager::itemRectSet(int _num)
{
	return v_item.at(_num).rc;
}
