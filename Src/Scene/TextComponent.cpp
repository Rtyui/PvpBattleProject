#include "TextComponent.h"
#include "App.h"
#include "Helpers.h"
#include "stdincl.h"

REGISTERIMPL(TextComponent);

TextComponent::TextComponent() : 
	m_alpha(255)
{
}

TextComponent::~TextComponent()
{
}

sf::Font TextComponent::GetFont()
{
	return m_font;
}

std::string TextComponent::GetText()
{
	return m_text.getString();
}

uint TextComponent::GetFontSize()
{
	return m_fontSize;
}

Vector2f TextComponent::GetSize()
{
	return Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height);
}


void TextComponent::SetFont(const std::string& filename)
{
	std::string file;
	file.append(FONTS_FOLDER);
	file.append(filename);

	m_font.loadFromFile(file);
	m_text.setFont(m_font);
}

void TextComponent::SetText(const std::string& textName)
{
	m_textName = textName;
	m_text.setString(m_textName);
}

void TextComponent::SetFontSize(uint fontSize)
{
	m_fontSize = fontSize;
	m_text.setCharacterSize(m_fontSize);
}

void TextComponent::SetTextColor(sf::Color color)
{
	m_color = color;
	m_text.setColor(m_color);
}

void TextComponent::SetAlpha(uint alpha)
{
	m_alpha = alpha;
	sf::Color c = m_text.getColor();
	c.a = m_alpha;
	m_text.setColor(c);
}

void TextComponent::SetColor(const sf::Color& color)
{
	m_text.setColor(color);
}

sf::Color TextComponent::GetColor()
{
	return m_text.getColor();
}

void TextComponent::Update(float dtime)
{
}

void TextComponent::PostUpdate(float dtime)
{
}

void TextComponent::Draw()
{
	g_app->m_window.draw(m_text, m_object->GetTransform());
}

void TextComponent::ParseAttribute(const TiXmlAttribute* attribute)
{
	Component::ParseAttribute(attribute);

	if (IsEqual(attribute->Name(), "font"))
	{
		SetFont(attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "text"))
	{
		SetText(attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "font_size"))
	{
		SetFontSize(attribute->IntValue());
	}
	else if (IsEqual(attribute->Name(), "color"))
	{
		Vector3f v = ParseVector3f(attribute->Value());
		SetTextColor(sf::Color((uint)v.x, (uint)v.y, (uint)v.z, m_alpha));
	}
	else if (IsEqual(attribute->Name(), "alpha"))
	{
		SetAlpha(attribute->IntValue());
	}
}