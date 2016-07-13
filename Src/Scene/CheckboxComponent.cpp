#include "CheckboxComponent.h"
#include "App.h"
#include "Helpers.h"
#include "stdincl.h"
#include "Input.h"
#include "SpriteComponent.h"
#include "ButtonComponent.h"

REGISTERIMPL(CheckboxComponent);

CheckboxComponent::CheckboxComponent() :
m_selected(false),
m_focused(false)
{
}

CheckboxComponent::~CheckboxComponent()
{
}

void CheckboxComponent::OnAddToObject()
{
	AddSprite();
	AddCheck();
}

void CheckboxComponent::Focus()
{
	if (!m_focused)
	{
		m_stateObjects[FOCUSED]->Enable();
		m_stateObjects[UNFOCUSED]->Disable();
		m_focused = true;
	}
}

void CheckboxComponent::Unfocus()
{
	if (m_focused)
	{
		m_stateObjects[UNFOCUSED]->Enable();
		m_stateObjects[FOCUSED]->Disable();
		m_focused = false;
	}
}

void CheckboxComponent::Update(float dtime)
{
	CheckMouseCollision();
}

void CheckboxComponent::SetSize(Vector2f size)
{
	m_size = size;
}

void CheckboxComponent::SetTexture(uint state, const std::string& filename)
{
	m_textures[state] = filename;
}

void CheckboxComponent::SetCheckSprite(const std::string& checkSprite)
{
	m_checkSprite = checkSprite;
}

void CheckboxComponent::Toggle()
{
	if (m_selected)
	{
		UnSelect();
	}
	else
	{
		Select();
	}
}

bool CheckboxComponent::IsSelected()
{
	return m_selected;
}

void CheckboxComponent::Select()
{
	m_checkObject->Enable();
	m_selected = true;
}

void CheckboxComponent::UnSelect()
{
	m_checkObject->Disable();
	m_selected = false;
}

void CheckboxComponent::CheckMouseCollision()
{
	Vector2f diff = g_input->GetMousePosition() - m_object->GetGlobalPos();
	float alpha = -m_object->GetGlobalRotation() * (float)PI / 180.f;
	Vector2f rotatedDiff = Vector2f(diff.x * cos(alpha) - diff.y * sin(alpha), diff.x * sin(alpha) + diff.y * cos(alpha));

	if (rotatedDiff.x >= 0 &&
		rotatedDiff.y >= 0 &&

		rotatedDiff.x <= m_size.x &&
		rotatedDiff.y <= m_size.y)
	{
		Focus();
		if (g_input->WasPressedThisTurn(MOUSE_LEFT))
		{
			if (m_selected)
			{
				UnSelect();
			}
			else
			{
				Select();
			}
		}
	}
	else
	{
		Unfocus();
	}
}

void CheckboxComponent::AddSprite()
{
	auto focusedObject = Object::Create();
	auto unfocusedObject = Object::Create();

	auto focusedSpriteComp = focusedObject->AddComponent<SpriteComponent>();
	auto unfocusedSpriteComp = unfocusedObject->AddComponent<SpriteComponent>();

	focusedSpriteComp->SetTexture(m_textures[FOCUSED]);
	unfocusedSpriteComp->SetTexture(m_textures[UNFOCUSED]);

	focusedSpriteComp->SetSize(m_size);
	unfocusedSpriteComp->SetSize(m_size);

	m_stateObjects[FOCUSED] = focusedObject.get();
	m_stateObjects[UNFOCUSED] = unfocusedObject.get();

	m_object->AddChild(std::move(focusedObject));
	m_object->AddChild(std::move(unfocusedObject));

	m_stateObjects[FOCUSED]->Disable();
}

void CheckboxComponent::AddCheck()
{
	auto checkObject = Object::Create();
	auto spriteComponent = checkObject->AddComponent<SpriteComponent>();

	spriteComponent->SetTexture(m_checkSprite);
	spriteComponent->SetSize(m_size);

	checkObject->Disable();
	m_checkObject = checkObject.get();
	m_object->AddChild(std::move(checkObject));
}

void CheckboxComponent::ParseAttribute(const TiXmlAttribute* attribute)
{
	Component::ParseAttribute(attribute);
	if (IsEqual(attribute->Name(), "texture_focused"))
	{
		SetTexture(FOCUSED, attribute->Value());
	}

	else if (IsEqual(attribute->Name(), "texture_unfocused"))
	{
		SetTexture(UNFOCUSED, attribute->Value());
	}

	else if (IsEqual(attribute->Name(), "size"))
	{
		SetSize(ParseVector2f(attribute->Value()));
	}

	else if (IsEqual(attribute->Name(), "texture_check"))
	{
		SetCheckSprite(attribute->Value());
	}
}