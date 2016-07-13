#include "STAT.h"

STAT* g_STAT;

STAT::STAT()
{
	g_STAT = this;
}

STAT::~STAT()
{
}

void STAT::ConstructKeyMap()
{
	m_keyMap.push_back(std::make_pair(sf::Keyboard::Dash, "-"));
	m_keyMap.push_back(std::make_pair(sf::Keyboard::Space, " "));

	m_keyMapShift.push_back(std::make_pair(sf::Keyboard::Dash, "_"));

	for (uint i = sf::Keyboard::Num0; i <= sf::Keyboard::Num9; ++i)
	{
		std::string strKey;
		strKey = char(i + 22);
		m_keyMap.push_back(std::make_pair(i, strKey));
	}

	for (uint i = sf::Keyboard::A; i <= sf::Keyboard::Z; ++i)
	{
		std::string strKey;
		strKey = char(i + 97);
		m_keyMap.push_back(std::make_pair(i, strKey));
		strKey = char(i + 65);
		m_keyMapShift.push_back(std::make_pair(i, strKey));
	}
}

std::string STAT::Translate(uint key)
{
	for (uint i = 0; i < m_keyMap.size(); ++i)
	{
		if (m_keyMap[i].first == key)
		{
			return m_keyMap[i].second;
		}
	}
	return "";
}

std::string STAT::TranslateShifted(uint key)
{
	for (uint i = 0; i < m_keyMapShift.size(); ++i)
	{
		if (m_keyMapShift[i].first == key)
		{
			return m_keyMapShift[i].second;
		}
	}
	return "";
}