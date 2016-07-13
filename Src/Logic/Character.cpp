#include "Character.h"
#include "Effect.h"
#include "Helpers.h"

Character::Character()
{
}

Character::~Character()
{
}

SpellRef Character::GetSpellByIndex(int index)
{
	return spells.at(index);
}

void Character::TakeDamage(int damage)
{
	hp -= damage;
}

int Character::GetSpellCount()
{
	return spells.size();
}

int Character::GetHp()
{
	return hp;
}

int Character::GetMaxHp()
{
	return maxHp;
}

float Character::GetModifiedMoveSpeed()
{
	return modifiedMoveSpeed;
}

void Character::AddEffect(EffectRef effect)
{
	activeEffects.push_back(effect);
}

void Character::RemoveEffect(EffectRef effect)
{
	int size = activeEffects.size();
	
	for (int i = 0; i < size; ++i)
	{
		if (activeEffects[i] == effect)
		{
			activeEffects.erase(activeEffects.begin() + i);
			break;
		}
	}
}

void Character::UpdateEffects(float dtime)
{
	for (int i = 0; i < activeEffects.size(); i++)
	{
		activeEffects[i]->Update(dtime);
	}
}

float Character::GetMoveSpeed()
{
	return moveSpeed;
}

bool Character::CanMove()
{
	return canMove;
}

bool Character::ControlsInverted()
{
	return controlsInverted;
}

void Character::SetCanMove(bool value)
{
	canMove = value;
}

void Character::HealPercent(int percentage)
{
	hp += (percentage / 100.f) * maxHp;
	if (hp > maxHp)
		hp = maxHp;
}

void Character::SetMoveSpeed(float newMoveSpeed)
{
	this->modifiedMoveSpeed = newMoveSpeed;
}

void Character::SetControlsInverted(bool value)
{
	controlsInverted = value;
}

