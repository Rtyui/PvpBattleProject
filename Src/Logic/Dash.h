#pragma once
#include <stdio.h>
#include "Spell.h"
#include "Object.h"


#define DASH_COOLDOWN				4
#define DASH_DAMAGE					150
#define DASH_DURATION				1.f
#define DASH_SPEED					350.f
#define STUN_DURATION				1.f

class Dash : public Spell
{
public:
	Dash();
	~Dash();

	void Cast(ObjectRef user, ObjectRef enemy);
	void Apply(ObjectRef target);

private:

	int duration;
	int stun_duration;
	float speed;
};