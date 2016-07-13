#include "SpriteSheetComponent.h"
#include "App.h"
#include "Helpers.h"
#include "stdincl.h"

REGISTERIMPL(SpriteSheetComponent);

SpriteSheetComponent::SpriteSheetComponent() :
m_timer(0),
m_currentLine(0),
m_currentColumn(0)
{
}

SpriteSheetComponent::~SpriteSheetComponent()
{
}

void SpriteSheetComponent::SetSize(Vector2f size)
{
	m_sprite.setScale(Vector2f(size.x / m_size.x, size.y / m_size.y));
}

Vector2f SpriteSheetComponent::GetSize()
{
	return Vector2f(m_sprite.getScale().x * m_size.x, m_sprite.getScale().y * m_size.y);
}

void SpriteSheetComponent::SetTexture(const std::string& filename)
{
	std::string file;
	file.append(TEXTURES_FOLDER);
	file.append(filename);
	auto result = m_texture.loadFromFile(file);
	assert(result);
	m_sprite.setTexture(m_texture);
	m_size = Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
}

void SpriteSheetComponent::SetTexture(const sf::Texture& texture)
{
	m_texture = texture;
	m_sprite.setTexture(texture);
	m_size = Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
}


void SpriteSheetComponent::SetFrameWidth(float frameWidth)
{
	m_frameWidth = frameWidth;
}

void SpriteSheetComponent::SetFrameHeight(float frameHeight)
{
	m_frameHeight = frameHeight;
}

void SpriteSheetComponent::SetFrameRate(uint frameRate)
{
	m_frameRate = frameRate;
}

void SpriteSheetComponent::SetLineSize(uint lineSize)
{
	m_lineSize = lineSize;
}

void SpriteSheetComponent::SetLinesNumber(uint linesNumber)
{
	m_linesNumber = linesNumber;
	SetFrameHeight(m_sprite.getGlobalBounds().height / m_linesNumber);

}

void SpriteSheetComponent::SetColumnsNumber(uint columnsNumber)
{
	m_columnsNumber = columnsNumber;
	SetFrameWidth(m_sprite.getGlobalBounds().width / m_columnsNumber);
}

void SpriteSheetComponent::SetCurrentLine(int currentLine)
{
	m_currentLine = currentLine;
}

void SpriteSheetComponent::SetCurrentColumn(int currentColumn)
{
	m_currentColumn = currentColumn;
}

void SpriteSheetComponent::OnAddToObject()
{
	

	m_sprite.setTextureRect(sf::IntRect(m_currentLine * (int)m_frameWidth, m_currentLine * (int)m_frameHeight, (int)m_frameWidth, (int)m_frameHeight));
}

void SpriteSheetComponent::Update(float dtime)
{
	m_timer += dtime;
	if (m_timer > 1.f / m_frameRate)
	{
		m_timer -= 1.f / m_frameRate;
		m_currentColumn = (m_currentColumn + 1) % m_lineSize;
		m_sprite.setTextureRect(sf::IntRect(m_currentColumn * (int)m_frameWidth, m_currentLine * (int)m_frameHeight, (int)m_frameWidth, (int)m_frameHeight));
	}
}

void SpriteSheetComponent::PostUpdate(float dtime)
{
}

void SpriteSheetComponent::Draw()
{
	g_app->m_window.draw(m_sprite, m_object->GetTransform());
}

void SpriteSheetComponent::ParseAttribute(const TiXmlAttribute* attribute)
{
	Component::ParseAttribute(attribute);
	if (IsEqual(attribute->Name(), "texture"))
	{
		SetTexture(attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "frame_rate"))
	{
		SetFrameRate(attribute->UnsignedValue());
	}
	else if (IsEqual(attribute->Name(), "line_size"))
	{
		SetLineSize(attribute->UnsignedValue());
	}
	else if (IsEqual(attribute->Name(), "lines_number"))
	{
		SetLinesNumber(attribute->UnsignedValue());
	}
	else if (IsEqual(attribute->Name(), "columns_number"))
	{
		SetColumnsNumber(attribute->UnsignedValue());
	}
}