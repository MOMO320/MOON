#include "stdafx.h"
#include "startMenuScene.h"

startMenuScene::startMenuScene()
	:m_menuCount(m_menuCount = 0)
{
	// 이미지
}

startMenuScene::~startMenuScene()
{
}

HRESULT startMenuScene::init()
{
	m_startMenuBubble[0] = IMAGEMANAGER->findImage("시작메뉴버블바탕");
	m_startMenuBubble[1] = IMAGEMANAGER->findImage("시작메뉴버블위");
	m_startMenuSideBar = IMAGEMANAGER->findImage("시작메뉴양문");
	m_gameLogo = IMAGEMANAGER->findImage("게임로고");
	m_menuChoiceUiL = IMAGEMANAGER->findImage("시작메뉴선택ui_L");
	m_menuChoiceUiR = IMAGEMANAGER->findImage("시작메뉴선택ui_R");

	// ====== [[ ANIMATION ]] ======== //
	m_bubble[0] = ANIMATIONMANAGER->findAnimation("bubbleAni1");
	m_bubble[1] = ANIMATIONMANAGER->findAnimation("bubbleAni2");

	m_bubble[0]->start();
	m_bubble[1]->start();

	return S_OK;
}

void startMenuScene::release()
{
}

void startMenuScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && m_menuCount < 2)
		m_menuCount++;

	if (KEYMANAGER->isOnceKeyDown(VK_UP) && m_menuCount > 0)
		m_menuCount--;

}

void startMenuScene::render()
{
	m_startMenuBubble[0]->aniRender(getMemDC(), 0, 0, m_bubble[0]);

	m_gameLogo->render(getMemDC(), (WINSIZEX - m_gameLogo->getWidth()) / 2, WINSIZEY / 2 - 280);

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
			printText(getMemDC(), m_menu[i].c_str(), "나눔스퀘어_ac Bold", WINSIZEX / 2 - 40, WINSIZEY / 2 + 50 + (i * 55), 35, RGB(255, 255, 255), true, RGB(255, 0, 255));
		else
			printText(getMemDC(), m_menu[i].c_str(), "나눔스퀘어_ac Bold", WINSIZEX / 2 - 20, WINSIZEY / 2 + 50 + (i * 55), 35, RGB(255, 255, 255), true, RGB(255, 0, 255));
	}
	choiceRender();

	m_startMenuBubble[1]->aniRender(getMemDC(), 0, 0, m_bubble[1]);

	m_startMenuSideBar->render(getMemDC(), 0, 0);

}

void startMenuScene::choiceRender()
{
	switch (m_menuCount)
	{
	case GAME:
		m_menuChoiceUiL->render(getMemDC(), WINSIZEX / 2 - 93, WINSIZEY / 2 + 50 + (m_menuCount * 55));
		m_menuChoiceUiR->render(getMemDC(), WINSIZEX / 2 + 75, WINSIZEY / 2 + 50 + (m_menuCount * 55));
		break;
	case MAPTOOL:
		m_menuChoiceUiL->render(getMemDC(), WINSIZEX / 2 - 73, WINSIZEY / 2 + 50 + (m_menuCount * 55));
		m_menuChoiceUiR->render(getMemDC(), WINSIZEX / 2 + 45, WINSIZEY / 2 + 50 + (m_menuCount * 55));
		break;
	case END:
		m_menuChoiceUiL->render(getMemDC(), WINSIZEX / 2 - 73, WINSIZEY / 2 + 50 + (m_menuCount * 55));
		m_menuChoiceUiR->render(getMemDC(), WINSIZEX / 2 + 45, WINSIZEY / 2 + 50 + (m_menuCount * 55));
		break;
	default:
		break;
	}
}

GAMEMENU startMenuScene::choiceMenu()
{
	switch (m_menuCount)
	{
	case GAME:	return GAME;
		break;

	case MAPTOOL: return MAPTOOL;
		break;
	case END: return END;
		break;
	default:
		break;
	}
	return ME_NULL;
}
