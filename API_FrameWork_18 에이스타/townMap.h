#pragma once
#include "dungeonMap.h"

class townMap : public dungeonMap
{
public:
	townMap();
	~townMap();

	HRESULT init() override;
	void release()override;
	void update()override;
	void render()override;

	DWORD*				getAttribute() override { return m_attribute; }
	tagTile*			getMap() override { return m_map; }
	int					getPosFirst() override { return m_pos[0]; }
	int					getPosSecond() override { return m_pos[1]; }
	collisionWwall *	getCollisionWAll() override { return m_wall; }
	RECT*				getChangeSceneRect() { return m_changeSceneRect; }

	tagTile				 m_map[2];

	collisionWwall		m_wall[4];

private:
	DWORD			   m_attribute[2];  // 의미없음
	tagOnceTile	       m_onceMap[2];	// 의미없음
	int				   m_pos[2];		// 의미없음
	//=============================================//
	image * townImg;
	RECT	m_changeSceneRect[2];



};

