#include "ExplosionTypeGenerator.h"
#include "RNG.h"
#include "Helpers.h"

ExplosionTypeGenerator::ExplosionTypeGenerator()
{
}

ExplosionTypeGenerator::~ExplosionTypeGenerator()
{
}

void ExplosionTypeGenerator::GenerateBurst(ParticleContainer& container)
{
	for (int i = 0; i < m_burst; ++i)
	{
		Particle p;

		float angle = RNG::Float(0.f, 2 * PI);
		p.SetVelocity(Vector2f(cos(angle) * m_velocityModule, sin(angle) * m_velocityModule));

		p.SetLifetime(m_particleLifetime);

		container.AddParticle(p);
	}
}

void ExplosionTypeGenerator::SetVelocityModule(float velocityModule)
{
	m_velocityModule = velocityModule;
}

void ExplosionTypeGenerator::ParseAttribute(const TiXmlAttribute* attribute)
{
	if (IsEqual(attribute->Name(), "velocity_module"))
	{
		SetVelocityModule(attribute->FloatValue());
	}
	else
	{
		ParticleGenerator::ParseAttribute(attribute);
	}
}