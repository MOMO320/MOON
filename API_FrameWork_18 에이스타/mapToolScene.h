#pragma once
#include "gameNode.h"
#include "mapTool.h"

class mapToolScene : public gameNode
{
public:
	mapToolScene();
	~mapToolScene();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;
	//virtual void setMap() override;


private:
	mapTool* m_mapTool;

};
