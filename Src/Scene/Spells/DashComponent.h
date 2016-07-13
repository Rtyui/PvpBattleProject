#pragma once

#include "Component.h"
#include "stdincl.h"
#include "Spell.h"

class DashComponent : public Component
{
	REGISTER(DashComponent);

public:

	DashComponent(void);
	~DashComponent(void);

	void							OnAddToObject() override;

	void							Update(float dtime) override;

	void							ShouldDesroy();

	void							SetDuration(float duration);
	void							SetDashSpeed(float dashSpeed);
	void							SetStun(float stun);
	void							SetDamage(int damage);
	void							SetEnabled(bool value);
private:

	//virtual void					ParseAttribute(const TiXmlAttribute* attribute) override;

	bool							m_enabled;
	bool							m_justEnabled;

	float							m_duration;
	float							m_dashSpeed;

	Vector2f						m_direction;

	float							m_stun;
	int								m_damage;

};

