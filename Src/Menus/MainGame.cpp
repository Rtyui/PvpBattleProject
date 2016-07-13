#include "MainGame.h"
#include "App.h"
#include "stdincl.h"
#include "PlayerMovement.h"
#include "PlayerHpBar.h"
#include "CharacterComponent.h"
#include "Helpers.h"

REGISTERIMPL(MainGame);

MainGame::MainGame() :
m_winTextDuration(0.f)
{
}

MainGame::~MainGame()
{
}

void MainGame::OnAddToObject()
{
}

void MainGame::OnActivate()
{
	
}

void MainGame::Update(float dtime)
{
	if (g_input->WasPressedThisTurn(KEY_P))
	{
		g_menuHandler->SwitchMenu(GAME_PAUSED_MENU);
	}

	if (m_battleEndedAnnounced)
	{
		m_winTextDuration -= dtime;
		if (m_winTextDuration <= 0.f)
		{
			m_battleEndedAnnounced = false;
			m_object->RemoveChild("WinText");
			g_menuHandler->SwitchMenu(MAIN_MENU);
		}
	}
}

void MainGame::PostUpdate(float dtime)
{
}

bool MainGame::BattleEndedAnnounced()
{
	return m_battleEndedAnnounced;
}


void MainGame::AnnounceFinish(const std::string& which)
{
	m_battleEndedAnnounced = true;

	m_winTextDuration = WIN_TEXT_DURATION;

	auto winText = Object::Create();
	winText->SetName("WinText");
	winText->SetPos(Vector2f(600, 300));
	auto winTextComp = winText->AddComponent<TextComponent>();
	winTextComp->SetColor(sf::Color::Green);
	winTextComp->SetFont("bellota.otf");
	winTextComp->SetFontSize(100);

	if (IsEqual(which.c_str(), "LeftHpBar"))
	{
		winTextComp->SetText("Player2 WINS!");
	}
	else
	{
		winTextComp->SetText("Player1 WINS!");
	}

	m_object->AddChild(std::move(winText));
}

