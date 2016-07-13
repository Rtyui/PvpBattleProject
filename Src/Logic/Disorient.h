#pragma once
#include <stdio.h>
#include "Spell.h"
#include "Object.h"

#define DISORIENT_COOLDOWN				4
#define DISORIENT_DAMAGE				150
#define DISORIENT_DURATION				2.5f
#define DISORIENT_AOE					100

class Disorient : public Spell
{
public:
	Disorient();
	~Disorient();

	void Cast(ObjectRef user, ObjectRef enemy);
	void Apply(ObjectRef target);
private:

	int duration;
	int damage;
	int aoe;
};