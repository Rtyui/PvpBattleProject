#include "App.h"
#include "DotEffect.h"

DotEffect::DotEffect()
{
}

DotEffect::~DotEffect()
{
}

void DotEffect::Apply(CharacterRef character)
{
	Effect::Apply(character);
}

void DotEffect::UnApply()
{
	Effect::UnApply();
}

void DotEffect::Update(float dtime)
{
	Effect::Update(dtime);
	timePassed += dtime;

	if (timePassed >= 1.f)
	{
		timePassed -= 1.f;
		character->TakeDamage(damage);
	}
}

void DotEffect::SetDamage(float damage)
{
	this->damage = damage;
}