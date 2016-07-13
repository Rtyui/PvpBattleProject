#include "App.h"
#include "DisorientEffect.h"

DisorientEffect::DisorientEffect()
{
}

DisorientEffect::~DisorientEffect()
{
}

void DisorientEffect::Apply(CharacterRef character)
{
	Effect::Apply(character);
	character->SetControlsInverted(true);
}

void DisorientEffect::UnApply()
{
	Effect::UnApply();
	character->SetControlsInverted(false);
}

void DisorientEffect::Update(float dtime)
{
	Effect::Update(dtime);
}