#include "Helpers.h"
#include "ProjectileComponent.h"
#include "App.h"
#include "Helpers.h"
#include "stdincl.h"
#include "Input.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"

REGISTERIMPL(ProjectileComponent);

const float ProjectileComponent::m_duration = 10.f;

ProjectileComponent::ProjectileComponent() :
m_canApplyOnUser(false),
m_canReflect(false),
m_lifespan(0.f)
{
}

ProjectileComponent::~ProjectileComponent()
{
}

void ProjectileComponent::Update(float dtime)
{
	m_lifespan += dtime;
	if (m_lifespan >= m_duration)
	{
		m_object->Trash();
	}

	auto colliderComp = m_object->GetComponent<ColliderComponent>();
	auto collidedObj = colliderComp->GetCollidedObj();

	if (collidedObj != NULL && collidedObj->GetComponent<ProjectileComponent>() == NULL )
	{
		if (m_canReflect && StringStartsWith("platform", collidedObj->GetName().c_str()))
		{
			SetDirection(Vector2f(m_direction.x * -1.f, m_direction.y * -1.f));
		}
		else if (m_canApplyOnUser) 
		{
			m_spell->Apply(collidedObj);
			m_object->Trash();
		}
		else if (collidedObj != m_user) 
		{
			m_spell->Apply(collidedObj);
			m_object->Trash();
		}


	}

	Vector2f deltaMove = m_direction * m_speed * dtime;
	m_object->SetPos(m_object->GetPos() + deltaMove);

	colliderComp->SetCollidedObject(NULL);
}

void ProjectileComponent::SetDirection(Vector2f dir)
{
	m_direction = dir;
}

void ProjectileComponent::SetSpeed(float speed)
{
	m_speed = speed;
}

void ProjectileComponent::SetSpell(SpellRef spell)
{
	m_spell = spell;
}

void ProjectileComponent::SetCanApplyOnUser(bool value)
{
	m_canApplyOnUser = value;
}

void ProjectileComponent::SetCanReflect(bool value)
{
	m_canReflect = value;
}

void ProjectileComponent::SetUser(ObjectRef user)
{
	m_user = user;
}

