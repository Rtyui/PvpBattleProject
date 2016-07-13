#include "Input.h"
#include "App.h"
#include "PlayerHpBar.h"
#include "Helpers.h"
#include "SpriteComponent.h"
#include "CharacterComponent.h"
#include "MainGame.h"

REGISTERIMPL(PlayerHpBar);

PlayerHpBar::PlayerHpBar()
{
}

PlayerHpBar::~PlayerHpBar()
{
}

void PlayerHpBar::OnAddToObject()
{
	LoadTextures();
}

void PlayerHpBar::Update(float dtime)
{
	if (m_object->GetParent()->GetComponent<MainGame>()->BattleEndedAnnounced())
	{
		m_object->Trash();
		return;
	}
	SetFeedback();
}

void PlayerHpBar::SetFeedback()
{
	auto character = m_player->GetComponent<CharacterComponent>()->GetCharacter();
	int hp = character->GetHp();
	if (hp == m_lastHp) return;
	if (hp < 0) m_object->GetParent()->GetComponent<MainGame>()->AnnounceFinish(m_object->GetName());
	m_lastHp = hp;
	int maxHp = character->GetMaxHp();
	float perc = (float)hp / maxHp;

	auto sprite = m_greenBar->GetComponent<SpriteComponent>()->GetSprite();
	auto rect = sprite->getTextureRect();
	rect.width = (int)(m_barSize.x * perc);
	sprite->setTextureRect(rect);
}


void PlayerHpBar::SetTexture(const std::string &target, const std::string &filename)
{
	if (IsEqual(target.c_str(), "avatar"))
	{
		m_avatarTextureFile = filename;
	}
	else if (IsEqual(target.c_str(), "frame"))
	{
		m_frameTextureFile = filename;
	}
	else if (IsEqual(target.c_str(), "green_bar"))
	{
		m_greenBarTextureFile = filename;
	}
}

void PlayerHpBar::SetOffset(const std::string &target, Vector2f offset)
{
	if (IsEqual(target.c_str(), "avatar"))
	{
		m_avatarOffset = offset;
	}
	else if (IsEqual(target.c_str(), "bar"))
	{
		m_barOffset = offset;
	}
}

void PlayerHpBar::SetPlayer(ObjectRef player)
{
	m_player = player;
	m_lastHp = m_player->GetComponent<CharacterComponent>()->GetCharacter()->GetHp();
}

void PlayerHpBar::LoadTextures()
{
	auto avatarObject = Object::Create();
	auto frameObject = Object::Create();
	auto greenBarObject = Object::Create();

	avatarObject->SetPos(m_avatarOffset);
	greenBarObject->SetPos(m_barOffset);

	auto avatarSpriteComp = avatarObject->AddComponent<SpriteComponent>();
	auto frameSpriteComp = frameObject->AddComponent<SpriteComponent>();
	auto greenBarSpriteComp = greenBarObject->AddComponent<SpriteComponent>();

	avatarSpriteComp->SetTexture(m_avatarTextureFile);
	frameSpriteComp->SetTexture(m_frameTextureFile);
	greenBarSpriteComp->SetTexture(m_greenBarTextureFile);

	m_barSize = greenBarSpriteComp->GetSize();

	m_avatar = avatarObject.get();
	m_frame = frameObject.get();
	m_greenBar = greenBarObject.get();

	m_object->AddChild(std::move(frameObject));
	m_object->AddChild(std::move(avatarObject));
	m_object->AddChild(std::move(greenBarObject));

}

void PlayerHpBar::ParseAttribute(const TiXmlAttribute* attribute)
{
	if (IsEqual(attribute->Name(), "avatar_texture"))
	{
		SetTexture("avatar", attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "frame_texture"))
	{
		SetTexture("frame", attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "green_bar_texture"))
	{
		SetTexture("green_bar", attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "avatar_offset"))
	{
		SetOffset("avatar", ParseVector2f(attribute->Value()));
	}
	else if (IsEqual(attribute->Name(), "bar_offset"))
	{
		SetOffset("bar", ParseVector2f(attribute->Value()));
	}
}
