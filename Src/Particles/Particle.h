#pragma once
#include "stdincl.h"

class Particle
{
public:

	enum COLORS {RED, GREEN, BLUE, ALPHA, NUM_COLORS};

	Particle();
	~Particle();

	void						SetPoisiton(Vector2f position);
	void						SetVelocity(Vector2f velocity);
	void						SetScale(Vector2f scale);
	void						SetLifetime(float lifetime);
	void						SetColor(uint red, uint green, uint blue, uint alpha);

	Vector2f					GetPosition();
	Vector2f					GetVelocity();
	Vector2f					GetScale();
	sf::Color					GetColor();

	void						Age(float deltaAge);
	bool						IsDead();

	sf::Transform				GetTransform();
	float						GetLifePercentage();

	void						Move(float dtime);

private:

	Vector2f					m_position;
	Vector2f					m_velocity;

	Vector2f					m_scale;

	sf::Transformable			m_transformable;

	uint						m_color[NUM_COLORS]; // RED, GREEN, BLUE, ALPHA

	float						m_lifetime;
	float						m_age;

};