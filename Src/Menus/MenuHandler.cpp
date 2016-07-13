#include "MenuHandler.h"
#include "App.h"
#include "stdincl.h"
#include "Helpers.h"

MenuHandler* g_menuHandler;

const char* MenuHandler::m_menusFiles[] =
{
	"MainMenu.xml",
	"PlayMenu.xml",
	"MainGame.xml",
	"OptionsMenu.xml",
	"ControlsMenu.xml",
	"GamePausedMenu.xml"
};

MenuHandler::MenuHandler()
{
	g_menuHandler = this;
}

MenuHandler::~MenuHandler()
{
}

void MenuHandler::OnStart()
{
	for (uint i = 0; i < NUM_MENUS; ++i)
	{
		auto menuObjPtr = Object::CreateFromFile(m_menusFiles[i]);
		auto menuObjRef = menuObjPtr.get();

		g_scene->GetRoot()->InsertChild(std::move(menuObjPtr), 0);
		m_menuList.push_back(menuObjRef);
		menuObjRef->Disable();
	}

	m_currentMenu = FIRST_MENU;

	m_menuList[m_currentMenu]->Enable();
}

void MenuHandler::SwitchMenu(uint menu)
{
	m_menuList[m_currentMenu]->Disable();
	m_menuList[menu]->Enable();
	m_menuList[menu]->SetJustEnabled();

	m_currentMenu = menu;
}

uint MenuHandler::GetIndex(const std::string &menu)
{
	if (IsEqual(menu.c_str(), "MainMenu"))
	{
		return MAIN_MENU;
	}
	else if (IsEqual(menu.c_str(), "GameMenu"))
	{
		return MAIN_GAME;
	}
	else if (IsEqual(menu.c_str(), "OptionsMenu"))
	{
		return OPTION_MENU;
	}
	else if (IsEqual(menu.c_str(), "ControlsMenu"))
	{
		return CONTROLS_MENU;
	}
	else if (IsEqual(menu.c_str(), "PlayMenu"))
	{
		return PLAY_MENU;
	}

	assert(nullptr);
	return 100;
}

ObjectRef MenuHandler::GetMenuObject(uint menu)
{
	return m_menuList[menu];
}

ObjectRef MenuHandler::GetCurrentMenu()
{
	return m_menuList[m_currentMenu];
}