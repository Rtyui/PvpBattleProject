#include "Disorient.h"
#include "stdincl.h"
#include "Object.h"
#include "CharacterComponent.h"
#include "PlayerMovement.h"
#include "App.h"
#include "DisorientEffect.h"

Disorient::Disorient()
{
	Spell::Spell();
	type = PROJECTILE_APPLY_ON_CHARACTER;

	damage = DISORIENT_DAMAGE;
	cooldown = DISORIENT_COOLDOWN;
	duration = DISORIENT_DURATION;
	aoe = DISORIENT_AOE;
}

Disorient::~Disorient() 
{
}

void Disorient::Cast(ObjectRef user, ObjectRef enemy)
{
	r_cooldown = cooldown;

	Vector2f userPos = user->GetPos();
	Vector2f enemyPos = enemy->GetPos();

	double firstDistance = sqrt(pow((userPos.x - enemyPos.x), 2)
		+ pow((userPos.y - enemyPos.y), 2));

	if (firstDistance < aoe)
	{
		Apply(enemy);
	}
}

void Disorient::Apply(ObjectRef target)
{
	auto characterComp = target->GetComponent<CharacterComponent>();

	if (!characterComp)
		return;

	auto character = characterComp->GetCharacter();

	character->TakeDamage(damage);

	/* TODO */
	EffectRef dEffect = new DisorientEffect();
	dEffect->SetDuration(duration);
	dEffect->Apply(character);
}