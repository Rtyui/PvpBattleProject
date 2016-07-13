#pragma once
#include "stdincl.h"
#include "Particle.h"

class ParticleContainer
{
public:
	ParticleContainer();
	~ParticleContainer();

	void									AddParticle(Particle p);

	Particle*								GetParticle(uint i);
	uint									GetSize();

	void									RemoveParticle(uint i);

protected:

	std::vector<Particle>					m_particles;

};