#include <stdio.h>
#include "Spell.h"

Spell::Spell()
{
	damage = 0;
	projectileSpeed = BASE_PROJECTILE_SPEED;
	slowPercentage = 0;
	r_cooldown = -42.f;
}

Spell::Spell(int damage) : damage(damage)
{
	projectileSpeed = BASE_PROJECTILE_SPEED;
	slowPercentage = 0;
}

Spell::Spell(int damage, int speed, int percent) : 
	damage(damage),
	projectileSpeed(speed),
	slowPercentage(percent) {}

Spell::~Spell() {}

void Spell::Cast(ObjectRef user, ObjectRef enemy)
{
}

bool Spell::CanCast()
{
	return r_cooldown <= 0;
}

void Spell::Apply(ObjectRef target)
{

}

void Spell::DecreaseCooldown(float value)
{
	if (r_cooldown > 0)
		r_cooldown -= value;
}
