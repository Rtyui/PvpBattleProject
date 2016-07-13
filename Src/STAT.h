#pragma once
#include "stdincl.h"

class STAT
{
public:
	STAT();
	~STAT();

	void										ConstructKeyMap();
	std::string									Translate(uint key);
	std::string									TranslateShifted(uint key);

private:
	std::vector<std::pair<uint, std::string> >	m_keyMap;
	std::vector<std::pair<uint, std::string> >	m_keyMapShift;
};

extern STAT* g_STAT;