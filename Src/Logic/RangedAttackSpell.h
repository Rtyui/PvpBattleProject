#pragma once
#include <stdio.h>
#include "Spell.h"

class RangedAttackSpell : public Spell
{
public:
	RangedAttackSpell();
	~RangedAttackSpell();

	void				Cast(ObjectRef user, ObjectRef enemy) override;
	void				Apply(ObjectRef target) override;
private:
};