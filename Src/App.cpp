#include "App.h"
#include "tinyxml.h"
#include "TextComponent.h"
#include "Helpers.h"
#include "RNG.h"


App* g_app = new App();

void Exit(const std::string& params)
{
	g_app->m_window.close();
}

void ShowFPS(const std::string& params)
{
	if (IsEqual(params.c_str(), "0"))
	{
		g_app->m_fpsObject->Disable();
	}
	else if (IsEqual(params.c_str(), ""))
	{
		return;
	}
	else
	{
		g_app->m_fpsObject->Enable();
	}
}

void Fullscreen(const std::string& params)
{
	if (IsEqual(params.c_str(), "0"))
	{
		if (g_optionsManager->m_fullscreen)
		{
			g_app->m_window.create(sf::VideoMode(g_app->APP_RESOLUTION_WIDTH, g_app->APP_RESOLUTION_HEIGHT), "Game");
			g_app->m_window.setFramerateLimit(60);
			g_optionsManager->m_fullscreen = false;
			return;
		}
		return;
	}
	else if (IsEqual(params.c_str(), ""))
	{
		return;
	}
	if (!g_optionsManager->m_fullscreen)
	{
		g_app->m_window.create(sf::VideoMode(g_app->APP_RESOLUTION_WIDTH, g_app->APP_RESOLUTION_HEIGHT), "Game", sf::Style::Fullscreen);
		g_app->m_window.setFramerateLimit(60);
		g_optionsManager->m_fullscreen = true;
	}
}

void WindowSize(const std::string& params)
{
	g_app->m_console->WriteMessage("width - height: " + std::to_string(g_app->APP_RESOLUTION_WIDTH) + " - " + std::to_string(g_app->APP_RESOLUTION_HEIGHT));
}

void ShowKids(ObjectRef o)
{
	if (o->GetChildrenCount() == 0) return;
	std::string line;
	line.append(o->GetName());
	line.append(" " + std::to_string(o->IsEnabled()));
	line.append(" (");
	for (uint i = 0; i < o->GetChildrenCount(); ++i)
	{
		line.append(o->GetChild(i)->GetName());
		line.append(" " + std::to_string(o->GetChild(i)->IsEnabled()));
		ShowKids(o->GetChild(i));
		if (i != o->GetChildrenCount() - 1)
		{
			line.append(", ");
		}
	}
	line.append(" )");
	g_app->m_console->WriteMessage(line);
}

void ShowTree(const std::string& params)
{
	ShowKids(g_scene->GetRoot());
}

App::App() :
m_timeAccumulator(0)
{
}

App::~App()
{
}

void App::Init()
{
	g_STAT->ConstructKeyMap();
	APP_RESOLUTION_WIDTH = 1280;
	APP_RESOLUTION_HEIGHT = 720;

	RNG::InitiateSeed();
	AddConsole();
	SetFpsObject();
	g_menuHandler->OnStart();

	g_optionsManager->Load();
	g_optionsManager->RefreshWindow();

	m_console->CreateCommand("exit", &Exit);
	m_console->CreateCommand("show_fps", &ShowFPS);
	m_console->CreateCommand("fullscreen", &Fullscreen);
	m_console->CreateCommand("get_window_size", &WindowSize);
	m_console->CreateCommand("get_tree", &ShowTree);
}

void App::Draw()
{
}

void App::Run()
{
	sf::Clock clock;

	Init();

	auto root = g_scene->GetRoot();
	root->OnStart();

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			g_input->HandleEvent(event);
		}

		sf::Time dtime = clock.getElapsedTime();
		m_window.clear();

		root->Update(dtime.asSeconds());
		root->PostUpdate(dtime.asSeconds());
		Update(dtime.asSeconds());
		g_input->Update();

		root->Draw();
		clock.restart();

		m_window.display();
	}
	g_optionsManager->Unload();
}

void App::Update(float dtime)
{
	m_timeAccumulator += dtime;
	if (m_timeAccumulator >= 1.f)
	{
		m_timeAccumulator = 0.f;
		auto fpsTextComp = m_fpsObject->GetComponent<TextComponent>();
		fpsTextComp->SetText(std::to_string((int)(1.f / dtime)));
	}
	
	if (g_input->WasPressedThisTurn(KEY_CONSOLE))
	{
		if (m_console->m_object->IsEnabled())
		{
			m_console->m_object->Disable();
		}
		else
		{
			m_console->m_object->Enable();
		}
	}
}

void App::SetFpsObject()
{
	auto fpsObject = Object::CreateFromFile("FpsObject.xml");

	fpsObject->SetPos(Vector2f(APP_RESOLUTION_WIDTH - 50.f, 0.f));
	fpsObject->Disable();
	m_fpsObject = fpsObject.get();
	g_scene->GetRoot()->AddChild(std::move(fpsObject));
}

void App::AddConsole()
{
	auto consolePtr = Object::CreateFromFile("Console.xml");
	m_console = consolePtr->GetComponent<ConsoleComponent>();
	g_scene->GetRoot()->AddChild(std::move(consolePtr));
}