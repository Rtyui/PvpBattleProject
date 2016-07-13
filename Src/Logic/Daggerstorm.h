#pragma once
#include <stdio.h>
#include "Spell.h"
#include "Object.h"


#define DAGGERSTORM_COOLDOWN				3
#define DAGGERSTORM_DAMAGE					0
#define DAGGERSTORM_DAMAGE_OVER_TIME		40
#define DAGGERSTORM_SLOW_PERCENTAGE			15
#define DAGGERSTORM_PROJECTILE_SPEED		200
#define DAGGERSTORM_DURATION				3

class Daggerstorm : public Spell
{
public:
	Daggerstorm();
	~Daggerstorm();

	void Cast(ObjectRef user, ObjectRef enemy);
	void Apply(ObjectRef target);
private:

	int damageOverTime;
	int duration;
	std::vector<Vector2f> directions;
};