#pragma once
#include <stdio.h>
#include "Spell.h"
#include "Object.h"


#define BLINK_COOLDOWN				3
#define BLINK_MOVE_DISTANCE			200.f

class Blink : public Spell
{
public:
	Blink();
	~Blink();

	void Cast(ObjectRef user, ObjectRef enemy);
	void Apply(ObjectRef target);
private:

	float moveDistance;
};