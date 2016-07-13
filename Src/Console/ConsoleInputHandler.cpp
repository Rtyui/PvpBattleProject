#include "ConsoleInputHandler.h"
#include "App.h"
#include "Helpers.h"
#include "stdincl.h"
#include "Input.h"
#include "TextComponent.h"
#include "STAT.h"

ConsoleInputHandler::ConsoleInputHandler()
{
}

ConsoleInputHandler::~ConsoleInputHandler()
{
}

void ConsoleInputHandler::UpdateCommandLine(uint key, ObjectRef commandLine)
{
	auto textComp = commandLine->GetComponent<TextComponent>();
	assert(commandLine);

	std::string currentCommand;

	currentCommand.append(textComp->GetText());

	if (g_input->IsPressed(KEY_SHIFT))
	{
		currentCommand.append(g_STAT->TranslateShifted(key));
	}
	else
	{
		currentCommand.append(g_STAT->Translate(key));
		
	}

	textComp->SetText(currentCommand);
}