#include <stdio.h>
#include "Spell.h"

class AssassinMeleeAttackSpell : public Spell
{
public:
	AssassinMeleeAttackSpell();
	~AssassinMeleeAttackSpell();

	void				Cast(ObjectRef user, ObjectRef enemy) override;
	void				Apply(ObjectRef target) override;

private:
	/* Area of effect of this spell */
	int aoe;
	int duration;
};