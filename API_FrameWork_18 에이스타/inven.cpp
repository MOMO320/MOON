#include "stdafx.h"
#include "inven.h"

inven::inven() :m_cusor(new Cusor)
{
}

inven::~inven()
{
	delete m_cusor;
}

HRESULT inven::init()
{
	ITEMMANAGER->init();
	invenRectSet();
	
	v_weaponeItem.push_back(ITEMMANAGER->v_item.at(0));
	v_weaponeItem.push_back(ITEMMANAGER->v_item.at(1));
	v_invenItem.push_back(ITEMMANAGER->v_item.at(3));
	v_invenItem.push_back(ITEMMANAGER->v_item.at(6));
	
	m_cusor->init();
	itemRectSet();

	return S_OK;
}

void inven::release()
{
	m_cusor->release();
}

void inven::update()
{
	m_cusor->update(v_invenItem, v_invenLeftRect);
	v_invenItem.at(m_cusor->chooseRect()).rc = v_invenLeftRect[m_cusor->changeRect()];
}

void inven::render(int _playerHp, int _playerAttack, int _Dev, int _playerSpeed)
{
	if (KEYMANAGER->isToggleKey(VK_F3))
	{
	    for (int i = 0 ; i < v_invenLeftRect.size(); i++)
	    {
	    	Rectangle(CAMERAMANAGER->getCameraDC(), v_invenLeftRect.at(i).left, v_invenLeftRect.at(i).top, v_invenLeftRect.at(i).right, v_invenLeftRect.at(i).bottom);
	    }
	    for (int i = 0; i < v_invenRightRect.size(); i++)
	    {
	    	Rectangle(CAMERAMANAGER->getCameraDC(), v_invenRightRect.at(i).left, v_invenRightRect.at(i).top, v_invenRightRect.at(i).right, v_invenRightRect.at(i).bottom);
	    }
	}

	for (int i = 0; i < v_invenItem.size(); i++)
	{
		v_invenItem[i].img->render(CAMERAMANAGER->getCameraDC(), v_invenItem[i].rc.left, v_invenItem[i].rc.top);
	}

	for (int i = 0; i < v_weaponeItem.size(); i++)
	{
		v_weaponeItem[i].img->render(CAMERAMANAGER->getCameraDC(), v_weaponeItem[i].rc.left, v_weaponeItem[i].rc.top);
	}

	//playerStatus 랜더
	printText(CAMERAMANAGER->getCameraDC(), to_string(_playerHp).c_str(), "나눔스퀘어_ac Bold", textRect[0].left + 5, textRect[0].top + 5, 30, RGB(255, 255, 255), true, RGB(255, 0, 255));
	printText(CAMERAMANAGER->getCameraDC(), to_string(_playerAttack).c_str(), "나눔스퀘어_ac Bold", textRect[1].left + 5, textRect[1].top + 5, 30, RGB(255, 255, 255), true, RGB(255, 0, 255));
	printText(CAMERAMANAGER->getCameraDC(), to_string(_Dev).c_str(), "나눔스퀘어_ac Bold", textRect[2].left + 5, textRect[2].top + 5, 30, RGB(255, 255, 255), true, RGB(255, 0, 255));
	printText(CAMERAMANAGER->getCameraDC(), to_string(_playerSpeed).c_str(), "나눔스퀘어_ac Bold", textRect[3].left + 5, textRect[3].top + 5, 30, RGB(255, 255, 255), true, RGB(255, 0, 255));

	// 커서랜더
	cusorRender();
}

void inven::cusorRender()
{
	m_cusor->render(v_invenLeftRect);
}

void inven::invenRectSet()
{
	//인벤 탑
	for (int i = 0; i < 5; i++)
	{
		invenTopRect[i] = RectMakeCenter((LEFTINVENX- 2) + (i * RECTRANGE), LEFTINVENY -3, 60, 60);
		v_invenLeftRect.push_back(invenTopRect[i]);
	}
	//인벤 탑
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			invenMidRect[(i*j) + j] = RectMakeCenter(LEFTINVENX + (j * RECTRANGE), LEFTINVENY +85 + (i * 70), 60, 60);
			v_invenLeftRect.push_back(invenMidRect[(i*j) + j]);
		}
	}
	// 아이템 돋보기 
	showItem = RectMakeCenter(LEFTINVENX, WINSIZEY - 200, 60, 60);
	v_invenLeftRect.push_back(showItem);

	// 무기
	for (int i = 0; i < 2; i++)
	{
		weaponeRect[i] = RectMakeCenter(WINSIZEX / 2 + 125 + (i * 175), LEFTINVENY + 18, 60, 60);
		v_invenRightRect.push_back(weaponeRect[i]);
	}

	// 장비
	for (int i = 0; i < 3; i++)
	{
		wearEquipment[i] = RectMakeCenter(WINSIZEX / 2 + 42, WINSIZEY / 2 - 75 + (i*RECTRANGE), 60, 60);
		v_invenRightRect.push_back(wearEquipment[i]);
	}

	// 플레이어 렉트
	playerView = RectMakeCenter(WINSIZEX / 2 + 218, WINSIZEY / 2 + 35,240, 270);
	v_invenRightRect.push_back(playerView);

	// 텍스트 렉트
	for (int i = 0; i < 4; i++)
	{
		textRect[i] = RectMakeCenter(WINSIZEX - 160, WINSIZEY / 2 - 82 + (i * 60), 70, 40);
		v_invenRightRect.push_back(textRect[i]);
	}

}

void inven::itemRectSet()
{
	v_weaponeItem.at(0).rc = weaponeRect[0];
	v_weaponeItem.at(1).rc = weaponeRect[1];

	for (int i = 0; i < v_invenItem.size(); i++)
	{
		v_invenItem.at(i).rc = v_invenLeftRect[i];
	}
	//v_invenItem.at(3).rc = v_invenLeftRect[1];


}
