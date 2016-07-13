#include "Effect.h"

Effect::Effect()
{
}

Effect::~Effect()
{
}

void Effect::Apply(CharacterRef character)
{
	this->character = character;
	this->character->AddEffect(this);
}

void Effect::UnApply()
{
	this->character->RemoveEffect(this);
}

void Effect::Update(float dtime)
{
	duration -= dtime;

	if (duration <= 0)
	{
		UnApply();
	}
}

void Effect::SetDuration(float duration)
{
	this->duration = duration;
}