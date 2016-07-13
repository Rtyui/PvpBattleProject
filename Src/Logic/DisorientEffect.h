#pragma once
#include <stdio.h>
#include <vector>
#include "Effect.h"


class DisorientEffect : public Effect
{
public:
	DisorientEffect();
	~DisorientEffect();

	virtual void				Apply(CharacterRef character) override;
	virtual void				UnApply() override;
	virtual void				Update(float dtime) override;


private:
};