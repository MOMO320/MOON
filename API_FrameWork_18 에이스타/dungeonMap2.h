#pragma once
#include "dungeonMap.h"


class dungeonMap2 : public dungeonMap
{
public:
	dungeonMap2();
	~dungeonMap2();

	HRESULT init() override;
	void release()override;
	void update()override;
	void render()override;

	void wallRectSet();


	DWORD*				getAttribute() override { return m_attribute; }
	tagTile*			getMap() override { return m_map; }
	int					getPosFirst() override { return m_pos[0]; }
	int					getPosSecond() override { return m_pos[1]; }
	collisionWwall *	getCollisionWAll() override { return m_wall; }

	tagTile				 m_map[BACKTILEX * BACKTILEY];

private:
	DWORD			   m_attribute[BACKTILEX * BACKTILEY];
	tagOnceTile	       m_onceMap[2];
	int				   m_pos[2];
	collisionWwall	   m_wall[4];
	collisionWwall		m_wall22;

};

