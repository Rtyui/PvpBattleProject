#pragma once

#include "stdincl.h"
#include "Component.h"

class ConsoleInputHandler
{

public:

	ConsoleInputHandler(void);
	~ConsoleInputHandler(void);

	void										UpdateCommandLine(uint key, ObjectRef commandLine);

private:

	std::vector<std::pair<uint, std::string> >	m_keyMap;
	std::vector<std::pair<uint, std::string> >	m_keyMapShift;
	

};

