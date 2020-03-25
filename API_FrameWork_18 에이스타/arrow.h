#pragma once
#include "objectManager.h"

class arrow : public objectManager
{
public:
	arrow();
	~arrow();

	HRESULT init(RECT _rc);
	void release();
	void update(RECT _rc , PLAYERDIRECTION _direct);
	void render(WEAPONEANI _weapone);

	void setArrowX(int _X) { m_arrow.m_x = _X; }
	void setArrowY(int _Y) { m_arrow.m_y = _Y; }
	void setMainRect(RECT _rc) { m_arrow.m_mainRc = _rc; }

	THROWOBJECTINFO getArrowInfo() { return m_arrow; }
	void setObjectRect(RECT _rc) { m_arrow.m_rc = _rc; }


private:
	THROWOBJECTINFO  m_arrow;
	objectManager *  m_objectManager;

};

