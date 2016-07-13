#pragma once
#include <stdio.h>
#include <vector>
#include "Effect.h"


class DotEffect : public Effect
{
public:
	DotEffect();
	~DotEffect();

	virtual void				Apply(CharacterRef character) override;
	virtual void				UnApply() override;
	virtual void				Update(float dtime) override;

	void						SetDamage(float damage);

private:

	float damage;
	float timePassed;
};