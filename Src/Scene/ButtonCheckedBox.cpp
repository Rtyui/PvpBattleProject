#include "ButtonCheckedBox.h"
#include "App.h"
#include "Helpers.h"
#include "stdincl.h"
#include "Input.h"
#include "SpriteComponent.h"

REGISTERIMPL(ButtonCheckedBox);

ButtonCheckedBox::ButtonCheckedBox():
m_selected(false)
{
}

ButtonCheckedBox::~ButtonCheckedBox()
{
}

void ButtonCheckedBox::SetSize(Vector2f size)
{
	m_size = size;
}

void ButtonCheckedBox::SetPos(Vector2f position)
{
	m_position = position;
}

void  ButtonCheckedBox::SetTexture(uint state, const std::string& filename)
{
	std::string file;
	file.append(RESOURCES);
	file.append(filename);
	auto result = m_textures[state].loadFromFile(file);
}

void ButtonCheckedBox::Select()
{
	if (!m_selected)
	{
		auto spriteComp = m_spriteHolder->GetComponent<SpriteComponent>();
		assert(spriteComp);

		spriteComp->SetTexture(m_textures[SELECTED]);

		m_selected = true;
	}
}

void ButtonCheckedBox::UnSelect()
{
	if (m_selected)
	{
		auto spriteComp = m_spriteHolder->GetComponent<SpriteComponent>();
		assert(spriteComp);

		spriteComp->SetTexture(m_textures[UNSELECTED]);

		m_selected = false;
	}
}