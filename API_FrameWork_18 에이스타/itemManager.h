#pragma once
#include "singletonBase.h"

class itemManager : public singletonBase<itemManager>
{
public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addItem(string _name, const char * _img, int _price, int _sellPrice, int _healHp);
	vector<itemInfo> findItem(string _name);
	RECT itemRectSet(int _num);
	vector<itemInfo> v_item;

private:
	map<string,vector<itemInfo>> map_item;
	itemInfo item;

};

