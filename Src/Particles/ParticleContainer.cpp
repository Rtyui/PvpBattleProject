#include "ParticleContainer.h"

ParticleContainer::ParticleContainer()
{
}

ParticleContainer::~ParticleContainer()
{
}

void ParticleContainer::AddParticle(Particle p)
{
	m_particles.push_back(p);
}

Particle* ParticleContainer::GetParticle(uint i)
{
	return &m_particles[i];
}

uint ParticleContainer::GetSize()
{
	return m_particles.size();
}

void ParticleContainer::RemoveParticle(uint i)
{
	m_particles.erase(m_particles.begin() + i);
}