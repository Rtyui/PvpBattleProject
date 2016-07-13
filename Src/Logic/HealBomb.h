#pragma once
#include <stdio.h>
#include "Spell.h"

#define HEALBOMB_COOLDOWN				5
#define HEALBOMB_DAMAGE					0
#define HEALBOMB_SLOW_PERCENTAGE		0
#define HEALBOMB_HEAL_PERCENTAGE		20
#define HEALBOMB_PROJECTILE_SPEED		250

class HealBomb : public Spell
{
public:
	HealBomb();
	~HealBomb();

	void Cast(ObjectRef user, ObjectRef enemy);
	void Apply(ObjectRef target);
private:

	int heal_percentage;
};