#pragma once

#include "Component.h"
#include "stdincl.h"

class OptionsMenu : public Component
{
	REGISTER(OptionsMenu);

public:

	OptionsMenu(void);
	~OptionsMenu(void);

	virtual void			OnStart();

	virtual void			Update(float dtime) override;
	virtual void			PostUpdate(float dtime) override;

	void					Apply();
	void					Cancel();
	void					CheckIfApplied();
	void					CheckIfCanceled();

	void					Preset();


private:

};

