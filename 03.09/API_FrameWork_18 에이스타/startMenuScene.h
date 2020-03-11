#pragma once
#include "gameNode.h"
#include "gameTypes.h"

class startMenuScene
	:public gameNode
{
public:
	startMenuScene();
	~startMenuScene();

	HRESULT init();
	void release();
	void update();
	void render();
	void choiceRender();
	GAMEMENU choiceMenu(); // mainGame�� �Ѱ��ִ� ��Ȱ
	void setChoiceMenu(int _menuCount) { m_menuCount = _menuCount; }

private:
	image* m_startMenuBubble[2];
	image* m_startMenuSideBar;
	image* m_gameLogo;
	image* m_menuChoiceUiL;
	image* m_menuChoiceUiR;

	animation* m_bubble[2];

	std::string m_menu[3] = { "�����ϱ�" , "����" , "����" };

	int m_menuCount;

};


