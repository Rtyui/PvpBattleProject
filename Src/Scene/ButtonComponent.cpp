#include "ButtonComponent.h"
#include "App.h"
#include "Helpers.h"
#include "stdincl.h"
#include "Input.h"
#include "SpriteComponent.h"

REGISTERIMPL(ButtonComponent);

ButtonComponent::ButtonComponent():
m_wasPressed(false),
m_focused(false),
m_deepened(false),
m_style(DEEP_ON_FOCUS)
{
}

ButtonComponent::~ButtonComponent()
{
}

void ButtonComponent::OnAddToObject()
{
	if (m_hasTextures)
	{
		CreateSpritesObjects();
	}

	CreateTextObject();
}

void ButtonComponent::Update(float dtime)
{
	CheckMouseCollision();
}

void ButtonComponent::PostUpdate(float dtime)
{
}

uint ButtonComponent::GetTypeIndex(const std::string& type)
{
	if (IsEqual(type.c_str(), "default"))
	{
		return DEFAULT;
	}
	else if (IsEqual(type.c_str(), "menu_changer"))
	{
		return MENU_CHANGER;
	}
	else if(IsEqual(type.c_str(), "exit"))
	{
		return EXIT;
	}
	assert(nullptr);
	return 100;
}

uint ButtonComponent::GetStyleIndex(const std::string& style)
{
	if (IsEqual(style.c_str(), "deep_on_click"))
	{
		return DEEP_ON_CLICK;
	}
	else if (IsEqual(style.c_str(), "deep_on_focus"))
	{
		return DEEP_ON_FOCUS;
	}
	assert(nullptr);
	return 100;
}

void ButtonComponent::SetSize(Vector2f size)
{
	m_size = size;
}

void  ButtonComponent::SetTexture(uint state, const std::string& filename)
{
	m_textures[state] = filename;
}

void ButtonComponent::SetType(uint type)
{
	m_type = type;
}

void ButtonComponent::SetStyle(uint style)
{
	m_style = style;
}

void ButtonComponent::OnFocus()
{
	if (!m_focused)
	{
		m_focused = true;

		if (m_hasTextures)
		{
			if (m_style == DEEP_ON_FOCUS)
			{
				m_stateObjects[FOCUSED]->Enable();
				m_stateObjects[UNFOCUSED]->Disable();
			}
		}

		if (m_textHighlights)
		{
			auto textComp = m_textHolder->GetComponent<TextComponent>();
			assert(textComp);

			textComp->SetColor(sf::Color(m_textHighlight.x, m_textHighlight.y, m_textHighlight.z));
		}
	}
}

void ButtonComponent::OnUnfocus()
{
	if (m_focused)
	{
		m_focused = false;

		if (m_hasTextures)
		{
			if (m_style == DEEP_ON_FOCUS)
			{
				m_stateObjects[UNFOCUSED]->Enable();
				m_stateObjects[FOCUSED]->Disable();
			}
		}

		if (m_textHighlights)
		{
			auto textComp = m_textHolder->GetComponent<TextComponent>();
			assert(textComp);

			textComp->SetColor(sf::Color(m_textColor.x, m_textColor.y, m_textColor.z));
		}
	}
}

void ButtonComponent::OnClick()
{

	if (m_type == MENU_CHANGER)
	{
		MenuChange();
	}
	else if (m_type == EXIT)
	{
		g_app->m_window.close();
	}
	else
	{
		m_wasPressed = true;

		if (m_style == DEEP_ON_CLICK)
		{
			if (m_deepened)
			{
				UnDeepen();
			}
			else
			{
				Deepen();
			}
		}
	}
}

void ButtonComponent::Deepen()
{
	m_deepened = true;

	m_stateObjects[FOCUSED]->Enable();
	m_stateObjects[UNFOCUSED]->Disable();
}

void ButtonComponent::UnDeepen()
{
	m_deepened = false;

	m_stateObjects[UNFOCUSED]->Enable();
	m_stateObjects[FOCUSED]->Disable();
}

void ButtonComponent::SetPressed(bool clicked)
{
	m_wasPressed = clicked;
}

void ButtonComponent::CheckMouseCollision()
{
	m_wasPressed = false;
	Vector2f diff = g_input->GetMousePosition() - m_object->GetGlobalPos();
	float alpha = -m_object->GetGlobalRotation() * (float)PI / 180.f;
	Vector2f rotatedDiff = Vector2f(diff.x * cos(alpha) - diff.y * sin(alpha), diff.x * sin(alpha) + diff.y * cos(alpha));

	if (rotatedDiff.x >= 0 &&
		rotatedDiff.y >= 0 &&

		rotatedDiff.x <= m_size.x &&
		rotatedDiff.y <= m_size.y)
	{
		OnFocus();

		if (g_input->WasPressedThisTurn(MOUSE_LEFT))
		{
			OnClick();
		}
	}
	else
	{
		OnUnfocus();
	}
}

void ButtonComponent::MenuChange()
{
	g_menuHandler->SwitchMenu(g_menuHandler->GetIndex(m_nextMenu));
}

void ButtonComponent::CreateSpritesObjects()
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

void ButtonComponent::CreateTextObject()
{
	auto textObj = Object::Create();
	auto textComp = textObj->AddComponent<TextComponent>();

	textComp->SetFont(m_font);
	textComp->SetFontSize(m_fontSize);
	textComp->SetColor(sf::Color(m_textColor.x, m_textColor.y, m_textColor.z));
	textComp->SetText(m_text);

	auto offset = Vector2f((m_size.x - textComp->GetSize().x) / 2.f, (m_size.y - textComp->GetSize().y) / 2.f);

	textObj->SetPos(Vector2f(offset.x, 0));

	m_textHolder = textObj.get();

	m_object->AddChild(std::move(textObj));
}

void ButtonComponent::SetText(const std::string& text)
{
	m_text = text;

	if (m_textHolder)
	{
		auto textComp = m_textHolder->GetComponent<TextComponent>();
		assert(textComp);

		textComp->SetText(m_text);

		auto offset = Vector2f((m_size.x - textComp->GetSize().x) / 2.f, (m_size.y - textComp->GetSize().y) / 2.f);
		m_textHolder->SetPos(offset);
	}
}

void ButtonComponent::SetTextFont(const std::string& font)
{
	m_font = font;
}

void ButtonComponent::SetFontSize(uint size)
{
	m_fontSize = size;
}

void ButtonComponent::SetTextColor(Vector3f color)
{
	m_textColor = color;
}

void ButtonComponent::SetHighlightTextColor(Vector3f color)
{
	m_textHighlight = color;
}

void ButtonComponent::SetIfHasTextures(bool hasTextures)
{
	m_hasTextures = hasTextures;
}

void ButtonComponent::SetIfTextHighlights(bool textHighlights)
{
	m_textHighlights = textHighlights;
}

Vector2f ButtonComponent::GetSize()
{
	return m_size;
}

bool ButtonComponent::WasPressed()
{
	return m_wasPressed;
}


void ButtonComponent::ParseAttribute(const TiXmlAttribute* attribute)
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
	else if (IsEqual(attribute->Name(), "next_menu"))
	{
		m_nextMenu = attribute->Value();
	}
	else if (IsEqual(attribute->Name(), "type"))
	{
		SetType(GetTypeIndex(attribute->Value()));
	}
	else if (IsEqual(attribute->Name(), "style"))
	{
		SetStyle(GetStyleIndex(attribute->Value()));
	}
	else if (IsEqual(attribute->Name(), "text"))
	{
		SetText(attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "text_font"))
	{
		SetTextFont(attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "text_size"))
	{
		SetFontSize(attribute->UnsignedValue());
	}
	else if (IsEqual(attribute->Name(), "text_color"))
	{
		SetTextColor(ParseVector3f(attribute->Value()));
	}
	else if (IsEqual(attribute->Name(), "text_highlight_color"))
	{
		SetHighlightTextColor(ParseVector3f(attribute->Value()));
	}
	else if (IsEqual(attribute->Name(), "has_textures"))
	{
		SetIfHasTextures(attribute->BoolValue());
	}
	else if (IsEqual(attribute->Name(), "text_highlights"))
	{
		SetIfTextHighlights(attribute->BoolValue());
	}
}

