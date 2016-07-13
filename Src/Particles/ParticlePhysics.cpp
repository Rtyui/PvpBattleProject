#include "ParticlePhysics.h"
#include "Helpers.h"

ParticlePhysics::ParticlePhysics()
{
}

ParticlePhysics::~ParticlePhysics()
{
}

void ParticlePhysics::ApplyPhysics(Particle* p, float dtime)
{
	p->SetVelocity(p->GetVelocity() + Vector2f(0.f, m_gravity * dtime));
}

void ParticlePhysics::SetGravity(float gravity)
{
	m_gravity = gravity;
}

void ParticlePhysics::ParseAttributes(const TiXmlElement* element)
{
	for (auto a = element->FirstAttribute(); a; a = a->Next())
	{
		ParseAttribute(a);
	}
}

void ParticlePhysics::ParseAttribute(const TiXmlAttribute* attribute)
{
	if (IsEqual(attribute->Name(), "gravity"))
	{
		SetGravity(attribute->FloatValue());
	}
}