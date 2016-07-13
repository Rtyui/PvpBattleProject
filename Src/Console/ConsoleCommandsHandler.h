#pragma once

#include "stdincl.h"
#include "TextComponent.h"

typedef void(*function)(const std::string&);

class ConsoleCommandsHandler
{

public:

	ConsoleCommandsHandler(void);
	~ConsoleCommandsHandler(void);

	void														CreateCommand(const std::string& commandName, function f);

	void														HandleCommand(const std::string& command, TextComponent* textComp);

	function													HasCommand(const std::string& commandName);

	void														PredictCommand(TextComponent* textComp);


private:

	std::vector<std::pair<std::string, function> >				m_commandsList;

};

