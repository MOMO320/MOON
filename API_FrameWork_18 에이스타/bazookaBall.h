#pragma once
#include "objectManager.h"

class bazookaBall : public objectManager
{
public:
	bazookaBall();
	~bazookaBall();

	HRESULT init();
	void release();
	void update(RECT _enemyRc , bool _isConnect);
	void render(bool _isConnect);

	void setBazookaBallX(int _X) { m_bazookaBall.m_x = _X; }
	void setBazookaBallY(int _Y) { m_bazookaBall.m_y = _Y; }
	void setMainRect(RECT _rc) { m_bazookaBall.m_mainRc = _rc; }

	THROWOBJECTINFO getBazookaBallInfo() { return m_bazookaBall; }
	void setObjectRect(RECT _rc) { m_bazookaBall.m_rc = _rc; }
	
private:
	THROWOBJECTINFO  m_bazookaBall;
	objectManager *  m_objectManager;
	bool			 m_isOnceAni = false;

};

