#include "GamePausedMenu.h"
#include "App.h"
#include "stdincl.h"

REGISTERIMPL(GamePausedMenu);

GamePausedMenu::GamePausedMenu()
{
}

GamePausedMenu::~GamePausedMenu()
{
}


void GamePausedMenu::Update(float dtime)
{
	if (g_input->WasPressedThisTurn(KEY_P))
	{
		g_menuHandler->SwitchMenu(MAIN_GAME);
	}
}

void GamePausedMenu::PostUpdate(float dtime)
{
}
