#include "ColliderComponent.h"
#include "App.h"
#include "Helpers.h"
#include "Input.h"
#include "MenuHandler.h"
#include "ShapeRectangle.h"
#include "PlayerMovement.h"
#include "ProjectileComponent.h"

REGISTERIMPL(ColliderComponent);

ColliderComponent::ColliderComponent() :
m_isStatic(false)
{
	m_collidedObject = NULL;
}

ColliderComponent::~ColliderComponent()
{
	delete m_shape;
}

void ColliderComponent::Update(float dtime)
{
	m_shape->UpdatePosition(m_object->GetGlobalPos());
}

void ColliderComponent::PostUpdate(float dtime)
{
	if (!m_isStatic)
	{
		CheckObjectForCollider(g_menuHandler->GetCurrentMenu());
	}
}

void ColliderComponent::CheckObjectForCollider(ObjectRef object)
{
	if (object->GetComponent<ColliderComponent>() && object != m_object)
	{
		CheckCollision(object);
	}
	for (uint i = 0; i < object->GetChildrenCount(); ++i)
	{
		CheckObjectForCollider(object->GetChild(i));
	}
}

void ColliderComponent::CheckCollision(ObjectRef object)
{
	auto colliderComp = object->GetComponent<ColliderComponent>();

	Vector2f delta = colliderComp->m_shape->Overlapped(m_shape);

	if ((delta.x != 0 || delta.y != 0) && object->GetComponent<ProjectileComponent>() == NULL) {
		m_collidedObject = object;
	}

	if (!m_isPhantom && !colliderComp->m_isPhantom)
		m_object->SetPos(m_object->GetPos() + delta);
	else
	{
		return;
	}

	auto moveComp = m_object->GetComponent<PlayerMovement>();

	if (moveComp)
	{
		if (delta.y < 0.f && moveComp->GetVerticalVelocity() > 0.f)
		{
			moveComp->SetOnGround(true);
			moveComp->SetVerticalVelocity(0.f);
		}
		else if (delta.y > 0.f && moveComp->GetVerticalVelocity() < 0.f)
		{
			moveComp->SetVerticalVelocity(0.f);
		}
		else if (delta.x == 0.f && delta.y == 0.f && moveComp->GetVerticalVelocity() > 0.f)
		{
			moveComp->SetOnGround(false);
		}
	}

}

void ColliderComponent::InitShape(const char* shape, const char* csize)
{
	if (IsEqual(shape, "rectangle"))
	{
		Vector2f size = ParseVector2f(csize);
		m_shape = new ShapeRectangle(size / 2.f, size);
	}
}

void ColliderComponent::SetIsStatic(bool value)
{
	m_isStatic = value;
}

void ColliderComponent::SetIsPhantom(bool value)
{
	m_isPhantom = value;
}

ObjectRef ColliderComponent::GetCollidedObj()
{
	return m_collidedObject;
}

bool ColliderComponent::IsPhantom()
{
	return m_isPhantom;
}

void ColliderComponent::SetCollidedObject(ObjectRef value)
{
	m_collidedObject = value;
}


void ColliderComponent::ParseAttribute(const TiXmlAttribute* attribute)
{
	if (IsEqual(attribute->Name(), "shape"))
	{
		InitShape(attribute->Value(), attribute->Next()->Value());
	}
	else if (IsEqual(attribute->Name(), "static"))
	{
		SetIsStatic(attribute->BoolValue());
	}
}
