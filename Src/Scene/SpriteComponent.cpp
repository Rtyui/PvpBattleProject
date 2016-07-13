#include "SpriteComponent.h"
#include "App.h"
#include "Helpers.h"
#include "stdincl.h"

REGISTERIMPL(SpriteComponent);

SpriteComponent::SpriteComponent()
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::SetSize(Vector2f size)
{
	m_sprite.setScale(Vector2f(size.x / m_size.x, size.y / m_size.y));
}

Vector2f SpriteComponent::GetSize()
{
	return Vector2f(m_sprite.getScale().x * m_size.x, m_sprite.getScale().y * m_size.y);
}

sf::Sprite* SpriteComponent::GetSprite()
{
	return &m_sprite;
}


void SpriteComponent::SetAlpha(uint alpha)
{
	sf::Color color = m_sprite.getColor();
	color.a = alpha;
	m_sprite.setColor(color);
}

void SpriteComponent::SetTexture(const std::string& filename)
{
	std::string file;
	file.append(TEXTURES_FOLDER);
	file.append(filename);
	auto result = m_texture.loadFromFile(file);
	assert(result);
	m_sprite.setTexture(m_texture);
	m_size = Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
}

void SpriteComponent::SetTexture(const sf::Texture& texture)
{
	m_texture = texture;
	m_sprite.setTexture(texture);
	m_size = Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
}

void SpriteComponent::Update(float dtime)
{
}

void SpriteComponent::PostUpdate(float dtime)
{
}

void SpriteComponent::Draw()
{
	g_app->m_window.draw(m_sprite, m_object->GetTransform());
}

void SpriteComponent::Flip()
{
	m_sprite.setOrigin({ (float)((int)(m_sprite.getOrigin().x + m_sprite.getLocalBounds().width) % (int)(2 * m_sprite.getLocalBounds().width)), 0 });
	m_sprite.setScale(Vector2f(m_sprite.getScale().x * -1.f, m_sprite.getScale().y));
}


void SpriteComponent::ParseAttribute(const TiXmlAttribute* attribute)
{
	Component::ParseAttribute(attribute);
	if (IsEqual(attribute->Name(), "texture"))
	{
		SetTexture(attribute->Value());
	}
	else if (IsEqual(attribute->Name(), "size"))
	{
		SetSize(ParseVector2f(attribute->Value()));
	}
}