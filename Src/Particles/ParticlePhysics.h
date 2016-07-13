#pragma once
#include "stdincl.h"
#include "Particle.h"

class ParticlePhysics
{
public:
	ParticlePhysics();
	~ParticlePhysics();

	void					ApplyPhysics(Particle* p, float dtime);

	void					SetGravity(float gravity);

	void					ParseAttributes(const TiXmlElement* element);

protected:

	void					ParseAttribute(const TiXmlAttribute* attribute);

	float					m_gravity;

};