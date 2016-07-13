#pragma once

#include "Component.h"
#include "stdincl.h"

class SpriteSheetComponent : public Component
{
	REGISTER(SpriteSheetComponent);
public:

	SpriteSheetComponent(void);
	~SpriteSheetComponent(void);

	void					SetTexture(const std::string& filename);
	void					SetTexture(const sf::Texture& texture);

	void					SetFrameWidth(float frameWidth);
	void					SetFrameHeight(float frameHeight);

	void					SetFrameRate(uint frameRate);

	void					SetLineSize(uint lineSize);

	void					SetLinesNumber(uint linesNumber);
	void					SetColumnsNumber(uint columnsNumber);

	void					SetCurrentLine(int currentLine);
	void					SetCurrentColumn(int currentColumn);

	void					SetSize(Vector2f size);
	Vector2f				GetSize();

	virtual void			OnAddToObject() override;
	virtual void			Update(float dtime) override;
	virtual void			PostUpdate(float dtime) override;

	virtual void			Draw() override;


private:

	virtual void			ParseAttribute(const TiXmlAttribute* attribute) override;

	sf::Sprite				m_sprite;
	sf::Texture				m_texture;

	Vector2f				m_size;

	float					m_frameWidth;
	float					m_frameHeight;
	float					m_timer;

	uint					m_lineSize;
	uint					m_frameRate;

	int						m_currentLine;
	int						m_currentColumn;

	uint					m_linesNumber;
	uint					m_columnsNumber;
	


};

