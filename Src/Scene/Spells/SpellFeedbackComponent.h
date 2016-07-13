#pragma once

#include "Component.h"
#include "stdincl.h"
#include "Spell.h"
#include "Character.h"

class SpellFeedbackComponent : public Component
{
	REGISTER(SpellFeedbackComponent);

public:

	SpellFeedbackComponent(void);
	~SpellFeedbackComponent(void);

	void							OnAddToObject() override;

	void							Update(float dtime) override;
	void							SetCharacter(const std::string& character);
	void							SetCharacter(CharacterRef character);

private:

	//virtual void					ParseAttribute(const TiXmlAttribute* attribute) override;

	std::vector<ObjectRef>			m_spells;
	std::vector<ObjectRef>			m_xes;

	CharacterRef					m_character;


};

