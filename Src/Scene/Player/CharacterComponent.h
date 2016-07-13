#pragma once

#include "Component.h"
#include "stdincl.h"
#include "Character.h"

class CharacterComponent : public Component
{
	REGISTER(CharacterComponent);

public:

	CharacterComponent(void);
	~CharacterComponent(void);

	void							OnAddToObject() override;


	virtual void					Update(float dtime) override;
	void							CheckSpellUse();
	CharacterRef					GetCharacter();
	void							SetEnemy(ObjectRef enemy);
	void							SetControls(uint controls);

	void							CreateCharacter(const std::string& type);

private:

	virtual void					ParseAttribute(const TiXmlAttribute* attribute) override;

	CharacterRef					m_character;
	ObjectRef						m_enemy;
	uint							m_controlsSet;
};		

