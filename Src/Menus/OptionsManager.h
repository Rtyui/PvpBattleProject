#pragma once

#include "stdincl.h"

class OptionsManager
{
public:

	enum ACTIONS {MOVE_LEFT, MOVE_RIGHT, JUMP, SPELL1, SPELL2, SPELL3, NUM_ACTIONS};

	OptionsManager(void);
	~OptionsManager(void);

	void						Load();
	void						Unload();
	void						RefreshWindow();

	uint						GetKeyForAction(uint action, uint controls);

	bool						m_fullscreen;

private:

	std::vector<uint>			m_firstPlayerControls;
	std::vector<uint>			m_secondPlayerControls;

};

extern OptionsManager* g_optionsManager;