#pragma once
#include "inven.h"

class invenScene : public inven
{
public:
	invenScene();
	~invenScene();

	HRESULT init();
	void release();
	void update();
	void render(int _playerHp , int _playerAttack, int _Dev , int _playerSpeed);

private:
	inven * m_inven;
	image * imgInven;


};

