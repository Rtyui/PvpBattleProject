#include "stdincl.h"
#include "Input.h"
#include "App.h"
#include "PlayerMovement.h"
#include "Physics.h"
#include "Helpers.h"
#include "CharacterComponent.h"
#include "SpriteComponent.h"
#include "OptionsManager.h"

REGISTERIMPL(PlayerMovement);

float PlayerMovement::m_jumpPower = -8.f;


PlayerMovement::PlayerMovement() :
m_verticalVelocity(0.f),
m_direction(Vector2f(1, 0))
{
}

PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::Update(float dtime)
{
	m_verticalVelocity += Physics::GetGravity() * dtime;
	Vector2f deltaMove = Vector2f(0.f, 0.f);

	auto character = m_object->GetComponent<CharacterComponent>()->GetCharacter();

	if (character->CanMove())
	{
		float moveSpeed = character->GetModifiedMoveSpeed();

		if (g_input->IsPressed(g_optionsManager->GetKeyForAction(OptionsManager::MOVE_LEFT, m_controlsSet)))
		{
			if (character->ControlsInverted()) goto invertRight;
			invertedLeft:
			deltaMove += Vector2f(-moveSpeed * dtime, 0.f);
			if (m_direction.x == 1)
			{
				m_direction = Vector2f(-1, 0);
				SwitchSide();
			}
		}
		else if (g_input->IsPressed(g_optionsManager->GetKeyForAction(OptionsManager::MOVE_RIGHT, m_controlsSet)))
		{
			if (character->ControlsInverted()) goto invertedLeft;
			invertRight:
			deltaMove += Vector2f(moveSpeed * dtime, 0.f);
			if (m_direction.x == -1)
			{
				m_direction = Vector2f(1, 0);
				SwitchSide();
			}
		}
		if (g_input->IsPressed(g_optionsManager->GetKeyForAction(OptionsManager::JUMP, m_controlsSet)) && m_onGround)
		{
			m_verticalVelocity = m_jumpPower;
			SetOnGround(false);
		}
	}

	m_object->SetPos(m_object->GetPos() + deltaMove + Vector2f(0.f, m_verticalVelocity));
}

void PlayerMovement::SetOnGround(bool value)
{
	m_onGround = value;
}

void PlayerMovement::SetVerticalVelocity(float value)
{
	m_verticalVelocity = value;
}

void PlayerMovement::SetControls(int controls)
{
	m_controlsSet = controls;
}

float PlayerMovement::GetVerticalVelocity()
{
	return m_verticalVelocity;
}

Vector2f PlayerMovement::GetDirection()
{
	return m_direction;
}

void PlayerMovement::SwitchSide()
{
	auto spriteComp = m_object->GetComponent<SpriteComponent>();

	spriteComp->Flip();
}


void PlayerMovement::ParseAttribute(const TiXmlAttribute* attribute)
{
	if (IsEqual(attribute->Name(), "controls"))
	{
		SetControls(attribute->IntValue());
	}
}
