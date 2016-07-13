#include "FireTypeGenerator.h"
#include "RNG.h"
#include "Helpers.h"

FireTypeGenerator::FireTypeGenerator() :
m_accumulator(0)
{
}

FireTypeGenerator::~FireTypeGenerator()
{
}

void FireTypeGenerator::GenerateBurst(ParticleContainer& container)
{
	for (int i = 0; i < m_burst; ++i)
	{
		Particle p;

		p.SetLifetime(m_particleLifetime);

		container.AddParticle(p);
	}
}

void FireTypeGenerator::Generate(ParticleContainer& container, float dtime)
{
	m_accumulator += dtime * m_perSecond;

	while (m_accumulator > 1.f)
	{
		m_accumulator -= 1.f;

		Particle p;

		p.SetPoisiton(Vector2f(RNG::Float(-m_generatingRange.x, m_generatingRange.x), RNG::Float(-m_generatingRange.y, m_generatingRange.y)));

		p.SetLifetime(m_particleLifetime);

		container.AddParticle(p);
	}
}

void FireTypeGenerator::SetGeneratingRange(Vector2f range)
{
	m_generatingRange = range;
}

void FireTypeGenerator::ParseAttribute(const TiXmlAttribute* attribute)
{
	if (IsEqual(attribute->Name(), "generating_range"))
	{
		SetGeneratingRange(ParseVector2f(attribute->Value()));
	}
	else
	{
		ParticleGenerator::ParseAttribute(attribute);
	}
}