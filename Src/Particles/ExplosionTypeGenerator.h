#pragma once
#include "stdincl.h"
#include "ParticleGenerator.h"

class ExplosionTypeGenerator : public ParticleGenerator
{
public:
	ExplosionTypeGenerator();
	~ExplosionTypeGenerator();

	virtual void					GenerateBurst(ParticleContainer& container) override;

	void							SetVelocityModule(float velocityModule);

private:

	void							ParseAttribute(const TiXmlAttribute* attribute) override;

	float							m_velocityModule;

};