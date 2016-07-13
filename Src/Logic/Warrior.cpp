#include "Warrior.h"
#include "Dash.h"
#include "Disorient.h"

Warrior::Warrior()
{
	hp = WARRIOR_HP;
	maxHp = WARRIOR_HP;
	mp = WARRIOR_MP;
	moveSpeed = WARRIOR_MOVESPEED;
	modifiedMoveSpeed = WARRIOR_MOVESPEED;
	canMove = true;

	spells.push_back(new WarriorMeleeAttackSpell());
	spells.push_back(new Dash());
	spells.push_back(new Disorient());
}

Warrior::~Warrior()
{
	for (int i = 0; i < SPELL_NUMBER; i++)
		delete(spells.at(i));
}