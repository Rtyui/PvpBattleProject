#include "Assassin.h"
#include "Daggerstorm.h"
#include "Blink.h"

Assassin::Assassin()
{
	hp = ASSASSIN_HP;
	maxHp = ASSASSIN_HP;
	mp = ASSASSIN_MP;
	moveSpeed = ASSASSIN_MOVESPEED;
	modifiedMoveSpeed = ASSASSIN_MOVESPEED;
	canMove = true;

	spells.push_back(new AssassinMeleeAttackSpell());
	spells.push_back(new Daggerstorm());
	spells.push_back(new Blink());
}

Assassin::~Assassin()
{
	for (int i = 0; i < SPELL_NUMBER; i++)
		delete(spells.at(i));
}