#pragma once
#include <stdio.h>
#include <vector>
#include "Character.h"

class Effect;
typedef Effect* EffectRef;



class Effect
{
public:
	Effect();
	~Effect();

	virtual void				Apply(CharacterRef character);
	virtual void				UnApply();
	virtual void				Update(float dtime);

	void						SetDuration(float duration);

protected:

	CharacterRef character;

	float duration;
};