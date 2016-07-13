#include "Helpers.h"
#include "SpellFeedbackComponent.h"
#include "SpriteComponent.h"
#include "MainGame.h"

REGISTERIMPL(SpellFeedbackComponent);

SpellFeedbackComponent::SpellFeedbackComponent()
{
}

SpellFeedbackComponent::~SpellFeedbackComponent()
{
}

void SpellFeedbackComponent::OnAddToObject()
{
}

void SpellFeedbackComponent::Update(float dtime)
{
	if (m_object->GetParent()->GetComponent<MainGame>()->BattleEndedAnnounced())
	{
		m_object->Trash();
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		SpellRef spell = m_character->GetSpellByIndex(i);

		if (!spell->CanCast())
		{
			m_xes[i]->Enable();
		} else {
			m_xes[i]->Disable();
		}


	}
}

void SpellFeedbackComponent::SetCharacter(const std::string& character)
{
	auto firstSpell = Object::Create();
	auto secondSpell = Object::Create();
	auto thirdSpell = Object::Create();
	
	auto x1 = Object::Create();
	auto x2 = Object::Create();
	auto x3 = Object::Create();

	auto firstSpellSprite = firstSpell->AddComponent<SpriteComponent>();
	auto secondSpellSprite = secondSpell->AddComponent<SpriteComponent>();
	auto thirdSpellSprite = thirdSpell->AddComponent<SpriteComponent>();

	auto x1_Sprite = x1->AddComponent<SpriteComponent>();
	auto x2_Sprite = x2->AddComponent<SpriteComponent>();
	auto x3_Sprite = x3->AddComponent<SpriteComponent>();

	x1_Sprite->SetTexture("x.png");
	x2_Sprite->SetTexture("x.png");
	x3_Sprite->SetTexture("x.png");

	x1_Sprite->SetSize(Vector2f(35.f, 35.f));
	x2_Sprite->SetSize(Vector2f(35.f, 35.f));
	x3_Sprite->SetSize(Vector2f(35.f, 35.f));

	if (IsEqual(character.c_str(), "wizard"))
	{
		firstSpellSprite->SetTexture("wizard_spell1.png");
		secondSpellSprite->SetTexture("wizard_spell2.png");
		thirdSpellSprite->SetTexture("wizard_spell3.png");
	}
	else if (IsEqual(character.c_str(), "warrior"))
	{
		firstSpellSprite->SetTexture("warrior_spell1.png");
		secondSpellSprite->SetTexture("warrior_spell2.png");
		thirdSpellSprite->SetTexture("warrior_spell3.png");
	}
	else if (IsEqual(character.c_str(), "assassin"))
	{
		firstSpellSprite->SetTexture("assassin_spell1.png");
		secondSpellSprite->SetTexture("assassin_spell2.png");
		thirdSpellSprite->SetTexture("assassin_spell3.png");
	}


	firstSpellSprite->SetSize(Vector2f(35.f, 35.f));
	secondSpellSprite->SetSize(Vector2f(35.f, 35.f));
	thirdSpellSprite->SetSize(Vector2f(35.f, 35.f));

	secondSpell->SetPos(Vector2f(firstSpellSprite->GetSize().x, 0.f));
	thirdSpell->SetPos(Vector2f(2 * firstSpellSprite->GetSize().x, 0.f));

	x2->SetPos(Vector2f(x1_Sprite->GetSize().x, 0.f));
	x3->SetPos(Vector2f(2 * x1_Sprite->GetSize().x, 0.f));

	x1->Disable();
	x2->Disable();
	x3->Disable();

	m_spells.push_back(firstSpell.get());
	m_spells.push_back(secondSpell.get());
	m_spells.push_back(thirdSpell.get());

	m_xes.push_back(x1.get());
	m_xes.push_back(x2.get());
	m_xes.push_back(x3.get());

	m_object->AddChild(std::move(firstSpell));
	m_object->AddChild(std::move(secondSpell));
	m_object->AddChild(std::move(thirdSpell));

	m_object->AddChild(std::move(x1));
	m_object->AddChild(std::move(x2));
	m_object->AddChild(std::move(x3));
}

void SpellFeedbackComponent::SetCharacter(CharacterRef character)
{
	this->m_character = character;
}