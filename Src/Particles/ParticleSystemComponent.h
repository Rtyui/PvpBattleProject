#pragma once
#include "stdincl.h"
#include "Component.h"
#include "ParticleGenerator.h"
#include "ParticleContainer.h"
#include "ParticlePhysics.h"
#include "ParticleEvolver.h"

class ParticleSystemComponent : public Component
{
	REGISTER(ParticleSystemComponent);
public:
	ParticleSystemComponent();
	~ParticleSystemComponent();


	void							CreateGenerator(const std::string& type);

	void							Update(float dtime) override;

	void							Draw();

	void							UpdateParticles(float dtime);

	void							SetTexture(const std::string& texture);

	void							ParseAttributes(const TiXmlElement* element) override;

private:

	void							ParseAttribute(const TiXmlAttribute* attribute) override;

	ParticleGenerator*				m_generator;
	ParticleContainer				m_container;
	ParticlePhysics					m_physics;
	ParticleEvolver					m_evolver;

	sf::Sprite						m_sprite;
	sf::Texture						m_texture;

	sf::RenderStates				m_states;
	sf::RenderTexture				m_renderTexture;
};