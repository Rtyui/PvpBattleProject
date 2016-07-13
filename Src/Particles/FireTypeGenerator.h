#pragma once
#include "stdincl.h"
#include "ParticleGenerator.h"

class FireTypeGenerator : public ParticleGenerator
{
public:
	FireTypeGenerator();
	~FireTypeGenerator();

	virtual void					GenerateBurst(ParticleContainer& container) override;
	virtual void					Generate(ParticleContainer& container, float dtime) override;

	void							SetGeneratingRange(Vector2f range);

private:

	void							ParseAttribute(const TiXmlAttribute* attribute) override;

	Vector2f						m_generatingRange;

	float							m_accumulator;
};