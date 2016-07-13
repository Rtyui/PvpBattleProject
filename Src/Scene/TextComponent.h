#pragma once

#include "Component.h"
#include "stdincl.h"

class TextComponent : public Component
{
	REGISTER(TextComponent);

public:

	TextComponent(void);
	~TextComponent(void);

	sf::Font					GetFont();
	std::string					GetText();

	uint						GetFontSize();
	Vector2f					GetSize();

	void						SetFont(const std::string& filename);
	void						SetText(const std::string& textName);
	void						SetFontSize(uint fontSize);
	void						SetTextColor(sf::Color color);
	void						SetAlpha(uint alpha);
	void						SetColor(const sf::Color& color);

	sf::Color					GetColor();

	virtual void				Update(float dtime) override;
	virtual void				PostUpdate(float dtime) override;

	virtual void				Draw() override;

private:

	virtual void				ParseAttribute(const TiXmlAttribute* attribute) override;

	sf::Text					m_text;
	sf::Font					m_font;

	sf::Color					m_color;

	std::string					m_textName;

	uint						m_fontSize;

	float						m_rotation;

	uint						m_alpha;

};

