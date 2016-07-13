#include "Helpers.h"
#include "DashComponent.h"
#include "App.h"
#include "Helpers.h"
#include "stdincl.h"
#include "Input.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "PlayerMovement.h"
#include "CharacterComponent.h"
#include "StunEffect.h"

REGISTERIMPL(DashComponent);

DashComponent::DashComponent() :
m_enabled(false),
m_justEnabled(true)
{
}

DashComponent::~DashComponent()
{
}

void DashComponent::OnAddToObject()
{
}

void DashComponent::Update(float dtime)
{
	if (!m_enabled) return;
	if (m_justEnabled)
	{
		m_justEnabled = false;
		m_direction = m_object->GetComponent<PlayerMovement>()->GetDirection();
	}
	m_duration -= dtime;
	if (m_duration <= 0.f)
	{
		ShouldDesroy();
	}

	m_object->SetPos(m_object->GetPos() + m_direction * m_dashSpeed * dtime);

	auto colliderComp = m_object->GetComponent<ColliderComponent>();
	auto collidedObj = colliderComp->GetCollidedObj();

	auto collidedCharacterComp = collidedObj->GetComponent<CharacterComponent>();

	if (collidedCharacterComp != NULL)
	{
		EffectRef effect = new StunEffect();
		effect->SetDuration(m_stun);
		effect->Apply(collidedCharacterComp->GetCharacter());

		collidedCharacterComp->GetCharacter()->TakeDamage(m_damage);

		ShouldDesroy();
	}
}

void DashComponent::ShouldDesroy()
{
	m_object->GetComponent<CharacterComponent>()->GetCharacter()->SetCanMove(true);
	m_enabled = false;
	m_justEnabled = true;
}

void DashComponent::SetDuration(float duration)
{
	m_duration = duration;
}

void DashComponent::SetDashSpeed(float dashSpeed)
{
	m_dashSpeed = dashSpeed;
}

void DashComponent::SetStun(float stun)
{
	m_stun = stun;
}

void DashComponent::SetDamage(int damage)
{
	m_damage = damage;
}

void DashComponent::SetEnabled(bool value)
{
	m_enabled = value;
}