#pragma once
#include "stdincl.h"
#include "Object.h"

class Spell;
typedef Spell* SpellRef;

#define BASE_PROJECTILE_SPEED					200

#define RANGED_ATTACK_DAMAGE					300
#define RANGED_ATTACK_COOLDOWN					3
#define RANGED_ATTACK_SLOW_PERCENTAGE			0

#define WARRIOR_MELEE_ATTACK_AOE				150
#define WARRIOR_MELEE_ATTACK_DAMAGE				150
#define WARRIOR_MELEE_SLOW_PERCENTAGE			0
#define WARRIOR_MELEE_ATTACK_COOLDOWN			3

#define ASSASSIN_MELEE_ATTACK_AOE				150
#define ASSASSIN_MELEE_ATTACK_DAMAGE			100
#define ASSASSIN_MELEE_SLOW_PERCENTAGE			15
#define ASSASSIN_MELEE_ATTACK_COOLDOWN			1
#define ASSASSIN_MELEE_SLOW_DURATION			3

enum STYPE {
	PROJECTILE_APPLY_ON_CHARACTER,
	PROJECTILE_APPLY_ON_ENVIROMENT,
	MELEE
};

class Spell
{
public:
	Spell();
	Spell(int damage);
	Spell(int damage, int percent);
	Spell(int damage, int speed, int percent);
	~Spell();

	virtual void				Cast(ObjectRef user, ObjectRef enemy);
	virtual void				Apply(ObjectRef target);

	bool						CanCast();
	void						DecreaseCooldown(float value);

protected:
	/* Type of spell */
	STYPE type;

	/* Damage this spell inflicts upon enemy */
	int damage;

	/* Projectile speed */
	int projectileSpeed;

	/* Slow percentage applied on enemy */
	int slowPercentage;

	/* Time between repeated uses of this spell */
	int cooldown;

	float r_cooldown;
};