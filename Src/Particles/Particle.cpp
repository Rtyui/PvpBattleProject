#include "Particle.h"
#include "Helpers.h"

float MinF(float a, float b);

Particle::Particle() :
m_age(0),
m_scale(Vector2f(0.1f, 0.1f)),
m_position(Vector2f(0.f, 0.f))
{
	for (uint i = 0; i < 4; ++i)
	{
		m_color[i] = 255;
	}
	m_transformable.setScale(m_scale);
	
}

Particle::~Particle()
{
}

void Particle::SetPoisiton(Vector2f position)
{
	m_position = position;
	m_transformable.setPosition(m_position);
}

void Particle::SetVelocity(Vector2f velocity)
{
	m_velocity = velocity;
}

void Particle::SetScale(Vector2f scale)
{
	m_scale = scale;
	m_transformable.setScale(m_scale);
}

void Particle::SetLifetime(float lifetime)
{
	m_lifetime = lifetime;
}

void Particle::SetColor(uint red, uint green, uint blue, uint alpha)
{
	m_color[RED] = red;
	m_color[GREEN] = green;
	m_color[BLUE] = blue;
	m_color[ALPHA] = alpha;
}

Vector2f Particle::GetPosition()
{
	return m_position;
}

Vector2f Particle::GetVelocity()
{
	return m_velocity;
}

Vector2f Particle::GetScale()
{
	return m_scale;
}

sf::Color Particle::GetColor()
{
	sf::Color c;
	c.r = m_color[RED];
	c.g = m_color[GREEN];
	c.b = m_color[BLUE];
	c.a = m_color[ALPHA];
	return c;
}

void Particle::Age(float deltaAge)
{
	m_age = MinF(m_age + deltaAge, m_lifetime);
}

bool Particle::IsDead()
{
	return m_age == m_lifetime;
}

sf::Transform Particle::GetTransform()
{
	return m_transformable.getTransform();
}

float Particle::GetLifePercentage()
{
	return m_age / m_lifetime;
}

void Particle::Move(float dtime)
{
	m_position += m_velocity * dtime;
}