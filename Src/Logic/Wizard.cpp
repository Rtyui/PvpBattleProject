#include "Wizard.h"
#include "FrozenOrb.h"

Wizard::Wizard()
{
	hp = WIZARD_HP;
	maxHp = WIZARD_HP;
	mp = WIZARD_MP;
	moveSpeed = WIZARD_MOVESPEED;
	modifiedMoveSpeed = WIZARD_MOVESPEED;
	canMove = true;
	spells.push_back(new RangedAttackSpell());
	spells.push_back(new HealBomb());
	spells.push_back(new FrozenOrb());
}

Wizard::~Wizard()
{
	for (int i = 0; i < SPELL_NUMBER; i++)
		delete(spells.at(i));
}