#pragma once
#include <stdio.h>
#include <vector>
#include "Effect.h"


class StunEffect : public Effect
{
public:
	StunEffect();
	~StunEffect();

	virtual void				Apply(CharacterRef character) override;
	virtual void				UnApply() override;
	virtual void				Update(float dtime) override;

	void						SetPercentage(float percentage);

private:

	float percentage;
};