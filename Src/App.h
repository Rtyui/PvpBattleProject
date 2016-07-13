#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "MenuHandler.h"
#include "Input.h"
#include "ConsoleComponent.h"
#include "OptionsManager.h"
#include "STAT.h"

class App
{
public:
	App();
	~App();

	void				Init();
	void				Draw();
	void				Run();

	int					APP_RESOLUTION_WIDTH;
	int					APP_RESOLUTION_HEIGHT;

	sf::RenderWindow	m_window;
	ConsoleComponent*	m_console;

	ObjectRef			m_fpsObject;

private:

	void				AddConsole();

	Input				m_input;
	MenuHandler			m_menuHandler;
	Scene				m_scene;
	OptionsManager		m_optionsManager;
	STAT				m_STAT;

	float				m_timeAccumulator;

	void				Update(float dtime);
	void				SetFpsObject();

};

extern App* g_app;
