#include "App.h"
#include "StunEffect.h"

StunEffect::StunEffect()
{
}

StunEffect::~StunEffect()
{
}

void StunEffect::Apply(CharacterRef character)
{
	Effect::Apply(character);
	character->SetCanMove(false);
}

void StunEffect::UnApply()
{
	Effect::UnApply();
	character->SetCanMove(true);
}

void StunEffect::Update(float dtime)
{
	Effect::Update(dtime);
}

void StunEffect::SetPercentage(float percentage)
{
	this->percentage = percentage;
}