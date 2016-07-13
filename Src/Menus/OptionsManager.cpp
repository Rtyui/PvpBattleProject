#include "OptionsManager.h"
#include "App.h"
#include "stdincl.h"
#include "Helpers.h"

OptionsManager* g_optionsManager;

OptionsManager::OptionsManager()
{
	g_optionsManager = this;
}

OptionsManager::~OptionsManager()
{
}


void OptionsManager::Load()
{

	m_firstPlayerControls = std::vector<uint>(NUM_ACTIONS, 100);
	m_secondPlayerControls = std::vector<uint>(NUM_ACTIONS, 100);


	TiXmlDocument doc;
	std::string file;

	file.append(XML_FOLDER);
	file.append("Options.xml");

	int ret = doc.LoadFile(file.c_str());
	assert(ret != 0);

	TiXmlElement* optionsElement = doc.FirstChildElement();
	for (auto a = optionsElement->FirstAttribute(); a; a = a->Next())
	{
		if (IsEqual(a->Name(), "fullscreen"))
		{
			m_fullscreen = a->BoolValue();
		}
		else if (IsEqual(a->Name(), "first_player_left"))
		{
			m_firstPlayerControls[MOVE_LEFT] = a->UnsignedValue();
		}
		else if (IsEqual(a->Name(), "first_player_right"))
		{
			m_firstPlayerControls[MOVE_RIGHT] = a->UnsignedValue();
		}
		else if (IsEqual(a->Name(), "first_player_jump"))
		{
			m_firstPlayerControls[JUMP] = a->UnsignedValue();
		}
		else if (IsEqual(a->Name(), "first_player_spell1"))
		{
			m_firstPlayerControls[SPELL1] = a->UnsignedValue();
		}
		else if (IsEqual(a->Name(), "first_player_spell2"))
		{
			m_firstPlayerControls[SPELL2] = a->UnsignedValue();
		}
		else if (IsEqual(a->Name(), "first_player_spell3"))
		{
			m_firstPlayerControls[SPELL3] = a->UnsignedValue();
		}
		else if (IsEqual(a->Name(), "second_player_left"))
		{
			m_secondPlayerControls[MOVE_LEFT] = a->UnsignedValue();
		}
		else if (IsEqual(a->Name(), "second_player_right"))
		{
			m_secondPlayerControls[MOVE_RIGHT] = a->UnsignedValue();
		}
		else if (IsEqual(a->Name(), "second_player_jump"))
		{
			m_secondPlayerControls[JUMP] = a->UnsignedValue();
		}
		else if (IsEqual(a->Name(), "second_player_spell1"))
		{
			m_secondPlayerControls[SPELL1] = a->UnsignedValue();
		}
		else if (IsEqual(a->Name(), "second_player_spell2"))
		{
			m_secondPlayerControls[SPELL2] = a->UnsignedValue();
		}
		else if (IsEqual(a->Name(), "second_player_spell3"))
		{
			m_secondPlayerControls[SPELL3] = a->UnsignedValue();
		}
	}
}

void OptionsManager::Unload()
{
	TiXmlDocument doc;
	std::string file;

	file.append(XML_FOLDER);
	file.append("Options.xml");

	int ret = doc.LoadFile(file.c_str());
	assert(ret != 0);

	TiXmlElement* optionsElement = doc.FirstChildElement();
	for (auto a = optionsElement->FirstAttribute(); a; a = a->Next())
	{
		if (IsEqual(a->Name(), "fullscreen"))
		{
			a->SetValue(std::to_string(m_fullscreen).c_str());
		}
		else if (IsEqual(a->Name(), "first_player_left"))
		{
			a->SetValue(std::to_string(m_firstPlayerControls[MOVE_LEFT]).c_str());
		}
		else if (IsEqual(a->Name(), "first_player_right"))
		{
			a->SetValue(std::to_string(m_firstPlayerControls[MOVE_RIGHT]).c_str());
		}
		else if (IsEqual(a->Name(), "first_player_jump"))
		{
			a->SetValue(std::to_string(m_firstPlayerControls[JUMP]).c_str());
		}
		else if (IsEqual(a->Name(), "first_player_spell1"))
		{
			a->SetValue(std::to_string(m_firstPlayerControls[SPELL1]).c_str());
		}
		else if (IsEqual(a->Name(), "first_player_spell2"))
		{
			a->SetValue(std::to_string(m_firstPlayerControls[SPELL2]).c_str());
		}
		else if (IsEqual(a->Name(), "first_player_spell3"))
		{
			a->SetValue(std::to_string(m_firstPlayerControls[SPELL3]).c_str());
		}
		else if (IsEqual(a->Name(), "second_player_left"))
		{
			a->SetValue(std::to_string(m_secondPlayerControls[MOVE_LEFT]).c_str());
		}
		else if (IsEqual(a->Name(), "second_player_right"))
		{
			a->SetValue(std::to_string(m_secondPlayerControls[MOVE_RIGHT]).c_str());
		}
		else if (IsEqual(a->Name(), "second_player_jump"))
		{
			a->SetValue(std::to_string(m_secondPlayerControls[JUMP]).c_str());
		}
		else if (IsEqual(a->Name(), "second_player_spell1"))
		{
			a->SetValue(std::to_string(m_secondPlayerControls[SPELL1]).c_str());
		}
		else if (IsEqual(a->Name(), "second_player_spell2"))
		{
			a->SetValue(std::to_string(m_secondPlayerControls[SPELL2]).c_str());
		}
		else if (IsEqual(a->Name(), "second_player_spell3"))
		{
			a->SetValue(std::to_string(m_secondPlayerControls[SPELL3]).c_str());
		}
	}
	doc.SaveFile();
}

void OptionsManager::RefreshWindow()
{
	if (m_fullscreen)
	{
		g_app->m_window.create(sf::VideoMode(g_app->APP_RESOLUTION_WIDTH, g_app->APP_RESOLUTION_HEIGHT), "Game", sf::Style::Fullscreen);
	}
	else
	{
		g_app->m_window.create(sf::VideoMode(g_app->APP_RESOLUTION_WIDTH, g_app->APP_RESOLUTION_HEIGHT), "Game");
	}
	g_app->m_window.setFramerateLimit(60);
}

uint OptionsManager::GetKeyForAction(uint action, uint controls)
{
	if (controls == 0)
	{
		return m_firstPlayerControls[action];
	}
	else
	{
		return m_secondPlayerControls[action];
	}
}



