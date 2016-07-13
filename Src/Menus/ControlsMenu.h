#pragma once

#include "Component.h"
#include "stdincl.h"

class ControlsMenu : public Component
{
	REGISTER(ControlsMenu);

public:

	ControlsMenu(void);
	~ControlsMenu(void);

	virtual void			OnStart();

	virtual void			Update(float dtime) override;
	virtual void			PostUpdate(float dtime) override;

private:

};

