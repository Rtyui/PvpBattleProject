#include "EditableTextBox.h"
#include "App.h"
#include "Helpers.h"
#include "stdincl.h"
#include "Input.h"
#include "SpriteComponent.h"

REGISTERIMPL(EditableTextBox);

EditableTextBox::EditableTextBox() :
m_selected(false)
{
}

EditableTextBox::~EditableTextBox()
{
}

void EditableTextBox::OnAddToObject()
{
	CreateObjects();
}

void EditableTextBox::Update(float dtime)
{
	CheckMouseCollision();

	if (m_selected)
	{
		if (g_input->WasKeyPressed())
		{
			AddCharacter();
		}
		if (g_input->WasPressedThisTurn(KEY_BACKSPACE))
		{
			DeleteLastCharacter();
		}
	}
}

void EditableTextBox::CreateObjects()
{
	auto selectedObj = Object::Create();
	auto unselectedObj = Object::Create();
	auto textHolderObj = Object::Create();

	auto selectedSpriteComp = selectedObj->AddComponent<SpriteComponent>();
	auto unselectedSpriteComp = unselectedObj->AddComponent<SpriteComponent>();
	auto textComp = textHolderObj->AddComponent<TextComponent>();

	selectedSpriteComp->SetTexture(m_textures[SELECTED]);
	unselectedSpriteComp->SetTexture(m_textures[UNSELECTED]);
	textComp->SetFont(m_font);

	selectedSpriteComp->SetSize(m_size);
	unselectedSpriteComp->SetSize(m_size);
	textComp->SetFontSize(m_fontSize);
	textComp->SetTextColor(sf::Color(m_textColor.x, m_textColor.y, m_textColor.z));

	m_spritesHolders[SELECTED] = selectedObj.get();
	m_spritesHolders[UNSELECTED] = unselectedObj.get();
	m_textHolder = textHolderObj.get();

	m_object->AddChild(std::move(selectedObj));
	m_object->AddChild(std::move(unselectedObj));
	m_object->AddChild(std::move(textHolderObj));

	m_spritesHolders[SELECTED]->Disable();
}

void EditableTextBox::CheckMouseCollision()
{
	Vector2f diff = g_input->GetMousePosition() - m_object->GetGlobalPos();
	float alpha = -m_object->GetGlobalRotation() * (float)PI / 180.f;
	Vector2f rotatedDiff = Vector2f(diff.x * cos(alpha) - diff.y * sin(alpha), diff.x * sin(alpha) + diff.y * cos(alpha));

	if (rotatedDiff.x >= 0 &&
		rotatedDiff.y >= 0 &&

		rotatedDiff.x <= m_size.x &&
		rotatedDiff.y <= m_size.y)
	{
		if (g_input->WasPressedThisTurn(MOUSE_LEFT))
		{
			Select();
		}
	}
	else
	{
		if (g_input->WasPressedThisTurn(MOUSE_LEFT))
		{
			UnSelect();
		}

	}
}

void EditableTextBox::SetSize(Vector2f size)
{
	m_size = size;
}

void EditableTextBox::SetFont(const std::string& font)
{
	m_font = font;
}

void EditableTextBox::SetFontSize(uint fontSize)
{
	m_fontSize = fontSize;
}


void EditableTextBox::SetTextureSelected(const std::string& texture)
{
	m_textures[SELECTED] = texture;
}

void EditableTextBox::SetTextureUnselected(const std::string& texture)
{
	m_textures[UNSELECTED] = texture;
}

void EditableTextBox::SetTextMaxLength(uint maxLength)
{
	m_textMaxLength = maxLength;
}

void EditableTextBox::SetTextColor(Vector3f color)
{
	m_textColor = color;
}

void EditableTextBox::ClearText()
{
	auto textComp = m_textHolder->GetComponent<TextComponent>();
	assert(textComp);

	textComp->SetText("");
}

std::string EditableTextBox::GetText()
{
	auto textComp = m_textHolder->GetComponent<TextComponent>();
	assert(textComp);

	return textComp->GetText();
}

void EditableTextBox::Select()
{
	if (!m_selected)
	{
		m_selected = true;
		m_spritesHolders[SELECTED]->Enable();
		m_spritesHolders[UNSELECTED]->Disable();
	}
}

void EditableTextBox::UnSelect()
{
	if (m_selected)
	{
		m_selected = false;
		m_spritesHolders[SELECTED]->Disable();
		m_spritesHolders[UNSELECTED]->Enable();
	}
}

void EditableTextBox::AddCharacter()
{
	auto textComp = m_textHolder->GetComponent<TextComponent>();
	assert(textComp);

	if (textComp->GetText().size() < m_textMaxLength)
	{
		if (g_input->IsPressed(KEY_SHIFT))
		{
			textComp->SetText(textComp->GetText() + g_STAT->TranslateShifted(g_input->KeyPressed()));
		}
		else
		{
			textComp->SetText(textComp->GetText() + g_STAT->Translate(g_input->KeyPressed()));
		}
	}
}

void EditableTextBox::DeleteLastCharacter()
{
	auto textComp = m_textHolder->GetComponent<TextComponent>();
	assert(textComp);

	std::string s = textComp->GetText();
	if (s.size() > 0)
	{
		s.resize(s.size() - 1);
	}
	textComp->SetText(s);
}

void EditableTextBox::ParseAttribute(const TiXmlAttribute* attribute)
{
	Component::ParseAttribute(attribute);
	if (IsEqual(attribute->Name(), "texture_selected"))
	{
		SetTextureSelected(attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "texture_unselected"))
	{
		SetTextureUnselected(attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "size"))
	{
		SetSize(ParseVector2f(attribute->Value()));
	}
	else if (IsEqual(attribute->Name(), "font"))
	{
		SetFont(attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "font_size"))
	{
		SetFontSize(attribute->UnsignedValue());
	}
	else if (IsEqual(attribute->Name(), "max_length"))
	{
		SetTextMaxLength(attribute->UnsignedValue());
	}
	else if (IsEqual(attribute->Name(), "color"))
	{
		SetTextColor(ParseVector3f(attribute->Value()));
	}
}