#pragma once

#include "Component.h"
#include "stdincl.h"

class GamePausedMenu : public Component
{
	REGISTER(GamePausedMenu);

public:

	GamePausedMenu(void);
	~GamePausedMenu(void);

	virtual void			Update(float dtime) override;
	virtual void			PostUpdate(float dtime) override;


private:

};

