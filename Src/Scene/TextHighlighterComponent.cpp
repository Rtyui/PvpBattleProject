#include "TextHighlighterComponent.h"
#include "App.h"
#include "Helpers.h"
#include "stdincl.h"
#include "Input.h"
#include "SpriteComponent.h"
#include <math.h>

int MinI(int a, int b);

REGISTERIMPL(TextHighlighterComponent);

TextHighlighterComponent::TextHighlighterComponent() :
m_selected(false)
{
}

TextHighlighterComponent::~TextHighlighterComponent()
{
}

void TextHighlighterComponent::OnStart()
{
	auto textComp = m_object->GetComponent<TextComponent>();
	assert(textComp);

	auto color = textComp->GetColor();
	m_highlightedColorMask.x = (float)MinI((int)m_highlightedColorMask.x, color.r - (int)m_highlightedColorMask.x);
	m_highlightedColorMask.y = (float)MinI((int)m_highlightedColorMask.y, color.g - (int)m_highlightedColorMask.y);
	m_highlightedColorMask.z = (float)MinI((int)m_highlightedColorMask.z, color.b - (int)m_highlightedColorMask.z);
}

void TextHighlighterComponent::Update(float dtime)
{

}

void TextHighlighterComponent::Select()
{
	if (!m_selected)
	{
		auto textComp = m_object->GetComponent<TextComponent>();
		assert(textComp);

		auto color = textComp->GetColor();
		color.r += m_highlightedColorMask.x;
		color.g += m_highlightedColorMask.y;
		color.b += m_highlightedColorMask.z;

		textComp->SetColor(color);
	}
}

void TextHighlighterComponent::UnSelect()
{
	if (m_selected)
	{
		auto textComp = m_object->GetComponent<TextComponent>();
		assert(textComp);

		auto color = textComp->GetColor();
		color.r -= m_highlightedColorMask.x;
		color.g -= m_highlightedColorMask.y;
		color.b -= m_highlightedColorMask.z;

		textComp->SetColor(color);
	}
}

void TextHighlighterComponent::CheckMouseCollision()
{
	auto textComp = m_object->GetComponent<TextComponent>();
	assert(textComp);

	Vector2f diff = g_input->GetMousePosition() - m_object->GetGlobalPos();
	float alpha = -m_object->GetGlobalRotation() * (float)PI / 180.f;
	Vector2f rotatedDiff = Vector2f(diff.x * cos(alpha) - diff.y * sin(alpha), diff.x * sin(alpha) + diff.y * cos(alpha));

	if (rotatedDiff.x >= 0 &&
		rotatedDiff.y >= 0 &&

		rotatedDiff.x <= textComp->GetSize().x &&
		rotatedDiff.y <= textComp->GetSize().y)
	{
		Select();
	}
	else
	{
		UnSelect();
	}
}

void TextHighlighterComponent::ParseAttribute(const TiXmlAttribute* attribute)
{

}
