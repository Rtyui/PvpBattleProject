#pragma once
#include <stdio.h>
#include <vector>
#include "Effect.h"


class SlowEffect : public Effect
{
public:
	SlowEffect();
	~SlowEffect();

	virtual void				Apply(CharacterRef character) override;
	virtual void				UnApply() override;
	virtual void				Update(float dtime) override;

	void						SetPercentage(float percentage);

private:

	float percentage;
};