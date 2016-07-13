#pragma once
#include "stdincl.h"
#include "Particle.h"

class ParticleEvolver
{
public:
	ParticleEvolver();
	~ParticleEvolver();

	void												EvolveParticle(Particle* p);

	void												ParseAttributes(const TiXmlElement* element);

protected:

	void												AddEvolutionStage(const TiXmlAttribute* attribute);

	std::vector<std::pair<float, uint> >				m_redEvolution;
	std::vector<std::pair<float, uint> >				m_greenEvolution;
	std::vector<std::pair<float, uint> >				m_blueEvolution;

	std::vector<std::pair<float, uint> >				m_alphaEvolution;

	std::vector<std::pair<float, float> >				m_scaleEvolutionX;
	std::vector<std::pair<float, float> >				m_scaleEvolutionY;


};