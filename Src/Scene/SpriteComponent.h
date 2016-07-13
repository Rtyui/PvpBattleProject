#pragma once

#include "Component.h"
#include "stdincl.h"

class SpriteComponent : public Component
{
	REGISTER(SpriteComponent);
public:
    SpriteComponent(void);
    ~SpriteComponent(void);

	void					SetTexture(const std::string& filename);
	void					SetTexture(const sf::Texture& texture);

	void					SetSize(Vector2f size);
	Vector2f				GetSize();
	sf::Sprite*				GetSprite();

	void					SetAlpha(uint alpha);


	void					Flip();

	virtual void			Update(float dtime) override;
	virtual void			PostUpdate(float dtime) override;

	virtual void			Draw() override;


private:

	virtual void			ParseAttribute(const TiXmlAttribute* attribute) override;

	sf::Sprite				m_sprite;
	sf::Texture				m_texture;

	Vector2f				m_size;
};

