#pragma once
#include "stdincl.h"
#include "Particle.h"
#include "ParticleContainer.h"

class ParticleGenerator
{
public:
	ParticleGenerator();
	~ParticleGenerator();

	virtual void					GenerateBurst(ParticleContainer& container);
	virtual void					Generate(ParticleContainer& container, float dtime);

	virtual void					ParseAttributes(const TiXmlElement* element);

	void							SetParticlesPerSecond(int perSecond);
	void							SetParticlesBurst(int burst);

	void							SetParticleLifetime(float lifetime);

protected:

	virtual void					ParseAttribute(const TiXmlAttribute* attribute);

	int								m_perSecond;
	int								m_burst;

	float							m_particleLifetime;


};