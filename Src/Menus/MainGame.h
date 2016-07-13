#pragma once

#include "Component.h"
#include "stdincl.h"

#define WIN_TEXT_DURATION 4.f

class MainGame : public Component
{
	REGISTER(MainGame);

public:

	MainGame(void);
	~MainGame(void);

	virtual void			OnAddToObject() override;
	virtual void			OnActivate() override;

	virtual void			Update(float dtime) override;
	virtual void			PostUpdate(float dtime) override;

	bool					BattleEndedAnnounced();

	void					AnnounceFinish(const std::string& which);

private:

	bool					m_battleEndedAnnounced;
	float					m_winTextDuration;
};

