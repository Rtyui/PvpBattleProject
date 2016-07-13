#include "ConsoleCommandsHandler.h"
#include "App.h"
#include "Helpers.h"
#include "stdincl.h"
#include "Input.h"
#include "TextComponent.h"

ConsoleCommandsHandler::ConsoleCommandsHandler()
{
}

ConsoleCommandsHandler::~ConsoleCommandsHandler()
{
}

void ConsoleCommandsHandler::CreateCommand(const std::string& commandName, function f)
{
	m_commandsList.push_back(std::make_pair(commandName, f));
}

function ConsoleCommandsHandler::HasCommand(const std::string& commandName)
{
	for (uint i = 0; i < m_commandsList.size(); ++i)
	{
		if (IsEqual(m_commandsList[i].first.c_str(), commandName.c_str()))
		{
			return m_commandsList[i].second;
		}
	}
	return nullptr;
}	

void ConsoleCommandsHandler::HandleCommand(const std::string& command, TextComponent* textComp)
{
	if (IsEqual(command.c_str(), ""))
	{
		textComp->SetText("Nothing is not a command!");
		return;
	}

	char* myString = new char[command.size()];
	char* parameter;
	strcpy_s(myString, _TRUNCATE, command.c_str());
	char* commandName = strtok_s(myString, " ", &parameter);

	if (auto funct = HasCommand(commandName))
	{
		textComp->SetText(command);
		funct(parameter);
		return;
	}
	else if (IsEqual(command.c_str(), "help"))
	{
		textComp->SetText(command);
		for (uint i = 0; i < m_commandsList.size(); ++i)
		{
			g_app->m_console->WriteMessage(m_commandsList[i].first);
		}
		return;
	}
	textComp->SetText(std::string(commandName).append(" - command not found "));
}

void ConsoleCommandsHandler::PredictCommand(TextComponent* textComp)
{
	for (uint i = 0; i < m_commandsList.size(); ++i)
	{
		if (StringStartsWith(textComp->GetText().c_str(), m_commandsList[i].first.c_str()))
		{
			textComp->SetText(m_commandsList[i].first);
			return;
		}
	}
}
