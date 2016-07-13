#pragma once
#include <stdio.h>
#include "Spell.h"
#include "Object.h"

#define FROZEN_ORB_COOLDOWN				4
#define FROZEN_ORB_DAMAGE				300
#define FROZEN_ORB_STUN_DURATION		2.f
#define FROZEN_ORB_PROJECTILE_SPEED		350

class FrozenOrb : public Spell
{
public:
	FrozenOrb();
	~FrozenOrb();

	void Cast(ObjectRef user, ObjectRef enemy);
	void Apply(ObjectRef target);
private:

	int stun_duration;
	int damage;
};