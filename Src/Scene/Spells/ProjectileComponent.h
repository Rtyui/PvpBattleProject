#pragma once

#include "Component.h"
#include "stdincl.h"
#include "Spell.h"

class ProjectileComponent : public Component
{
	REGISTER(ProjectileComponent);

public:

	ProjectileComponent(void);
	~ProjectileComponent(void);

	void							Update(float dtime);

	void							SetDirection(Vector2f dir);
	void							SetSpeed(float speed);
	void							SetSpell(SpellRef spell);
	void							SetUser(ObjectRef user);

	void							SetCanApplyOnUser(bool value);
	void							SetCanReflect(bool value);
private:

	//virtual void					ParseAttribute(const TiXmlAttribute* attribute) override;

	SpellRef						m_spell;

	Vector2f						m_direction;
	float							m_speed;

	ObjectRef						m_user;

	bool							m_canApplyOnUser;
	bool							m_canReflect;
	static const float				m_duration;
	float							m_lifespan;


};

