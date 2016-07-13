#pragma once
#include <stdio.h>
#include <vector>
#include "Spell.h"

class Character;
typedef Character* CharacterRef;

class Effect;
typedef Effect* EffectRef;

#define BASE_MOVESPEED								50
#define SPELL_NUMBER								3

#define WARRIOR_HP									2400
#define WARRIOR_MP									800
#define WARRIOR_MOVESPEED							120

#define WIZARD_HP									1200
#define WIZARD_MP									1800
#define WIZARD_MOVESPEED							150

#define ASSASSIN_HP									1400
#define ASSASSIN_MP									800
#define ASSASSIN_MOVESPEED							135



class Character
{
public:
	Character();
	~Character();

	virtual SpellRef				GetSpellByIndex(int index);

	int								GetSpellCount();
	int								GetHp();
	int								GetMaxHp();
	float							GetModifiedMoveSpeed();
	float							GetMoveSpeed();
	bool							CanMove();
	bool							ControlsInverted();

	void							SetMoveSpeed(float newMoveSpeed);
	void							SetCanMove(bool value);
	void							SetControlsInverted(bool value);

	void							TakeDamage(int damage);
	void							HealPercent(int percentage);

	void							AddEffect(EffectRef effect);
	void							RemoveEffect(EffectRef effect);
	void							UpdateEffects(float dtime);


protected:
	/* Current health points of this character*/
	int hp;

	/* Maximum health points of this character*/
	int maxHp;

	/* Mana points of this character */
	int mp;

	/* Movespeed of this character */
	float moveSpeed;

	bool canMove;

	bool controlsInverted;

	float modifiedMoveSpeed;

	/* List of spells for this character 
	*  First spell is always its basic attack
	*/
	std::vector<SpellRef> spells;
	std::vector<EffectRef>	activeEffects;
};