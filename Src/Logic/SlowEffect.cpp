#include "App.h"
#include "SlowEffect.h"

SlowEffect::SlowEffect()
{
}

SlowEffect::~SlowEffect()
{
}

void SlowEffect::Apply(CharacterRef character)
{
	Effect::Apply(character);
	float new_ms = character->GetModifiedMoveSpeed() - character->GetMoveSpeed() * percentage;
	character->SetMoveSpeed(new_ms);
}

void SlowEffect::UnApply()
{
	Effect::UnApply();
	float new_ms = character->GetModifiedMoveSpeed() + character->GetMoveSpeed() * percentage;
	character->SetMoveSpeed(new_ms);
}

void SlowEffect::Update(float dtime)
{
	Effect::Update(dtime);
}

void SlowEffect::SetPercentage(float percentage)
{
	this->percentage = percentage;
}