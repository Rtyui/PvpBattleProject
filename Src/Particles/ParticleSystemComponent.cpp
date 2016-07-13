#include "ParticleSystemComponent.h"
#include "Helpers.h"
#include "ExplosionTypeGenerator.h"
#include "App.h"
#include "FireTypeGenerator.h"

REGISTERIMPL(ParticleSystemComponent);

ParticleSystemComponent::ParticleSystemComponent()
{
	m_states.blendMode = sf::BlendAdd;
	m_renderTexture.create(1280, 720);
}

ParticleSystemComponent::~ParticleSystemComponent()
{
	delete m_generator;
}

void ParticleSystemComponent::CreateGenerator(const std::string& type)
{
	if (IsEqual(type.c_str(), "explosion"))
	{
		m_generator = new ExplosionTypeGenerator();
	}
	else if (IsEqual(type.c_str(), "fire"))
	{
		m_generator = new FireTypeGenerator();
	}
}

void ParticleSystemComponent::Update(float dtime)
{
	m_generator->Generate(m_container, dtime);
	UpdateParticles(dtime);
}

void ParticleSystemComponent::Draw()
{
	m_states.blendMode = sf::BlendAdd;

	m_renderTexture.clear(sf::Color::Transparent);

	for (uint i = 0; i < m_container.GetSize(); ++i)
	{
		auto p = m_container.GetParticle(i);
		m_sprite.setColor(p->GetColor());
		
		m_states.transform = m_object->GetTransform() * p->GetTransform();

		m_renderTexture.draw(m_sprite, m_states);
	}

	m_renderTexture.display();

	sf::Sprite sprite(m_renderTexture.getTexture());
	g_app->m_window.draw(sprite);

}

void ParticleSystemComponent::UpdateParticles(float dtime)
{
	for (uint i = 0; i < m_container.GetSize(); ++i)
	{
		auto p = m_container.GetParticle(i);
		p->Age(dtime);
		if (p->IsDead())
		{
			m_container.RemoveParticle(i);
			continue;
		}
		p->Move(dtime);
		p->SetPoisiton(m_container.GetParticle(i)->GetPosition() + m_container.GetParticle(i)->GetVelocity() * dtime);
		m_physics.ApplyPhysics(p, dtime);
		m_evolver.EvolveParticle(p);
	}
}

void ParticleSystemComponent::SetTexture(const std::string& texture)
{
	std::string file;
	file.append(TEXTURES_FOLDER);
	file.append(texture);

	m_texture.loadFromFile(file);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
}

void ParticleSystemComponent::ParseAttributes(const TiXmlElement* element)
{
	for (auto a = element->FirstAttribute(); a; a = a->Next())
	{
		ParseAttribute(a);
	}

	for (auto e = element->FirstChildElement(); e; e = e->NextSiblingElement())
	{
		if (IsEqual(e->Value(), "Generator"))
		{
			m_generator->ParseAttributes(e);
		}
		else if (IsEqual(e->Value(), "Physics"))
		{
			m_physics.ParseAttributes(e);
		}
		else if (IsEqual(e->Value(), "Evolver"))
		{
			m_evolver.ParseAttributes(e);
		}
	}
}

void ParticleSystemComponent::ParseAttribute(const TiXmlAttribute* attribute)
{
	if (IsEqual(attribute->Name(), "generator_type"))
	{
		CreateGenerator(attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "texture"))
	{
		SetTexture(attribute->Value());
	}
}