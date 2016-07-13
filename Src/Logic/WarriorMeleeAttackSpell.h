#include <stdio.h>
#include "Spell.h"

class WarriorMeleeAttackSpell : public Spell 
{
public:
	WarriorMeleeAttackSpell();
	~WarriorMeleeAttackSpell();

	void				Cast(ObjectRef user, ObjectRef enemy) override;
	void				Apply(ObjectRef target) override;
private:
	/* Area of effect of this spell */
	int aoe;
};