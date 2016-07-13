#include "stdincl.h"
#include "Input.h"
#include "App.h"
#include "CharacterComponent.h"
#include "Physics.h"
#include "Helpers.h"
#include "Wizard.h"
#include "Warrior.h"
#include "Assassin.h"
#include "MainGame.h"

REGISTERIMPL(CharacterComponent);


CharacterComponent::CharacterComponent()
{
}

CharacterComponent::~CharacterComponent()
{
}

void CharacterComponent::OnAddToObject()
{
}


void CharacterComponent::Update(float dtime)
{
	if (m_object->GetParent()->GetComponent<MainGame>()->BattleEndedAnnounced())
	{
		m_object->Trash();
		return;
	}

	m_character->UpdateEffects(dtime);

	/* Treat keyboard controls */
	if (g_input->WasPressedThisTurn(g_optionsManager->GetKeyForAction(OptionsManager::SPELL1, m_controlsSet))) 
	{
		SpellRef spell = m_character->GetSpellByIndex(0);
		if (spell->CanCast())
			spell->Cast(m_object, m_enemy);
	}
	else if (g_input->WasPressedThisTurn(g_optionsManager->GetKeyForAction(OptionsManager::SPELL2, m_controlsSet)))
	{
		SpellRef spell = m_character->GetSpellByIndex(1);
		if (spell->CanCast())
			spell->Cast(m_object, m_enemy);
	}
	else if (g_input->WasPressedThisTurn(g_optionsManager->GetKeyForAction(OptionsManager::SPELL3, m_controlsSet)))
	{
		SpellRef spell = m_character->GetSpellByIndex(2);
		if (spell->CanCast())
			spell->Cast(m_object, m_enemy);
	}

	int spellCount = m_character->GetSpellCount();
	for (int i = 0; i < spellCount; ++i)
	{
		m_character->GetSpellByIndex(i)->DecreaseCooldown(dtime);
	}
}

void CharacterComponent::CheckSpellUse()
{
	 
}

CharacterRef CharacterComponent::GetCharacter()
{
	return m_character;
}

void CharacterComponent::SetEnemy(ObjectRef enemy)
{
	m_enemy = enemy;
}

void CharacterComponent::SetControls(uint controls)
{
	m_controlsSet = controls;
}

void CharacterComponent::CreateCharacter(const std::string& type)
{
	if (IsEqual(type.c_str(), "wizard"))
	{
		m_character = new Wizard();
	}
	else if (IsEqual(type.c_str(), "warrior"))
	{
		m_character = new Warrior();
	}
	else if (IsEqual(type.c_str(), "assassin"))
	{
		m_character = new Assassin();
	}

}

void CharacterComponent::ParseAttribute(const TiXmlAttribute* attribute)
{
	if (IsEqual(attribute->Name(), "type"))
	{
		CreateCharacter(std::string(attribute->Value()));
	}
}
