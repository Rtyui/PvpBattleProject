#include "ParticleGenerator.h"
#include "Helpers.h"

ParticleGenerator::ParticleGenerator() :
m_perSecond(0),
m_burst(0)
{
}

ParticleGenerator::~ParticleGenerator()
{
}

void ParticleGenerator::GenerateBurst(ParticleContainer& container)
{
}

void ParticleGenerator::Generate(ParticleContainer& container, float dtime)
{
}

void ParticleGenerator::ParseAttributes(const TiXmlElement* element)
{
	for (auto a = element->FirstAttribute(); a; a = a->Next())
	{
		ParseAttribute(a);
	}
}

void ParticleGenerator::SetParticlesPerSecond(int perSecond)
{
	m_perSecond = perSecond;
}

void ParticleGenerator::SetParticlesBurst(int burst)
{
	m_burst = burst;
}

void ParticleGenerator::SetParticleLifetime(float lifetime)
{
	m_particleLifetime = lifetime;
}

void ParticleGenerator::ParseAttribute(const TiXmlAttribute* attribute)
{
	if (IsEqual(attribute->Name(), "per_second"))
	{
		SetParticlesPerSecond(attribute->IntValue());
	}
	else if(IsEqual(attribute->Name(), "burst"))
	{
		SetParticlesBurst(attribute->IntValue());
	}
	else if (IsEqual(attribute->Name(), "particle_lifetime"))
	{
		SetParticleLifetime(attribute->FloatValue());
	}
}