#pragma once
#include "dungeonMap.h"

class toDungeonMap : public dungeonMap
{
public:
	toDungeonMap();
	~toDungeonMap();

	HRESULT init() override;
	void release()override;
	void update()override;
	void render()override;

	DWORD*				getAttribute() override { return m_attribute; }
	tagTile*			getMap() override { return m_map; }
	int					getPosFirst() override { return m_pos[0]; }
	int					getPosSecond() override { return m_pos[1]; }
	collisionWwall *	getCollisionWAll() override { return m_wall; }

	tagTile				 m_map[2]; // �ǹ̾���
	collisionWwall		m_wall[4]; // �ǹ̾���
	image * toDungeon;
	RECT m_intoDungeonCollision;


protected:
	DWORD			   m_attribute[2];  // �ǹ̾���
	tagOnceTile	       m_onceMap[2];	// �ǹ̾���
	int				   m_pos[2];		// �ǹ̾���
	

};

